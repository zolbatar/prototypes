SuperStrict
Import "Colour.bmx"
Import "Fleet.bmx"
Import "GameData.bmx"
Import "GFX.bmx"
Import "Loadout.bmx"
Import "ModuleChooser.bmx"
Import "Piece.bmx"
Import "WeaponChooser.bmx"
Import "Vessel.bmx"
Import "UIFullScreenButtonBar.bmx"
Import "UIInputBox.bmx"
Import "UISelector.bmx"
Import "WeaponClass.bmx"

Type TShipEditor
	Const Spacer:Int = 8, zoom:Int = 128
	Field changes:Int = 0, selectedVessel:TVessel = Null
	Field toolboxX:Int, posX:Int, posY:Int, sizeGrid:Int, gridLeft:Int, gridTop:Int, gridRight:Int, gridBottom:Int, variantSelector:Int = 0
	Field renameMode:Int = 0, chooseModuleMode:Int = 0, listVesselMode:Int = 0, loadoutMode:Int = 0, chooseWeaponMode:Int = 0 
	Field renameUI:TUIInputBox, moduleUI:TModuleChooser, loadoutUI:TLoadout, listVesselsUI:TUISelector, weaponUI:TWeaponChooser
	Field origX:Int = -1, origY:Int = -1
	
	Function Create(gfx:TGFX, gd:TGameData, fleet:TFleet, v:TVessel)
		Local o:TShipEditor = New TShipEditor
		o.selectedVessel = v
		
		' Calc grid size
		Local sX:Int = (gfx.width - 10)  / o.selectedVessel.maxShapeX
		Local sY:Int = (gfx.height - TGameData.ToolbarHeight - o.PieceSize(gfx) - Spacer - 10 - 10)  / o.selectedVessel.maxShapeY
		o.sizeGrid = Min(sX, sY)
		
		' Loop
		gd.sf.p = MilliSecs()
		FlushKeys()
		Repeat
			If gd.pieces[o.toolboxX + 1].maxVariant > 1 Then o.variantSelector = 1 Else o.variantSelector = 0

			' Grid size varies depending on what is visible
			o.gridLeft = (gfx.width - 10 - (o.selectedVessel.maxShapeX * o.sizeGrid)) / 2
			o.gridTop = TGameData.ToolbarHeight + (o.PieceSize(gfx) + Spacer) + 10 + 5
			o.gridRight = o.gridLeft + (o.sizeGrid * o.selectedVessel.maxShapeX)
			o.gridBottom = o.gridTop + (o.sizeGrid * o.selectedVessel.maxShapeY)
			
			If o.renameMode = 0 And o.chooseModuleMode = 0 And o.listVesselMode = 0 And o.loadoutMode = 0 And o.chooseWeaponMode = 0 Then 
				Local click:String = gd.buttons.Clicked()
			
				If KeyHit(KEY_S) Then 
					fleet.SaveFleet()
				ElseIf KeyHit(KEY_D) Or click = "Delete" Then 
					o.DeleteGridLocation(gd.pieces)
				ElseIf KeyHit(KEY_COMMA) Or click = "RotateLeft" Then 
					o.RotateLeft()
				ElseIf KeyHit(KEY_PERIOD) Or click = "RotateRight" Then 
					o.RotateRight()
				ElseIf click = "DeleteVessel" And fleet.vessels.Count() > 0 Then
					ListRemove(fleet.vessels, o.selectedVessel)
					o.changes = 1
					o.selectedVessel = TVessel(fleet.vessels.First())
				ElseIf KeyHit(KEY_N) Or click = "NewVessel" Then
					o.selectedVessel = TVessel.Create()
					o.changes = 1
					ListAddLast(fleet.vessels, o.selectedVessel)
				ElseIf KeyHit(KEY_LEFT) Or click = "PreviousVessel" Then
					If fleet.vessels.First() <> o.selectedVessel Then o.selectedVessel = TVessel(fleet.vessels.FindLink(o.selectedVessel).PrevLink().Value())
				ElseIf KeyHit(KEY_RIGHT) Or click = "NextVessel" Then
					If fleet.vessels.Last() <> o.selectedVessel Then o.selectedVessel = TVessel(fleet.vessels.FindLink(o.selectedVessel).NextLink().Value())
				ElseIf KeyHit(KEY_C) Or click = "CentreVessel" Then o.selectedVessel.CentreBlueprint()
				ElseIf KeyHit(KEY_R) Or click = "RenameVessel" Then 
					FlushKeys()
					o.renameUI = TUIInputBox.Create("Enter the vessel name:", o.selectedVessel.name, 360, "Rename Vessel", 30)
					o.renameMode = 1
				ElseIf KeyHit(KEY_L) Or click = "ListVessels" Then 
					o.listVesselMode = 1
					Local s:TList = CreateList()
					For Local v:TVessel = EachIn fleet.vessels
						ListAddLast(s, v.name)
					Next
					o.listVesselsUI = TUISelector.Create(s, 350, "Select Vessel", "Vessel", 0, 0)
				End If
				If Left(click, 12) = "ChooseModule" Then
					Local s:String[] = click.Split(":")
					o.moduleUI = TModuleChooser.Create(Int(s[1]), Int(s[2]), "Choose a module:", "Choose Module") 
					o.chooseModuleMode = 1
				ElseIf Left(click, 12)  = "ChooseWeapon" Then
					Local s:String[] = click.Split(":")
					o.weaponUI = TWeaponChooser.Create(Int(s[1]), Int(s[2]), "Configure Weapon:", "Configure Weapon")
					o.chooseWeaponMode = 1
				End If
				If KeyHit(KEY_O) Or click = "ConfigureLoadout" Then 
					o.loadoutMode = 1
					o.loadoutUI = New TLoadout.Create("Choose loadout:", "Choose Loadout", o.selectedVessel) 
				End If
		
				' Mouse position on grid
				If MouseX() > o.gridLeft And MouseX() < o.gridRight And MouseY() > o.gridTop And MouseY() < o.gridBottom Then
					o.posX = (MouseX() - o.gridLeft) / o.sizeGrid
					o.posY = (MouseY() - o.gridTop) / o.sizeGrid
				Else
					o.posX = -1
					o.posY = -1 
				End If

				' Mouse click?
				If MouseHit(1) Then
					If gd.buttons.CheckClick(MouseX(), MouseY()) = 1 Then 
					ElseIf MouseY() < (TGameData.ToolbarHeight + o.PieceSize(gfx) + 10) And MouseY() > TGameData.ToolbarHeight Then 
						o.SelectToolboxItem(gfx)
					End If
				ElseIf MouseDown(1) Then
					If MouseX() <> o.origX Then
						If o.origX = -1 Then
							If MouseY() < (TGameData.ToolbarHeight + o.PieceSize(gfx) + 10) And MouseY() > TGameData.ToolbarHeight Then
								o.origX = MouseX()
								o.origY = MouseY()
							End If
						Else
							o.origX = MouseX()
							o.origY = MouseY()
						End If
					End If
				Else
					If o.origX <> -1 And o.origY <> -1 And o.posX <> -1 And o.posY <> -1 Then
						o.SelectGridLocation(gd.pieces)
					End If
					o.origX = -1
					o.origY = -1
				End If
			End If

			' Render
			gd.sf.Render(1.0)
			gd.buttons.ClearButtons()
			o.UIButtons(gd.buttons, fleet)
			o.UIToolbar(gfx)
			o.UISelector(gfx, gd.pieces, gd.fleetColours)
			o.UIGrid(gfx, 0)
			o.UIShapes(gd.pieces, gd.fleetColours, gd.buttons)
			o.UIGrid(gfx, 1)
			o.UIText(gfx, gd)
			If o.renameMode = 1 Then
				o.RenameVessel(gfx, gd)
			End If
			If o.chooseModuleMode = 1 Then
				o.ChooseModule(gfx, gd)
			End If
			If o.loadoutMode = 1 Then
				o.ChooseLoadout(gfx, gd)	
				gd.buttons.Render(gfx)
			End If
			If o.listVesselMode = 1 Then
				o.ListVessels(gfx, fleet, gd)
			End If
			If o.chooseWeaponMode = 1 Then
				o.ChooseWeapon(gfx, gd)
			End If
			gd.buttons.Render(gfx)
			
			' Quit?
			If KeyHit(KEY_Q) Then 
				If o.changes = 0 Then Return
				Local r:Int = TFullScreenButtonBar.CreateSave(gfx, gd.buttons)
				Select r
				Case 0
				Case 1
					fleet.SaveFleet()
					Return
				Case 2
					If fleet.ReloadFleet(gd.pieces) = -1 Then gd.LoadGD()
					Return
				End Select
			Else
				If o.renameMode = 0 And o.chooseModuleMode = 0 And o.listVesselMode = 0 And o.loadoutMode = 0 And o.chooseWeaponMode = 0 Then 
					If o.origX <> -1 And o.origY <> -1 Then 
						gfx.pointer = -1
						TPiece.RenderPiece(gd.pieces, o.sizeGrid, o.toolboxX + 1, o.origX, o.origY, 0, 0)
					End If
				End If
				gfx.UIScanlines()
				Flip()
			End If
			PollSystem()			
			gd.sf.Cycle()
		Forever
	End Function
	
	Method ListVessels(gfx:TGFX, fleet:TFleet, gd:TGameData)
		Local f:Int = listVesselsUI.Render(gfx, gd.buttons, gd.sf, 1)
		If f = - 100 Then
		ElseIf f = -1 Then 
			listVesselMode = 0
			Return
		Else
			' Selected
			selectedVessel = TVessel(fleet.vessels.ValueAtIndex(f))
			listVesselMode = 0
		End If
	End Method

	Method RenameVessel(gfx:TGFX, gd:TGameData)
		Local name:String = renameUI.Render(gfx, gd, 1)
		If name = Null Then Return
		FlushKeys()
		selectedVessel.name = name
		renameMode = 0
		changes = 1
	End Method
	
	Method ChooseModule(gfx:TGFX, gd:TGameData)
		Local m:Int = moduleUI.Render(gfx, 1, gd)
		If m = -1 Then Return
		If m = -2 Then
			chooseModuleMode = 0
			Return
		End If
		FlushKeys()
		selectedVessel.shapeV[posX, posY].variant = m
		chooseModuleMode = 0
		changes = 1
	End Method
	
	Method ChooseWeapon(gfx:TGFX, gd:TGameData)
		Local m:Int = weaponUI.Render(gfx, 1, gd, selectedVessel)
		If m = -1 Then Return
		If m = -2 Then
			chooseWeaponMode = 0
			Return
		End If
		FlushKeys()
		chooseWeaponMode = 0
		changes = 1
	End Method

	Method ChooseLoadout(gfx:TGFX, gd:TGameData)
		Local m:Int = loadoutUI.Render(gfx, 1, gd)
		If m = -1 Then Return
		If m = -2 Then
			loadoutMode = 0
			Return
		End If
		loadoutMode = 0
		If m = -3 Then
			changes = 1
		End If
	End Method

	Method RotateLeft()
		If selectedVessel.shapeV[posX, posY].piece = 3 Then Return
		selectedVessel.shapeV[posX, posY].RotateL()
		changes = 1
	End Method
	
	Method RotateRight()
		If selectedVessel.shapeV[posX, posY].piece = 3 Then Return
		selectedVessel.shapeV[posX, posY].RotateR()
		changes = 1
	End Method

	Method SelectToolboxItem(gfx:TGFX)
		toolboxX = (MouseX() - 5) / (PieceSize(gfx) + 8)
	End Method

	Method DeleteGridLocation(pieces:TPiece[])
		If posX = -1 Or posY = -1 Then Return
		selectedVessel.shapeV[posX, posY].piece = 0
		selectedVessel.shapeV[posX, posY].rot = 0 
		selectedVessel.shapeV[posX, posY].variant = 0 
		selectedVessel.shapeV[posX, posY].autoFire = 1.0 	
		selectedVessel.shapeV[posX, posY].preferredAmmo1V = -1
		selectedVessel.shapeV[posX, posY].preferredAmmo2V = -1
		selectedVessel.shapeV[posX, posY].preferredAmmo3V = -1
		selectedVessel.BuildGunsMissilesModules(pieces)
		changes = 1
	End Method

	Method SelectGridLocation(pieces:TPiece[])
		If posX = -1 Or posY = -1 Then Return
		If selectedVessel.shapeV[posX, posY].piece = toolboxX + 1 Then Return  
		selectedVessel.shapeV[posX, posY].piece = toolboxX + 1 
		selectedVessel.shapeV[posX, posY].rot = 0 
		selectedVessel.shapeV[posX, posY].variant = 0 
		selectedVessel.shapeV[posX, posY].autoFire = 1.0 	
		selectedVessel.shapeV[posX, posY].preferredAmmo1V = -1
		selectedVessel.shapeV[posX, posY].preferredAmmo2V = -1
		selectedVessel.shapeV[posX, posY].preferredAmmo3V = -1
		selectedVessel.BuildGunsMissilesModules(pieces)
		changes = 1
	End Method
	
	Method UIShapes(pieces:TPiece[], colours:TColour[], buttons:TButtons)
		SetOrigin(gridLeft + (sizeGrid / 2), gridTop + (sizeGrid / 2))
		SetPlayerColour(2, colours)
		For Local y:Int = 0 To selectedVessel.maxShapeY - 1
			For Local x:Int = 0 To selectedVessel.maxShapeX - 1
				Local b:TBlock = selectedVessel.shapeV[x, y]
				TPiece.RenderPiece(pieces, sizeGrid, b.piece, x * sizeGrid, y * sizeGrid, b.rot, b.variant)
				Local spX:Int = (sizeGrid - 50) / 2.0
				Local spY:Int = (sizeGrid - TButtons.HeightSmall) / 2.0
				If pieces[b.piece].isModule = 1 Then
					If b.variant = 0 Then
						buttons.AddButtonMS("Choose", 2, (x * sizeGrid) + spX + gridLeft, (y * sizeGrid) + spY + gridTop + 5, 50 ,"ChooseModule:" + x + ":" + y)
					Else
						buttons.AddButtonMS("Change", 1, (x * sizeGrid) + spX + gridLeft, (y * sizeGrid) + spY + gridTop + 5, 50 ,"ChooseModule:" + x + ":" + y)
					End If
				ElseIf pieces[b.piece].isGun = 1 Or pieces[b.piece].isMissile = 1 Then
					If selectedVessel.shapeV[x, y].preferredAmmo1V = -1 And selectedVessel.shapeV[x, y].preferredAmmo2V = -1 And selectedVessel.shapeV[x, y].preferredAmmo3V = -1 Then
						buttons.AddButtonMS("Choose", 2, (x * sizeGrid) + spX + gridLeft, (y * sizeGrid) + spY + gridTop + 5, 50 ,"ChooseWeapon:" + x + ":" + y)	
					Else
						buttons.AddButtonMS("Change", 1, (x * sizeGrid) + spX + gridLeft, (y * sizeGrid) + spY + gridTop + 5, 50 ,"ChooseWeapon:" + x + ":" + y)	
					End If
				End If
				If b.piece > 0 And x = posX And y = posY Then
					buttons.AddButtonImage(0, 5, (x * sizeGrid) + gridLeft, (y * sizeGrid) + gridTop, 25, "RotateLeft")
					buttons.AddButtonImage(2, 2, (x * sizeGrid) + gridLeft + (sizeGrid / 2) - 12.5, (y * sizeGrid) + gridTop, 25, "Delete")
					buttons.AddButtonImage(1, 5, (x * sizeGrid) + gridLeft + (sizeGrid - 25), (y * sizeGrid) + gridTop, 25, "RotateRight")
				End If
			Next
		Next
	End Method

	Method UIGrid(gfx:TGFX, phase:Int)
		SetColor(0, 0, 160)
		SetAlpha(0.15)
		If phase = 0 Then DrawRect(gridLeft, gridTop, gridRight - gridLeft, gridBottom - gridTop)
'		If phase = 0 Then gfx.BlueprintBackgroundRenderPortion(gridLeft, gridTop, gridRight - gridLeft, gridBottom - gridTop)
		SetOrigin(gridLeft, gridTop)
		If phase = 0 Then
			SetAlpha(0.5)
			gfx.GridBox(selectedVessel.maxShapeX, selectedVessel.maxShapeY, sizeGrid, sizeGrid, -1, -1, 1)
		Else
			SetAlpha(0.05)
			gfx.GridBox(selectedVessel.maxShapeX, selectedVessel.maxShapeY, sizeGrid, sizeGrid, posX, posY, 0)
		End If
		SetAlpha(1.0)
		SetOrigin(0, 0)
	End Method
	
	Method UIButtons(buttons:TButtons, fleet:TFleet)
		buttons.ClearButtons()
		buttons.AddButtonBordered("New", "Vessel", 1, 10, 5, 100, "NewVessel")
		buttons.AddButtonBordered("Delete", "Vessel", 2, 110, 5, 100, "DeleteVessel", selectedVessel = Null)
		buttons.AddButtonBordered("Rename", "Vessel", 0, 210, 5, 100, "RenameVessel", selectedVessel = Null)
		buttons.AddButtonBordered("Previous", "Vessel", 0, 310, 5, 100, "PreviousVessel", selectedVessel = Null Or fleet.vessels.First() = selectedVessel)
		buttons.AddButtonBordered("Next", "Vessel", 0, 410, 5, 100, "NextVessel", selectedVessel = Null Or fleet.vessels.Last() = selectedVessel)
		buttons.AddButtonBordered("List", "Vessels", 0, 510, 5, 100, "ListVessels", selectedVessel = Null)
		buttons.AddButtonBordered("Centre", "Vessel", 4, 620, 5, 100, "CentreVessel", selectedVessel = Null)
		buttons.AddButtonBordered("Configure", "Loadout", 5, 730, 5, 100, "ConfigureLoadout", selectedVessel = Null)
	End Method

	Method UIToolbar(gfx:TGFX)
		SetColor(0, 0, 160)
		SetAlpha(0.5)
		DrawRect(0, 0, gfx.width, TGameData.ToolbarHeight + PieceSize(gfx) + Spacer + 10)
		SetColor(255, 255, 255)
		SetAlpha(1.0)
	End Method
	
	Method PieceSize:Int(gfx:TGFX)
		Return ((gfx.width - 10) / (NoPieces - 1)) - 8
	End Method
	
	Method PieceSizeV:Int(gfx:TGFX, pieces:TPiece[])
		Return ((gfx.height - TGameData.ToolbarHeight - PieceSize(gfx) - Spacer - 10) / (pieces[toolboxX + 1].maxVariant - 1)) - 4
	End Method

	Method UISelector(gfx:TGFX, pieces:TPiece[], colours:TColour[])
		Local ps:Int = PieceSize(gfx)
		SetOrigin(5, TGameData.ToolbarHeight + 5)

		' Grid
		SetColor(0, 0, 160)
		SetAlpha(1.0)
		gfx.Grid(NoPieces - 1, 1, ps + Spacer, ps + Spacer, ToolboxX, 0, 0)

		' Pieces
		SetAlpha(1.0)
		SetPlayerColour(2, colours)
		For Local i:Int = 0 To NoPieces - 2
			TPiece.RenderPiece(pieces, ps, i + 1, (i * (ps + spacer)) + (spacer / 2) + (ps / 2), (ps / 2) + (spacer / 2), 0, 0)
		Next
		SetOrigin(0,0)
		SetAlpha(1.0)
	End Method

	Method UIText(gfx:TGFX, gd:TGameData)
		Local p:TPiece
		Local ms:Int = 0
		Local mg:Int = 0
		If posX <> -1 And posY <> -1 Then
			p = gd.pieces[selectedVessel.shapeV[posX, posY].piece]
			ms = p.isModule And selectedVessel.shapeV[posX, posY].variant > 0
			mg = p.isMissile Or p.isGun
		End If
		
		gfx.SetFontSize(TGFX.FontMediumSmall)
		SetOrigin(5, gridTop)
		SetColor(255, 255, 0)
		gfx.SetFontSize(TGFX.FontMedium)
		DrawText("Component Specification:", 0, 0)
		gfx.SetFontSize(TGFX.FontMediumSmall)
		SetColor(200, 200, 200)
		DrawText("Mass: ", 0, 20)
		DrawText("Power Needed: ", 0, 35)
		DrawText("Cost: ", 0, 50)
		DrawText("Description: ", 0, 65)

		SetColor(255, 255, 0)
		SetOrigin(5, gridTop + 90)
		gfx.SetFontSize(TGFX.FontMedium)
		DrawText("Vessel Specification:", 0, 0)
		gfx.SetFontSize(TGFX.FontMediumSmall)
		SetColor(200, 200, 200)
		DrawText("Name: ", 0, 20)
		DrawText("Mass: ", 0, 35)
		DrawText("Speed: ", 0, 50)
		DrawText("Rotation: ", 0, 65)
		DrawText("Hull: ", 0, 80)
		DrawText("Power Output: ", 0, 95)
		DrawText("Power Required: ", 0, 110)
		DrawText("Shield: ", 0, 125)
		DrawText("Basic Cost: ", 0, 140)
		DrawText("+ Modules Cost: ", 0, 155)
		DrawText("+ Ammo Cost: ", 0, 170)

		If ms = 1 Then 
			SetOrigin(5, gridTop + 285)
			SetColor(255, 255, 0)
			gfx.SetFontSize(TGFX.FontMedium)
			DrawText("Equipped Module:", 0, 0)
			gfx.SetFontSize(TGFX.FontMediumSmall)
			SetColor(200, 200, 200)
			DrawText("Mass: ", 0, 20)
			DrawText("Power Needed: ", 0, 35)
			DrawText("Description: ", 0, 50)
		ElseIf mg = 1
			SetOrigin(5, gridTop + 285)
			SetColor(255, 255, 0)
			gfx.SetFontSize(TGFX.FontMedium)
			DrawText("Equipped Weapon Mount:", 0, 0)
			gfx.SetFontSize(TGFX.FontMediumSmall)
			SetColor(200, 200, 200)
			DrawText("Mass: ", 0, 20)
			DrawText("Power Needed: ", 0, 35)
			DrawText("Description: ", 0, 50)
			DrawText("Preferred 1: ", 0, 65)
			DrawText("Preferred 2: ", 0, 80)
			DrawText("Preferred 3: ", 0, 95)
		End If

		SetColor(0, 255, 0)
		SetOrigin(100, gridTop)
		DrawText(gd.pieces[toolboxX + 1].GetMass() + " tons", 0, 20)
		DrawText(gd.pieces[toolboxX + 1].GetPower() + "MW", 0, 35)
		DrawText(gd.pieces[toolboxX + 1].GetCost() + " points", 0, 50)
		DrawText(gd.pieces[toolboxX + 1].GetDescription(), 0, 65)

		SetOrigin(100, gridTop + 90)
		DrawText(selectedVessel.name, 0, 20)
		Local mass:Int = selectedVessel.CalcMass(gd.pieces)
		DrawText(mass + " tons", 0, 35)
		Local propulsion:Int = selectedVessel.CalcPropulsion(gd.pieces, gd.defaultOnOff)
		Local speed:Int = selectedVessel.CalcSpeed(propulsion, mass)
		Local dps:Float = selectedVessel.CalcDPS(propulsion, mass)
		DrawText(Int(speed) + " m/s", 0, 50)
		DrawText(RoundDouble(dps, 1) + " dps", 0, 65)
		DrawText(selectedVessel.CalcArmour(mass) + " HP", 0, 80)
		Local po:Int = selectedVessel.CalcPowerOutput(gd.pieces, gd.defaultCondition, gd.defaultOnOff)
		Local poi:Int = selectedVessel.CalcPower(gd.pieces, gd.defaultOnOff)  
		If po < poi Then SetColor(255, 0, 0)
		DrawText(po + "MW", 0, 95)
		SetColor(0, 255, 0)
		DrawText(poi + "MW", 0, 110)
		DrawText(selectedVessel.CalcShield(gd.pieces, gd.defaultCondition, gd.defaultOnOff) + " SP", 0, 125)
		DrawText(selectedVessel.CalcCostBase(gd.pieces) + " points", 0, 140)
		DrawText(selectedVessel.CalcCost(gd.pieces) + " points", 0, 155)
		DrawText(selectedVessel.CalcCostTotal(gd.pieces, gd.weapons, selectedVessel.loadout) + " points", 0, 170)
		SetColor(255, 255, 255)

		If ms = 1 Then 
			Local v:Int = selectedVessel.shapeV[posX, posY].variant
			SetColor(0, 255, 0)
			SetOrigin(100, gridTop + 285)
			DrawText(p.GetMass(v) + " tons", 0, 20)
			DrawText(p.GetPower(v) + "MW", 0, 35)
			DrawText(p.GetDescription(v), 0, 50)
		ElseIf mg = 1
			Local v:Int = selectedVessel.shapeV[posX, posY].variant
			SetColor(0, 255, 0)
			SetOrigin(100, gridTop + 285)
			DrawText(p.GetMass(v) + " tons", 0, 20)
			DrawText(p.GetPower(v) + "MW", 0, 35)
			DrawText(p.GetDescription(v), 0, 50)
			If selectedVessel.shapeV[posX, posY].preferredAmmo1V = -1 Then
				DrawText("None", 0, 65)
			Else
				DrawText(gd.weapons[selectedVessel.shapeV[posX, posY].preferredAmmo1V].name, 0, 65)
			End If
			If selectedVessel.shapeV[posX, posY].preferredAmmo2V = -1 Then
				DrawText("None", 0, 80)
			Else
				DrawText(gd.weapons[selectedVessel.shapeV[posX, posY].preferredAmmo2V].name, 0, 80)
			End If
			If selectedVessel.shapeV[posX, posY].preferredAmmo3V = -1 Then
				DrawText("None", 0, 95)
			Else
				DrawText(gd.weapons[selectedVessel.shapeV[posX, posY].preferredAmmo3V].name, 0, 95)
			End If
		End If

	End Method
	
End Type

