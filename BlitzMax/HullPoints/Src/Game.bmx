SuperStrict
Import "GameData.bmx"
Import "GameEntity.bmx"
Import "GameRender.bmx"
Import "GameSave.bmx"
Import "GameState.bmx"
Import "GFX.bmx"
Import "Profiler.bmx"
Import "Radar.bmx"
Import "UIFullScreenButtonBar.bmx"
Import "XY.bmx"
Import "XYEntity.bmx"

Type TGame
	Const Spacer:Int = 8
	Field firstX:Int = -1, firstY:Int = -1, lastX:Int = -1, lastY:Int = -1, width:Int, height:Int
	Field g:TGameState, selectedVessel:TGameEntity = Null, gd:TGameData, timeLastPainted:Long = 0, radar:TRadar
	Field scrolling:Int = 0, prevX:Int, prevY:Int, origX:Int = 0, origY:Int = 0, previousScroll:Int = 0, changes:Int = 0, filename:String, showOptions:Int = 0
	Field originalCentreX:Double, originalCentreY:Double, overview:Int = 0

	Function CreateWithGameState(gfx:TGFX, gd:TGameData, g:TGameState)
		Local o:TGame = New TGame
		o.g = g
		o.radar = TRadar.Create(o.g, gd.fleetColours)
		o.selectedVessel = Null
		o.gd = gd
		gd.sf.SetRandomImage()
		
		' Set all start positions, move stuff to reserve
		For Local player:Int = 0 To 1
			For Local ge:TGameEntity = EachIn g.entities[player]
				ge.startX = ge.x
				ge.startY = ge.y
				
				For Local sc:TScriptItem = EachIn ge.script
					If sc.t = TScriptItem.ScriptJumpIn Then
						ListAddFirst(g.entitiesReserve, ge)
						ListRemove(g.entities[ge.owningPlayerNo], ge)
					End If
				Next
			Next
		Next
		
		' Starting stats
		g.p1PointsInitial = g.p1Points
		g.p2PointsInitial = g.p2Points
		g.milliStart = MilliSecs()
		
		o.Start(gfx, gd)
	End Function
	
	Method Start(gfx:TGFX, gd:TGameData)
		?debug
   			TProfiler.Enter("Game::Start")
  		?
		g.ResetScale()
		TGameRender.SetupMapView(gfx, gd, g, 0)
		origX = 0
		origY = 0
		g.centreX = 0.0
		g.centreY = 0.0
		originalCentreX = g.centreX
		originalCentreY = g.centreY
		
		g.cinematicMode = 1
		g.showRadar = 0
		g.showOrders = 0
		g.showMissileTargets = 0
		g.showStars = 1
		g.showTrails = 1

		' Loop
		gd.sf.p = MilliSecs()
		FlushKeys()
		FlushMouse()
		Local time:Long = 0
		Local ms:Long = MilliSecs() - g.milliStart
		PaintTargets(ms)
		Repeat
			Local m:Long = MilliSecs()
			Local click:String = ""
			click = gd.buttons.Clicked()
	
			If KeyHit(KEY_ESCAPE) Then
				Clear()
				selectedVessel = Null
			ElseIf KeyHit(KEY_TAB) And selectedVessel <> Null Then
				If overview = 1 Then
					overview = 0
				Else
					selectedVessel.vessel.RealDimension(firstX, firstY, lastX, lastY, width, height)
					overview = 1
				End If
			End If
	
			If showOptions = 1 Then
				If KeyHit(KEY_O) Then Clear()
				If click = "ShowTrails" Then g.showTrails = g.showTrails ~ 1
				If click = "ShowTracking" Then g.showMissileTargets = g.showMissileTargets  ~ 1
				If click = "ColourCoded" Then g.bulletsInColour = g.bulletsInColour ~ 1
				If click = "ShowMessages" Then g.showMessages = g.showMessages ~ 1
				If click = "ShowDetailedMessages" Then g.optionShowAllMessages = g.optionShowAllMessages ~ 1
				If MouseHit(1) Then gd.buttons.CheckClick(MouseX(), MouseY())
			ElseIf overview = 1 Then
				If MouseHit(1) Then gd.buttons.CheckClick(MouseX(), MouseY())
				If click = "DischargeEMP" And selectedVessel <> Null Then
					selectedVessel.haloActive = ms  
					selectedVessel.lastEMP = ms
					FireHalo(ms)
					overview = 0
				ElseIf Left(click, 15) = "LaunchFighters:" And selectedVessel <> Null Then
					Local sa:String[] = Right(click, click.Length - 15).Split(",")
					Local xy:TXY = TXY.Create(Int(sa[0]), Int(sa[1]))
					ListAddFirst(selectedVessel.launching, xy)
				End If
			Else
				CheckOrderInput(click, ms)
				If KeyHit(KEY_SPACE) Then
					If g.cinematicMode = 0 Then
						g.cinematicMode = 1
						g.showRadar = 0
						g.showOrders = 0
						g.showMissileTargets = 0
						g.showStars = 1
						g.showTrails = 1
					Else
						g.cinematicMode = 0
						g.showRadar = 1
						g.showOrders = 1
						g.showMissileTargets = 0
						g.showStars = 1
						g.showTrails = 1
					End If
				End If
				If KeyHit(KEY_BACKSPACE) Then 
					g.optionShowEnemyInfo = g.optionShowEnemyInfo ~ 1
					g.allowAIEnemySelection = g.allowAIEnemySelection ~ 1
				End If
				If KeyHit(KEY_C) And selectedVessel <> Null Then
					g.centreX = selectedVessel.x
					g.centreY = selectedVessel.y
					originalCentreX = g.centreX
					originalCentreY = g.centreY
					origX = 0
			  		origY = 0
				ElseIf KeyHit(KEY_R) Or click = "ResetMapView" Then
					g.ResetScale()
					origX = 0
		 	 		origY = 0
					g.centreX = 0.0
					g.centreY = 0.0
					originalCentreX = g.centreX
					originalCentreY = g.centreY
				ElseIf KeyHit(KEY_EQUALS) Or MouseZ() > previousScroll Then
					g.ZoomIn()
					originalCentreX = g.centreX
					originalCentreY = g.centreY
					origX = 0
	 		 		origY = 0
				ElseIf KeyHit(KEY_MINUS) Or MouseZ() < previousScroll Then
					g.ZoomOut()
					originalCentreX = g.centreX
					originalCentreY = g.centreY
					origX = 0
			  		origY = 0
				ElseIf KeyHit(KEY_O) Then
					showOptions = 1
				End If

				' Select on map?
				If MouseHit(1) Then 
					If gd.buttons.CheckClick(MouseX(), MouseY()) = 0 Then
						SelectEntity(gd, gfx, ms)
					End If
				End If
				
				' Scroll?
				If MouseDown(2) Then
					ScrollAction(gfx)
				Else
					scrolling = 0
					originalCentreX = g.centreX
					originalCentreY = g.centreY
					origX = 0
			  		origY = 0
				End If
			End If
			previousScroll = MouseZ()
			
			' Set scroll position
			g.centreX = originalCentreX + (origX * g.mapSectionSize * (g.scale / g.strategicScale) / g.size)
			g.centreY = originalCentreY - (origY * g.mapSectionSize * (g.scale / g.strategicScale) / g.size)
				
			' Render
			BuildButtons(gfx, gd)
			If overview = 0 Then
				TGameRender.Render(gfx, gd, g, selectedVessel, HoverEntity(gd, gfx), Null, Null, 0, radar, ms) 
			Else
				TGameRender.Render(gfx, gd, g, selectedVessel, Null, Null, Null, 0, radar, ms) 
			End If
			If showOptions = 1 Then	ShowOptionsWindow(gfx)
			If overview = 1 Then UIShapes(gfx, gd.pieces, gd.fleetColours, gd.buttons, ms)
			gd.buttons.Render(gfx)

			' Quit?
			If KeyHit(KEY_Q) Then 
				Local r:Int = TFullScreenButtonBar.CreateEndGame(gfx, gd.buttons)
				Select r
				Case 0
				Case 1
					?debug
   						TProfiler.Leave("Game::Start")
				  	?
					Return
				Case 2
					?debug
   						TProfiler.Leave("Game::Start")
				  	?
					Return
				End Select
			Else
				' Tot up points
				TGameEntity.CalcPoints(gd, g)
			
				' Won/lose?
				Local e:Int = 0 
				
				' Always win if everything destroyed
				If g.p1points = 0 Then
					SetColor(0, 0, 0)
					SetAlpha(0.25)
					DrawRect(0, 0, gfx.width, gfx.height)
					SetAlpha(1.0)
					SetColor(255, 255, 255)
					gfx.CenteredText(TGFX.FontXXLarge, "Defeat!", gfx.height / 2 - 100)
					SetColor(255, 255, 0)
					gfx.CenteredText(TGFX.FontXLarge, "All your vessels were destroyed.", gfx.height / 2)
					e = 1
				ElseIf g.p2points = 0 Then
					SetColor(0, 0, 0)
					SetAlpha(0.25)
					DrawRect(0, 0, gfx.width, gfx.height)
					SetAlpha(1.0)
					SetColor(255, 255, 255)
					gfx.CenteredText(TGFX.FontXXLarge, "Victory!", gfx.height / 2 - 100)
					SetColor(255, 255, 0)
					gfx.CenteredText(TGFX.FontXLarge, "You annihilated the enemy!", gfx.height / 2)
					e = 1
				End If
				If e = 0 Then
					If g.victoryCondition = TVictoryConditions.VictoryHoldout Then
						If ms > g.lastMissionCheck + 1000 Then
							g.lastMissionCheck = ms
							
							' Timeout?
							Local t:Long = g.victoryHoldOut - (ms / 1000)
							If t <= 0 Then
								e = 1
								SetColor(0, 0, 0)
								SetAlpha(0.5)
								DrawRect(0, 0, gfx.width, gfx.height)
								SetAlpha(1.0)
								SetColor(255, 255, 255)
								gfx.CenteredText(TGFX.FontXXLarge, "Victory!", gfx.height / 2 - 100)
								SetColor(255, 255, 0)
								gfx.CenteredText(TGFX.FontXLarge, "You successfully held onto the objective.", gfx.height / 2)
							Else
								e = 1
								For Local ge:TGameEntity = EachIn g.entities[0]
									If DistanceIsLess(ge.x, ge.y, g.victoryX, g.victoryY, 5000) Then
										e = 0
										Exit
									End If
								Next
								If e = 1 Then
									SetColor(0, 0, 0)
									SetAlpha(0.5)
									DrawRect(0, 0, gfx.width, gfx.height)
									SetAlpha(1.0)
									SetColor(255, 255, 255)
									gfx.CenteredText(TGFX.FontXXLarge, "Defeat!", gfx.height / 2 - 100)
									SetColor(255, 255, 0)
									gfx.CenteredText(TGFX.FontXLarge, "You failed to hold the objective.", gfx.height / 2)
								End If
							End If
						End If
					ElseIf g.victoryCondition = TVictoryConditions.VictoryProtect
						g.remaining = 0
						For Local ge:TGameEntity = EachIn g.victoryEntityList
							If ge.died = 0 Then g.remaining :+ 1
						Next 
						If g.remaining = 0 Then e = 1
						If e = 1 Then
							SetColor(0, 0, 0)
							SetAlpha(0.5)
							DrawRect(0, 0, gfx.width, gfx.height)
							SetAlpha(1.0)
							SetColor(255, 255, 255)
							gfx.CenteredText(TGFX.FontXXLarge, "Defeat!", gfx.height / 2 - 100)
							SetColor(255, 255, 0)
							gfx.CenteredText(TGFX.FontXLarge, "You failed to protect the required vessels.", gfx.height / 2)
						End If
					End If
				End If
				gfx.UIScanlines()
				Flip()
				If e = 1 Then
					Delay(150)
					FlushMouse()
					FlushKeys()
					Repeat 
						If MouseHit(1) Then Exit
						If GetChar() <> 0 Then Exit 
					Forever
					FlushKeys()
					FlushMouse()
					Return
				End If
			End If
			PollSystem()			
			gd.sf.Cycle()

			' Animate
			time = MilliSecs() - ms - g.milliStart
			g.frameTime = MilliSecs() - m
			m = MilliSecs() - g.milliStart
			If m < 0 Then m :+ 2147483648
			If timeLastPainted < ms - 5000 Then PaintTargets(ms)
			radar.SetVisible(0)
			Animate(Double(time) / 1000.0, ms)
			g.calcTime = (MilliSecs() - g.milliStart - m)
			Local totalFrameTime:Double = Double(g.calcTime + g.frameTime) / 1000.0
			g.Zoom(totalFrameTime)
			ms = m

		Forever
		?debug
   			TProfiler.Leave("Game::Start")
  		?
	End Method

	Method PieceSize:Int(gfx:TGFX)
		?debug
   			TProfiler.Enter("Game::PieceSize")
  		?
		Local i:Int = ((gfx.width - 10) / (NoPieces - 1)) - 8
		?debug
   			TProfiler.Leave("Game::PieceSize")
  		?
		Return i
	End Method
	
	Method UIShapes(gfx:TGFX, pieces:TPiece[], colours:TColour[], buttons:TButtons, ms:Long)
		?debug
   			TProfiler.Enter("Game::UIShapes")
  		?
		If selectedVessel = Null Then
			overview = 0
			?debug
   				TProfiler.Leave("Game::UIShapes")
		  	?
			Return
		End If
		buttons.ClearButtons()
		
		' Calc grid size
		Local sX:Int = (gfx.width - 50)  / width
		Local sY:Int = (gfx.height - 50)  / height
		Local sizeGrid:Int = Min(sX, sY)

		Local gridLeft:Int = (gfx.width - (width * sizeGrid)) / 2
		Local gridTop:Int = (gfx.height - (height * sizeGrid)) / 2
		SetOrigin(0, 0)
		SetColor(0, 0, 0)
		SetAlpha(0.8)
		DrawRect(0, 0, gfx.width, gfx.height)
		SetOrigin(gridLeft + (sizeGrid / 2), gridTop + (sizeGrid / 2))
		Local s:String
		For Local y:Int = 0 To height - 1
			For Local x:Int = 0 To width - 1
				Local b:TBlock = selectedVessel.shape[x + firstX, y + firstY]
				Local p:TPiece = pieces[b.piece]
				SetPlayerColour(selectedVessel.owningPlayerNo, colours)
				TPiece.RenderPiece(pieces, sizeGrid, b.piece, x * sizeGrid, y * sizeGrid, b.rot, b.variant)
				Local spX:Int = (sizeGrid - 50) / 2.0
				Local spX100:Int = (sizeGrid - 100) / 2.0
				Local spY:Int = (sizeGrid - TButtons.HeightSmall) / 2.0
				If p.isModule = 1 Or p.isMissile = 1 Or p.isGun = 1 Or p.propulsion.length > 0 Or p.isLauncher = 1 Then 
					Local c:Double = selectedVessel.condition[x + firstX, y + firstY]
					gfx.SetFontSize(TGFX.FontLarge)
					If c > 0.75 Then SetColor(124, 252, 0) ElseIf c > 0.5 Then SetColor(255, 153, 0) Else SetColor(255, 0, 0) 
					s = ((Int(c * 100.0) / 5) * 5) + "%"
					If selectedVessel.onOff[x + firstX, y + firstY] = 0.0 Then 
						If selectedVessel.condition[x + firstX, y + firstY] = 0.0 Then 
							s = "DESTROYED"
						Else
							s = "DOWN"
						End If
					End If
					DrawText(s, x * sizeGrid - (gfx.GetCachedFontWidth(s) / 2.0), y * sizeGrid - 35)
					gfx.SetFontSize(TGFX.FontSmall)
					SetColor(255, 255, 255)
					DrawText(p.descriptions[b.variant], x * sizeGrid - (gfx.GetCachedFontWidth(p.descriptions[b.variant]) / 2), y * sizeGrid - 10)
					gfx.SetFontSize(TGFX.FontMedium)
					If p.isMissile = 1 And selectedVessel.condition[x + firstX, y + firstY] > 0.0 Then
						If b.weapon = Null Then 
							SetColor(255, 255, 255)
							Local s:String = "Out of ammo"
							DrawText(s, x * sizeGrid - (gfx.GetCachedFontWidth(s) / 2), y * sizeGrid + gfx.GetCachedFontHeight(" ") + 5)
						Else
							SetColor(255, 255, 0)
							DrawText(b.weapon.name, x * sizeGrid - (gfx.GetCachedFontWidth(b.weapon.name) / 2), y * sizeGrid + 5)
							SetColor(255, 255, 255)
							s = b.numberRemaining + " missiles"
							If b.numberRemaining = 0 And selectedVessel.AmmoRemaining(x + firstX, y + firstY) = 0 Then s = "Out of ammo"
							DrawText(s, x * sizeGrid - (gfx.GetCachedFontWidth(s) / 2), y * sizeGrid + gfx.GetCachedFontHeight(b.weapon.name) + 5)
						End If
					ElseIf p.isGun = 1 And selectedVessel.condition[x + firstX, y + firstY] > 0.0 Then
						If b.weapon = Null Then 
							SetColor(255, 255, 255)
							Local s:String = "Out of ammo"
							DrawText(s, x * sizeGrid - (gfx.GetCachedFontWidth(s) / 2), y * sizeGrid + gfx.GetCachedFontHeight(" ") + 5)
						Else
							SetColor(255, 255, 0)
							DrawText(b.weapon.name, x * sizeGrid - (gfx.GetCachedFontWidth(b.weapon.name) / 2), y * sizeGrid + 5)
							SetColor(255, 255, 255)
							s = b.numberRemaining + " shots"
							If b.numberRemaining = 0 And selectedVessel.AmmoRemaining(x + firstX, y + firstY) = 0 Then s = "Out of ammo"
							DrawText(s, x * sizeGrid - (gfx.GetCachedFontWidth(s) / 2), y * sizeGrid + gfx.GetCachedFontHeight(b.weapon.name) + 5)
						End If
					ElseIf p.isModule = 1 And b.variant = 8 Then
						If ms > selectedVessel.lastEMP + TWeaponClass.EMPRecharge Then buttons.AddButtonL("Discharge", "EMP", 5, (x * sizeGrid) + spX100 + gridLeft, (y * sizeGrid) + spY + gridTop + 5, 100 ,"DischargeEMP")	
					ElseIf p.isLauncher = 1 Then
						SetColor(255, 255, 255)
						s = b.numberRemaining + " fighters"
						SetColor(255, 255, 0)
						DrawText(s, x * sizeGrid - (gfx.GetCachedFontWidth(s) / 2), y * sizeGrid + 5)
						If selectedVessel.shape[x + firstX, y + firstY].numberRemaining > 0 Then
							Local found:Int = 0
							For Local xy:TXY = EachIn selectedVessel.launching
								If xy.x = x + firstX And xy.y = y + firstY Then
									found = 1
									Exit
								End If
							Next 
							If found = 0 Then buttons.AddButtonMS("Scramble", 5, (x * sizeGrid) + spX100 + gridLeft, (y * sizeGrid) + spY + gridTop + 25, 100 ,"LaunchFighters:" + String(x + firstX) + "," + String(y + firstY))	
						End If
					End If
				End If
			Next
		Next
		?debug
   			TProfiler.Leave("Game::UIShapes")
  		?
	End Method
	
	Method Clear(selected:Int = 0)
		?debug
   			TProfiler.Enter("Game::Clear")
  		?
		showOptions = 0
		g.moveOrderStep = 0
		g.pursueOrderStep = 0
		g.fireTargetStep = 0
		g.headingOrderStep = 0
		g.autoBow = 0
		g.autoStern = 0
		g.autoStarboard = 0
		g.autoPort = 0
		overview = 0
		?debug
   			TProfiler.Leave("Game::Clear")
  		?
	End Method

	Method CheckOrderInput(click:String, ms:Long)
		?debug
   			TProfiler.Enter("Game::CheckOrderInput")
  		?
		If KeyHit(KEY_H) Or click = "HeadingOrder" And selectedVessel <> Null Then
			Clear()
			g.headingOrderStep = 1
		ElseIf KeyHit(KEY_M) Or click = "MoveOrder" And selectedVessel <> Null Then 
			Clear()
			g.moveOrderStep = 1
		ElseIf KeyHit(KEY_E) Or click = "EscortOrder" And selectedVessel <> Null Then
			Clear()
			g.removeOrderWhenArrived = 1
			g.pursueOrderStep = 1
			g.pursueIsEscort = 1
		ElseIf KeyHit(KEY_P) Or click = "ApproachOrder" And selectedVessel <> Null Then
			Clear()
			g.removeOrderWhenArrived = 1
			g.pursueOrderStep = 1
			g.pursueIsEscort = 0
		ElseIf click = "RemoveOrderWhenArrived" Then
			g.removeOrderWhenArrived = g.removeOrderWhenArrived ~ 1
		ElseIf click = "Pursue25000m" Then
			g.pursueOrderStep = 2
			g.pursueDistance = 25000
		ElseIf click = "Pursue10000m" Then
			g.pursueOrderStep = 2
			g.pursueDistance = 10000
		ElseIf click = "Pursue5000m" Then
			g.pursueOrderStep = 2
			g.pursueDistance = 5000
		ElseIf click = "Pursue2500m" Then
			g.pursueOrderStep = 2
			g.pursueDistance = 2500
		ElseIf KeyHit(KEY_F) Or click = "FireOrder" Then
			Clear()
			g.rateFull = 0
			g.rateHalf = 0
			g.rateQuarter = 0
			g.rateHarassing = 0
			g.rateWeapon = 1
			g.fireTargetStep = 1
		End If
		If click = "FullRateOn" Then
			g.rateFull = 1
			g.rateHalf = 0
			g.rateQuarter = 0
			g.rateHarassing = 0
			g.rateWeapon = 0
		ElseIf click = "HalfRateOn" Then
			g.rateFull = 0
			g.rateHalf = 1
			g.rateQuarter = 0
			g.rateHarassing = 0
			g.rateWeapon = 0
		ElseIf click = "QuarterRateOn" Then
			g.rateFull = 0
			g.rateHalf = 0
			g.rateQuarter = 1
			g.rateHarassing = 0
			g.rateWeapon = 0
		ElseIf click = "HarassingOn" Then
			g.rateFull = 0
			g.rateHalf = 0
			g.rateQuarter = 0
			g.rateHarassing = 1
			g.rateWeapon = 0
		ElseIf click = "WeaponRateOn" Then
			g.rateFull = 0
			g.rateHalf = 0
			g.rateQuarter = 0
			g.rateHarassing = 0
			g.rateWeapon = 1
		ElseIf click = "AutoBowOn" Then
			g.autoBow = 1
			g.autoStern = 0
			g.autoStarboard = 0
			g.autoPort = 0
		ElseIf click = "AutoPortOn" Then
			g.autoBow = 0
			g.autoStern = 0
			g.autoStarboard = 0
			g.autoPort = 1
		ElseIf click = "AutoStarboardOn" Then
			g.autoBow = 0
			g.autoStern = 0
			g.autoStarboard = 1
			g.autoPort = 0
		ElseIf click = "AutoSternOn" Then
			g.autoBow = 0
			g.autoStern = 1
			g.autoStarboard = 0
			g.autoPort = 0
		ElseIf click = "AutoBowOff" Or click = "AutoPortOff" Or click = "AutoStarboardOff" Or click = "AutoSternOff" Then
			g.autoBow = 0
			g.autoStern = 0
			g.autoStarboard = 0
			g.autoPort = 0
		End If
		If KeyHit(KEY_L) Or click = "GunsOnly" Then
			g.fireChosen = "GunsOnly"
			If g.fireTargetStep = 1 Then g.fireTargetStep = 2 Else g.fireTargetStep = 2
		ElseIf KeyHit(KEY_I) Or click = "MissileOnly" Then
			g.fireChosen = "MissileOnly"
			If g.fireTargetStep = 1 Then g.fireTargetStep = 2 Else g.fireTargetStep = 2
		ElseIf KeyHit(KEY_A) Or click = "AllWeapons" Then
			g.fireChosen = "AllWeapons"
			If g.fireTargetStep = 1 Then g.fireTargetStep = 2 Else g.fireTargetStep = 2
		End If
		If click = "HoldOrders" And selectedVessel <> Null Then
			selectedVessel.HoldOrders()
		End If
		If click = "UnholdOrders" And selectedVessel <> Null Then
			selectedVessel.UnholdOrders(ms)
		End If
		If Mid(click, 1, 11) = "CancelOrder" And selectedVessel <> Null Then
			Local i:Int = Int(Right(click, Len(click) - 12))
			selectedVessel.CancelOrder(i, g, ms)
		End If
		?debug
   			TProfiler.Leave("Game::CheckOrderInput")
  		?
	End Method

	Method ShowOptionsWindow(gfx:TGFX)
		?debug
   			TProfiler.Enter("Game::ShowOptionsWindow")
  		?
		Const h:Int = 400
		SetColor(0, 0, 0)
		SetAlpha(0.75)
		DrawRect(0, 0, gfx.width, gfx.height)
		SetColor(0, 0, 160)
		SetAlpha(1.0)
		DrawRect((gfx.width - 400) / 2, (gfx.height / 2) - (h / 2), 400, h)
		SetColor(0, 0, 32)
		SetAlpha(1.0)
		DrawRect(((gfx.width - 400) / 2) + 2, ((gfx.height / 2.0) - (h / 2)) + 2, 400 - 4, h - 4)

		' Title
		gfx.SetFontSize(TGFX.FontXXLarge)	
		SetAlpha(1.0)
		SetColor(255, 255, 255)
		DrawText("Options", Int((gfx.width / 2) - (gfx.GetCachedFontWidth("Options") / 2.0)), (gfx.height / 2) - (h / 2) + 25)

		' Bottom
		SetColor(0, 255, 0)
		gfx.SetFontSize(TGFX.FontLarge)
		Local s:String = "(Escape to Close)"
		DrawText(s, Int((gfx.width / 2) - (gfx.GetCachedFontWidth(s) / 2.0)), (gfx.height / 2) + (h / 2) - 35)
		?debug
   			TProfiler.Leave("Game::ShowOptionsWindow")
  		?
	End Method
	
	Method ScrollAction(gfx:TGFX)	
		?debug
   			TProfiler.Enter("Game::ScrollAction")
  		?
		If scrolling = 1 Then
			Local dX:Int = MouseX() - prevX					
			Local dY:Int = MouseY() - prevY
			g.CanScroll(gfx, dX, dY, 0)
			origX :- dX
			origY :- dY
			gd.sf.panCycle(dX, dY)
		Else
			scrolling = 1
		End If
		prevX = MouseX()
		prevY = MouseY()
		?debug
   			TProfiler.Leave("Game::ScrollAction")
  		?
	End Method

	Method HoverEntity:TGameEntity(gd:TGameData, gfx:TGFX)
		?debug
   			TProfiler.Enter("Game::HoverEntity")
  		?
		Local tX:Double, tY:Double
		GetPosition(gfx, tX, tY)

		Local dist:Double = 9999999
		Local v:TGameEntity = Null
		For Local player:Int = 0 To 1
			For Local ge:TGameEntity = EachIn g.entities[player]
				If Abs(tX - ge.x) < (gd.SnapSize * g.scale) And Abs(tY - ge.y) < (gd.SnapSize * g.scale) Then
					Local m:Double = Min(Abs(tX - ge.x), Abs(tY - ge.y))
					If m < dist Then
						If (ge.owningPlayerNo = 0 And ge.computerControlled = 0) Or g.allowAIEnemySelection = 1 Or g.pursueOrderStep = 2 Or g.fireTargetStep = 2 Then
							v = ge
							dist = m
							gfx.pointer = 1
						Else
							gfx.pointer = 2
						End If
					End If
				End If
			Next
		Next 	
		?debug
   			TProfiler.Leave("Game::HoverEntity")
  		?
		Return v
	End Method
	
	Method SelectEntity(gd:TGameData, gfx:TGFX, ms:Long)
		?debug
   			TProfiler.Enter("Game::SelectEntity")
  		?
		Local tX:Double, tY:Double
		GetPosition(gfx, tX, tY)
		
		If g.moveOrderStep = 1 And selectedVessel <> Null Then
			selectedVessel.AddMoveOrder(tX, tY, 1.0, ms)
			g.moveOrderStep  = 0
			?debug
   				TProfiler.Leave("Game::SelectEntity")
		  	?
			Return
		ElseIf g.headingOrderStep = 1 And selectedVessel <> Null Then
			selectedVessel.AddHeadingOrder(tX, tY, ms)
			g.headingOrderStep  = 0
			?debug
   				TProfiler.Leave("Game::SelectEntity")
		  	?
			Return
		End If

		' Selected?
		Local dist:Double = 9999999
		Local selected:Int = 0
		Local selectedVesselSaved:TGameEntity = selectedVessel
		selectedVessel = Null
		For Local player:Int = 0 To 1
			For Local ge:TGameEntity = EachIn g.entities[player]
				If Abs(tX - ge.x) < (gd.SnapSize * g.scale) And Abs(tY - ge.y) < (gd.SnapSize * g.scale) Then
					Local m:Double = Min(Abs(tX - ge.x), Abs(tY - ge.y))
					If m < dist Then
						selected = 1
						selectedVessel = ge
						dist = m
						gfx.pointer = 1
					End If
				End If
			Next
		Next 

		If g.fireTargetStep = 2 Then
			Local level:Int = 0
			Select g.fireChosen
			Case "GunsOnly"
				level = 0
			Case "MissileOnly"
				level = 1
			Case "AllWeapons"
				level = 2
			End Select
			Local autoDirection:Int = -1 
			If g.autoBow = 1 Then autoDirection = 0
			If g.autoPort = 1 Then autoDirection = 1
			If g.autoStarboard = 1 Then autoDirection = 2
			If g.autoStern = 1 Then autoDirection = 3
			Local rate:Double = 1.0
			If g.rateWeapon = 1 Then rate = -1.0
			If g.rateFull = 1 Then rate = 1.0
			If g.rateHalf = 1 Then rate = 0.5
			If g.rateQuarter = 1 Then rate = 0.25
			If g.rateHarassing = 1 Then rate = 0.1
			If selectedVessel = Null Then
				If level = 1 Then
				Else
					selectedVesselSaved.AddFireOrderXY(tX, tY, level, autoDirection, selectedVesselSaved.owningPlayerNo, ms, rate)
					g.fireTargetStep = 0
				End If
			Else
				selectedVesselSaved.AddFireOrder(selectedVessel, level, autoDirection, selectedVessel.owningPlayerNo, ms, rate)
				g.fireTargetStep = 0
				selectedVessel = Null
			End If
		ElseIf g.pursueOrderStep = 2 Then
			If selectedVessel <> Null And selectedVesselSaved <> Null Then
				If g.pursueIsEscort = 0 Then
					selectedVesselSaved.AddPursueOrder(selectedVessel, g.pursueDistance, 0, ms, 0, g.removeOrderWhenArrived)
				Else
					Local escortAngle:Double
					Select selectedVessel.escortCount
					Case 0
						escortAngle = -30
					Case 1
						escortAngle = 30
					Case 2
						escortAngle = -150
					Case 3
						escortAngle = 150
					Case 4
						escortAngle = -60
					Case 5
						escortAngle = 60
					Case 4
						escortAngle = -120
					Case 5
						escortAngle = 120
					Default
						escortAngle = 180
					End Select
					selectedVessel.escortCount :+ 1	
					selectedVesselSaved.AddPursueOrder(selectedVessel, g.pursueDistance, escortAngle, ms, 0, 0)
				End If
				g.pursueOrderStep = 0
			End If
			selectedVessel = Null
		Else
			Clear(0)
		End If	
		If selectedVessel <> Null And (selectedVessel.owningPlayerNo <> 0 Or selectedVessel.computerControlled = 1) And g.allowAIEnemySelection = 0 Then selectedVessel = Null
		If selectedVessel = Null Then selectedVessel = selectedVesselSaved
		?debug
   			TProfiler.Leave("Game::SelectEntity")
  		?
	End Method

	Method GetPosition(gfx:TGFX, tX:Double Var, tY:Double Var)
		?debug
   			TProfiler.Enter("Game::GetPosition")
  		?
		tX = (MouseX() - g.mapViewCentreX) * g.scale
		tY = (g.mapViewCentreY - MouseY()) * g.scale
		tX :+ g.centreX
		tY :+ g.centreY		
		?debug
   			TProfiler.Leave("Game::GetPosition")
  		?
	End Method

	Method BuildButtons(gfx:TGFX, gd:TGameData)
		?debug
   			TProfiler.Enter("Game::BuildButtons")
  		?
		gd.buttons.ClearButtons()
		If showOptions = 1 Then
			Local b:Int = (gfx.height / 2.0) - 100
			Local m:Int = (gfx.width / 2) - 150
			gd.buttons.AddButtonBordered("Show Missile", "Trails", 4, m, b + (50 * 0), 300, "ShowTrails", g.showTrails = 0)
			gd.buttons.AddButtonBordered("Show Missile", "Tracking", 4, m, b + (50 * 1), 300, "ShowTracking", g.showMissileTargets = 0)
			gd.buttons.AddButtonBordered("Colour Missile", "& Projectiles", 4, m, b + (50 * 2), 300, "ColourCoded", g.bulletsInColour = 0)
			gd.buttons.AddButtonBordered("Show", "Messages", 4, m, b + (50 * 3), 300, "ShowMessages", g.showMessages = 0)
			gd.buttons.AddButtonBordered("Detailed", "Messages", 4, m, b + (50 * 4), 300, "ShowDetailedMessages", g.optionShowAllMessages = 0)
		End If
		?debug
	   		TProfiler.Leave("Game::BuildButtons")
  		?
	End Method
		
	Method DamageVesselImpact(geTarget:TGameEntity, damage:Double, ms:Long)
		?debug
   			TProfiler.Enter("Game::DamageVesselImpact")
  		?
		If geTarget.shieldRemaining > 0 Then
			If geTarget.shieldRemaining < damage Then
				damage :- geTarget.shieldRemaining
				geTarget.shieldRemaining = 0
			Else
				geTarget.shieldRemaining :- damage
				damage = 0
			End If
		End If
								
		' Damage remaining, take off armour
		geTarget.armourRemaining :- damage

		If geTarget.armourRemaining < 0 Then
			Destroy(geTarget, "was destroyed in a collision.", ms)
		End If	
		?debug
   			TProfiler.Leave("Game::DamageVesselImpact")
  		?
	End Method	
		
	Method FireHalo(ms:Long)
		?debug
   			TProfiler.Enter("Game::FireHalo")
  		?
		For Local geTarget:TGameEntity = EachIn g.entities[selectedVessel.owningPlayerNo ~ 1]
			Local dist:Double = DistanceBetweenPoints(geTarget.x, geTarget.y, selectedVessel.x, selectedVessel.y)
			If dist < TWeaponClass.EMPRadius Then
				geTarget.electricActive = ms
				Local damage:Double = TWeaponClass.EMPDamage * (1.0 - (dist / TWeaponClass.EMPRadius))
				Local systemsDamage:Double = 1.0 - (dist / TWeaponClass.EMPRadius)
				
				' Shield damage
				geTarget.shieldRemaining :- damage
				If geTarget.shieldRemaining < 0 Then geTarget.shieldRemaining = 0
				If geTarget.shieldRemaining > 0 Then systemsDamage :/ 2.0

				' Go through modules, missiles and guns doing random damage
				For Local x:TXY = EachIn geTarget.vessel.modules
					If geTarget.condition[x.x, x.y] > 0.0 And RndFloat() < systemsDamage Then DamageSystem(x, systemsDamage, geTarget)
				Next
				For Local x:TXY = EachIn geTarget.vessel.thrusters
					If geTarget.condition[x.x, x.y] > 0.0 And RndFloat() < systemsDamage Then DamageSystem(x, systemsDamage, geTarget)
				Next
				For Local x:TXY = EachIn geTarget.vessel.missiles
					If geTarget.condition[x.x, x.y] > 0.0 And RndFloat() < systemsDamage Then DamageSystem(x, systemsDamage, geTarget)
				Next
				For Local x:TXY = EachIn geTarget.vessel.guns
					If geTarget.condition[x.x, x.y] > 0.0 And RndFloat() < systemsDamage Then DamageSystem(x, systemsDamage, geTarget)
				Next
					
				' Apply any damage
				If geTarget.ApplyDamage(gd, g, ms) = 1 Then
					Destroy(geTarget, "self-destructed.", ms)
				End If
			End If
		Next 
		?debug
   			TProfiler.Leave("Game::FireHalo")
  		?
	End Method	
		
	Method Scripts(t:Long, e:TList, reserve:Int, ms:Long)
		?debug
   			TProfiler.Enter("Game::Scripts")
  		?
		For Local ge:TGameEntity = EachIn e
			For Local sc:TScriptItem = EachIn ge.script
				If t >= sc.time Then
					Select sc.t
					Case TScriptItem.ScriptJumpIn
						If sc.stage = 0 Then
							ListAddFirst(g.jumpPoints, TXYEntity.Create(ge.x, ge.y, ms, ge.collisionSize))
							sc.stage = 1
						ElseIf sc.stage = 1 And t > (sc.time + 3.0) Then
							ListAddFirst(g.entities[ge.owningPlayerNo], ge)
							ListRemove(g.entitiesReserve, ge)
							ge.lastJump = ms
							ListRemove(ge.script, sc)
						End If
					Case TScriptItem.ScriptJumpOut
						If sc.stage = 0 Then
							' Slow down
							If ge.currentSpeed > 0 Then
								ge.currentSpeed = 0
								ge.speed = 0
								ge.targetSpeed = 0
							Else
								ListAddFirst(g.jumpPoints, TXYEntity.Create(ge.x, ge.y, ms, ge.collisionSize))
								sc.stage = 1
							End If
						ElseIf sc.stage = 1 And (t > sc.time + 3.0) Then
							ListAddFirst(g.entitiesReserve, ge)
							ListRemove(g.entities[ge.owningPlayerNo], ge)
							ListRemove(ge.script, sc)
						End If
					End Select
				End If
			Next
		Next
		?debug
   			TProfiler.Leave("Game::Scripts")
  		?
	End Method	
		
	Method LaunchFighters(ms:Long)
		?debug
   			TProfiler.Enter("Game::LaunchFighters")
  		?
		For Local player:Int = 0 To 1
			For Local ge:TGameEntity = EachIn g.entities[player]
				For Local xy:TXY = EachIn ge.launching
					Local lt:TBlock = ge.shape[xy.x, xy.y]
					If lt.fired < ms Then
						lt.numberRemaining :- 1
						lt.fired = ms + 150
						
						' Offset
						Local mX:Double, mY:Double
						Local ran:Int = 0
						If Rnd() > 0.5 Then ran = 1
						Select lt.rot
						Case 0
							mX = (xy.x - ge.centreX) * TGameEntity.SectionSizeX
							If ran = 0 Then 
								mY = (xy.y - ge.centreY + 0.5) * TGameEntity.SectionSizeY
							Else
								mY = (xy.y - ge.centreY - 0.5) * TGameEntity.SectionSizeY
							End If
						Case 1
							If ran = 0 Then 
								mX = (xy.x - ge.centreX - 0.5) * TGameEntity.SectionSizeX
							Else
								mX = (xy.x - ge.centreX + 0.5) * TGameEntity.SectionSizeX
							End If
							mY = (xy.y - ge.centreY) * TGameEntity.SectionSizeY
						Case 2 
							mX = (xy.x - ge.centreX) * TGameEntity.SectionSizeX
							If ran = 0 Then 
								mY = (xy.y - ge.centreY - 0.5) * TGameEntity.SectionSizeY
							Else
								mY = (xy.y - ge.centreY + 0.5) * TGameEntity.SectionSizeY
							End If
						Case 3	
							If ran = 0 Then 
								mX = (xy.x - ge.centreX + 0.5) * TGameEntity.SectionSizeX
							Else
								mX = (xy.x - ge.centreX - 0.5) * TGameEntity.SectionSizeX
							End If
							mY = (xy.y - ge.centreY) * TGameEntity.SectionSizeY
						End Select
						RotateAroundOrigin(mX, mY, ge.angle + 90)

						' Work out angle, with randomness
						Local ra:Double = Rnd(0.0, 30.0) - 15.0
						ra = 0
						Local tubeAngle:Double = lt.TubeAngle(ge.angle + ra)
						If ran = 0 Then tubeAngle :- 180

						Local nge:TGameEntity = TGameEntity.CreateFighter(g.entityID, ge.owningPlayerNo, g.fighter, ge.x + mX, ge.y - mY, tubeAngle, gd.weapons, ms)
						nge.carrier = ge
						ListAddFirst(g.entities[nge.owningPlayerNo], nge)
						g.entityID :+ 1
						
						' Empty?
						If ge.shape[xy.x, xy.y].numberRemaining = 0 Then
							ListRemove(ge.launching, xy)
						End If
					End If
				Next
			Next
		Next
		?debug
   			TProfiler.Leave("Game::LaunchFighters")
  		?
	End Method	
		
	Method Animate(timeSeconds:Float, ms:Long)
		?debug
   			TProfiler.Enter("Game::Animate")
  		?

		' Clear targets
		For Local player:Int = 0 To 1
			For Local ge:TGameEntity = EachIn g.entities[player]
				ge.targetedCount = 0
			Next
		Next
		
		' Fighters
		LaunchFighters(ms)
		
		' Script
		Local t:Double = ms / 1000
		Scripts(t, g.entities[0], 0, ms)
		Scripts(t, g.entities[1], 0, ms)
		Scripts(t, g.entitiesReserve, 1, ms)
		
		' Animate
		For Local ge:TGameScenery = EachIn g.entitiesObjects
			ge.Animate(timeSeconds)
		Next
		For Local ge:TGameEntity = EachIn g.entitiesDead
			ge.AnimateSimple(timeSeconds, g, ms, gd)
		Next
		For Local player:Int = 0 To 1
			For Local ge:TGameEntity = EachIn g.entities[player]

				' Set targets, so AI can gang up
				For Local o:TOrder = EachIn ge.orders
					If o.t = OrderFire And o.target <> Null Then
						o.target.targetedCount :+ 1
					End If
				Next

				' Returning to carrier
				If ge.vessel.fighter = 1 And ge.returningToCarrier = 1 And DistanceIsLess(ge.x, ge.y, ge.carrier.x, ge.carrier.y, 50) Then
					For Local xy:TXY = EachIn ge.carrier.vessel.launchers
						If Not ge.carrier.launching.Contains(xy) Then
							Local lt:TBlock = ge.carrier.shape[xy.x, xy.y]
							If lt.numberRemaining < TGameEntity.NumberFighters Then
								lt.numberRemaining :+ 1
								ListRemove(g.entities[ge.owningPlayerNo], ge)
								Exit
							End If
						End If
					Next
				End If

				' EMP?
				If ge.haloActive > 0 And ms > ge.haloActive + 1500 Then
					ge.haloActive = 0
				End If
				
				' Electric?
				If ge.electricActive > 0 And ms > ge.electricActive + 1500 Then
					ge.electricActive = 0
				End If				

				' Have we left the game zone?
				If ge.x <= -(g.worldSizeX / 2) Or ge.x >= (g.worldSizeX / 2) Or ge.y <= -(g.worldSizeY / 2) Or ge.y >= (g.worldSizeY / 2) Then
					ListRemove(g.entities[ge.owningPlayerNo], ge)
				End If

				' Create list of targets
				ge.targetsWithinRangeCollision = CreateList()
				ge.targetsWithinRange250 = CreateList()
				ge.targetsWithinRange500 = CreateList()
				ge.targetsWithinRange2500 = CreateList()
				ge.targetsWithinRange5000 = CreateList()
				ge.targetsWithinRange10000 = CreateList()
				ge.targetsWithinRange15000 = CreateList()
				ge.targetsWithinRange30000 = CreateList()
				For Local geT:TGameEntity = EachIn g.entities[player ~ 1]
					Local dist:Double = DistanceBetweenPoints(ge.x, ge.y, geT.x, geT.y)
					If Not ge.CanSeeTarget(geT) Then Continue
					If dist < ge.collisionSize Then ListAddFirst(ge.targetsWithinRangeCollision, geT)
					If dist <= 250 Then ListAddFirst(ge.targetsWithinRange250, geT)
					If dist <= 500 Then ListAddFirst(ge.targetsWithinRange500, geT)
					If dist <= 2500 Then ListAddFirst(ge.targetsWithinRange2500, geT)
					If dist <= 5000 Then ListAddFirst(ge.targetsWithinRange5000, geT)
					If dist <= 10000 Then ListAddFirst(ge.targetsWithinRange10000, geT)
					If dist <= 15000 Then ListAddFirst(ge.targetsWithinRange15000, geT)
					If dist <= 30000 Then ListAddFirst(ge.targetsWithinRange30000, geT)
				Next

				ge.Animate(timeSeconds, g, ms, gd)
			Next
			For Local ge:TGameEntity = EachIn g.entitiesProjectiles[player]

				' Create list of targets
				ge.targetsWithinRangeCollision = CreateList()
				ge.targetsWithinRange250 = CreateList()
				ge.targetsWithinRange500 = CreateList()
				ge.targetsWithinRange2500 = CreateList()
				ge.targetsWithinRange5000 = CreateList()
				ge.targetsWithinRange10000 = CreateList()
				ge.targetsWithinRange15000 = CreateList()
				ge.targetsWithinRange30000 = CreateList()
				If ge.w.defensive = 1 Then
					For Local geT:TGameEntity = EachIn g.entitiesProjectiles[player ~ 1]
						Local dist:Double = DistanceBetweenPoints(ge.x, ge.y, geT.x, geT.y)
						If Not ge.CanSeeTarget(geT) Then Continue
						If dist < ge.w.hitRadius Then ListAddFirst(ge.targetsWithinRangeCollision, geT)
						If ge.w.maxRange >= 250 And dist <= 250 Then ListAddFirst(ge.targetsWithinRange250, geT)
						If ge.w.maxRange >= 500 And dist <= 500 Then ListAddFirst(ge.targetsWithinRange500, geT)
						If ge.w.maxRange >= 2500 And dist <= 2500 Then ListAddFirst(ge.targetsWithinRange2500, geT)
						If ge.w.maxRange >= 5000 And dist <= 5000 Then ListAddFirst(ge.targetsWithinRange5000, geT)
						If ge.w.maxRange >= 10000 And dist <= 10000 Then ListAddFirst(ge.targetsWithinRange10000, geT)
						If ge.w.maxRange >= 15000 And dist <= 15000 Then ListAddFirst(ge.targetsWithinRange15000, geT)
						If ge.w.maxRange >= 30000 And dist <= 30000 Then ListAddFirst(ge.targetsWithinRange30000, geT)
					Next
				Else
					For Local geT:TGameEntity = EachIn g.entities[player ~ 1]
						Local dist:Double = DistanceBetweenPoints(ge.x, ge.y, geT.x, geT.y)
						If Not ge.CanSeeTarget(geT) Then Continue
						If dist < ge.w.hitRadius Then ListAddFirst(ge.targetsWithinRangeCollision, geT)
						If ge.w.maxRange >= 250 And dist <= 250 Then ListAddFirst(ge.targetsWithinRange250, geT)
						If ge.w.maxRange >= 500 And dist <= 500 Then ListAddFirst(ge.targetsWithinRange500, geT)
						If ge.w.maxRange >= 2500 And dist <= 2500 Then ListAddFirst(ge.targetsWithinRange2500, geT)
						If ge.w.maxRange >= 5000 And dist <= 5000 Then ListAddFirst(ge.targetsWithinRange5000, geT)
						If ge.w.maxRange >= 10000 And dist <= 10000 Then ListAddFirst(ge.targetsWithinRange10000, geT)
						If ge.w.maxRange >= 15000 And dist <= 15000 Then ListAddFirst(ge.targetsWithinRange15000, geT)
						If ge.w.maxRange >= 30000 And dist <= 30000 Then ListAddFirst(ge.targetsWithinRange30000, geT)
					Next
				End If
				
				' Have we left the game zone?
				If ge.x <= -(g.worldSizeX / 2) Or ge.x >= (g.worldSizeX / 2) Or ge.y <= -(g.worldSizeY / 2) Or ge.y >= (g.worldSizeY / 2) Then
					ListRemove(g.entitiesProjectiles[ge.owningPlayerNo], ge)
				End If
			Next
		Next

		' Remove dead
		For Local ge:TGameEntity = EachIn g.entitiesProjectilesDead
			If ms > ge.removeWhen Then ListRemove(g.entitiesProjectilesDead, ge) 
		Next
		For Local ge:TGameEntity = EachIn g.entitiesDead
			If ms > ge.removeWhen Then ListRemove(g.entitiesDead, ge) 
		Next
		
		' Vessel collisions
		For Local ge:TGameEntity = EachIn g.entities[0]
			If ge.vessel.fighter = 0 Then
				For Local geTarget:TGameEntity = EachIn ge.targetsWithinRangeCollision
					If geTarget.vessel.fighter = 0 Then
						DamageVesselImpact(ge, (geTarget.mass / 5) * timeSeconds, ms)
						DamageVesselImpact(geTarget, (ge.mass / 5) * timeSeconds, ms)
					End If
				Next
			End If
		Next
		
		' Missile/projectile impacts
		For Local player:Int = 0 To 1
			For Local ge:TGameEntity = EachIn g.entitiesProjectiles[player]
				Local htList:TList
		
				' Exceeded lifetime?
				If ge.distanceTravelled > ge.w.maxRange And RndDouble() < 0.025 * (ge.distanceTravelled / ge.w.maxRange) Then
					' Star pattern?
					If ge.w.starPattern = 1 Then
						ge.removeWhen = ms + 2500
						ge.died = ms
						ListAddFirst(g.entitiesProjectilesDead, ge)
						ListRemove(g.entitiesProjectiles[ge.owningPlayerNo], ge)
						For Local i:Int = 0 To Rand(5, 10)
							Local newA:Double = AdjustAngle(ge.angle + Rnd(0, 360.0))
							Local geN:TGameEntity = TGameEntity.CreateBullet(g.entityID, gd.pieces, ge.owningPlayerNo, g.shrapnel, ge.x, ge.y, newA, gd.weapons[TWeaponClass.fragmentID], ms)
							geN.speed :* (RndDouble() + 0.5)
							geN.targetSpeed = geN.speed
							geN.currentSpeed = geN.speed
							g.entityID :+ 1
							ListAddFirst(g.entitiesProjectiles[geN.owningPlayerNo], geN)
						Next
					Else
						ge.removeWhen = ms + 2500
						ge.died = ms
						ListAddFirst(g.entitiesProjectilesDead, ge)
						ListRemove(g.entitiesProjectiles[ge.owningPlayerNo], ge)
					End If
				Else
					ge.Animate(timeSeconds, g, ms, gd)
				End If
				
				' Who did we hit?
				If ge.vessel.ship = 0 And ge.w.defensive = 1 Then 
					htList = HitTestProjectile(ge)
				Else 
					htList = HitTestVessel(ge)
				End If
				
				Local d:Int = 0
				If htList.Count() > 0 Then
					Local dist:Double = DistanceBetweenPoints(g.centreX, g.centreY, ge.x, ge.y)	

					' Who is damaged?
					If ge.vessel.ship = 0 And ge.w.defensive = 1 Then 
						DamageTestProjectile(ge, ms, htList)
					Else 
						DamageTestVessel(ge, ms, d, htList)
					End If
					If d > 0 Then
						gd.sound.PlayLargeExplosionSound(0, ms, 1.0 / (dist / g.scale / 5000.0))
					Else
						gd.sound.PlayExplosionSound(0, ms, 1.0 / (dist / g.scale / 5000.0))
					End If
					
					' Star pattern?
					If ge.w.starPattern = 1 Then
						ge.removeWhen = ms + 2500
						ge.died = ms
						ListAddFirst(g.entitiesProjectilesDead, ge)
						ListRemove(g.entitiesProjectiles[ge.owningPlayerNo], ge)
						For Local i:Int = 0 To Rand(5, 10)
							Local newA:Double = AdjustAngle(ge.angle + Rnd(0, 360.0))
							Local geN:TGameEntity = TGameEntity.CreateBullet(g.entityID, gd.pieces, ge.owningPlayerNo, g.shrapnel, ge.x, ge.y, newA, gd.weapons[TWeaponClass.fragmentID], ms)
							geN.speed :* (RndDouble() + 0.5)
							geN.targetSpeed = geN.speed
							geN.currentSpeed = geN.speed
							g.entityID :+ 1
							ListAddFirst(g.entitiesProjectiles[geN.owningPlayerNo], geN)
						Next
					Else
						ge.removeWhen = ms + 2500
						ge.died = ms
						ListAddFirst(g.entitiesProjectilesDead, ge)
						ListRemove(g.entitiesProjectiles[ge.owningPlayerNo], ge)
					End If
				End If
			Next
		Next
		?debug
   			TProfiler.Leave("Game::Animate")
  		?
	End Method
	
	Method HitTestProjectile:TList(ge:TGameEntity)
		?debug
   			TProfiler.Enter("Game::HitTestProjectile")
  		?
		Local l:TList = CreateList()
		For Local geTarget:TGameEntity = EachIn ge.targetsWithinRange500
			If DistanceIsLess(ge.x, ge.y, geTarget.x, geTarget.y, geTarget.collisionSize + ge.w.hitRadius) Then 
				ListAddFirst(l, geTarget)
			End If
		Next
		?debug
   			TProfiler.Leave("Game::HitTestProjectile")
  		?
		Return l
	End Method
	
	Method HitTestVessel:TList(ge:TGameEntity)
		?debug
   			TProfiler.Enter("Game::HitTestVessel")
  		?
		Local l:TList = CreateList()
		For Local geTarget:TGameEntity = EachIn ge.targetsWithinRange500
			If DistanceIsLess(ge.x, ge.y, geTarget.x, geTarget.y, geTarget.collisionSize + ge.w.hitRadius) Then 
				
				If geTarget.vessel.fighter = 1 Then 
					ListAddFirst(l, geTarget)
				Else
					If ge.w.hitRadius = 0 Then 
						' Figure out where on the vessel we hit
						Local x:Int = ((ge.x - geTarget.x) / TGameEntity.SectionSizeX) + geTarget.centreX
						Local y:Int = ((geTarget.y - ge.y) / TGameEntity.SectionSizeY) + geTarget.centreY
						If x < 0 Or y < 0 Or x >= TVessel.MaxShapeX Or y >= TVessel.MaxShapeY Then Continue
						If geTarget.shape[x, y].piece > 0 Then
							ListAddFirst(l, geTarget)
						End If
					Else
						ListAddFirst(l, geTarget)
					End If
				End If
			End If
		Next
		?debug
   			TProfiler.Leave("Game::HitTestVessel")
  		?
		Return l
	End Method

	Method DamageSystem(x:TXY, m:Double, ge:TGameEntity)
		?debug
   			TProfiler.Enter("Game::DamageSystem")
  		?
		Local d:Double = (RndDouble() * m) * (RndDouble() * 3)
		ge.condition[x.x, x.y] :- d
		If ge.condition[x.x, x.y] < 0.0 Then
			ge.condition[x.x, x.y] = 0.0
			ge.onOff[x.x, x.y] = 0.0
		End If
		?debug
   			TProfiler.Leave("Game::DamageSystem")
  		?
	End Method

	Method DamageTestProjectile(ge:TGameEntity, ms:Long, lst:TList)
		?debug
   			TProfiler.Enter("Game::DamageTestProjectile")
  		?
		For Local geTarget:TGameEntity = EachIn lst
			ListRemove(g.entitiesProjectiles[geTarget.owningPlayerNo], geTarget)
		Next
		?debug
   			TProfiler.Leave("Game::DamageTestProjectile")
  		?
	End Method
	
	Method DamageTestVessel(ge:TGameEntity, ms:Long, destroyed:Int Var, lst:TList)
		?debug
   			TProfiler.Enter("Game::DamageTestVessel")
  		?
		Local paint:Int = 0
		destroyed = 0
		
		' Blast radius damage
		For Local geTarget:TGameEntity = EachIn lst
			Local dist:Double = DistanceBetweenPoints(ge.x, ge.y, geTarget.x, geTarget.y)			
			Local damage:Double = ge.w.damage * (1.0 - (dist / (geTarget.collisionSize + ge.w.blastRadius)))
			Local systemsDamage:Double = (damage / (geTarget.shield + geTarget.armour)) * 10.0
					
			' Shield?
			If ge.w.damageHullMultiplier = 1.0 Then 'Bypass shield
				Local lDamage:Double = damage * ge.w.damageShieldMultiplier
				If geTarget.shieldRemaining > 0 Then
					If geTarget.shieldRemaining < ldamage Then
						damage :- (geTarget.shieldRemaining / ge.w.damageShieldMultiplier)
						geTarget.shieldRemaining = 0
					Else
						geTarget.shieldRemaining :- ldamage
						damage = 0
					End If
				End If
			End If
								
			' Damage remaining, take off armour
			geTarget.armourRemaining :- (damage * ge.w.damageHullMultiplier)
						
			' Destroyed?
			If geTarget.armourRemaining < 0 Then
				destroyed :+ 1
				Destroy(geTarget, "was destroyed.", ms)
			Else
				If geTarget.lastAttack < (ms - TGameState.MessageRepeat) Then
					g.AddMessage("<" + geTarget.name + "> is under attack.", ms, geTarget.owningPlayerNo)
					geTarget.lastAttack = ms
				End If
	
				' If we have shield then damage is a lot less
				If geTarget.shieldRemaining > 0 Then systemsDamage :/ 2.0
				systemsDamage :* ge.w.damageSystemMultiplier
					
				' Go through modules, missiles and guns doing random damage
				For Local x:TXY = EachIn geTarget.vessel.modules
					Local b:TBlock = geTarget.shape[x.x, x.y]
						
					' Radar seeking do lots of radar damage
					If ge.w.radarSeeking = 1 And (b.variant = 4 Or b.variant = 5) And geTarget.onOff[x.x, x.y] = 1.0 Then 								
						geTarget.condition[x.x, x.y] :- (RndDouble()) + 0.25
						If geTarget.condition[x.x, x.y] < 0 Then geTarget.condition[x.x, x.y] = 0
					End If
					If geTarget.condition[x.x, x.y] > 0.0 And RndFloat() < systemsDamage Then DamageSystem(x, systemsDamage, geTarget)
				Next
				For Local x:TXY = EachIn geTarget.vessel.thrusters
					If geTarget.condition[x.x, x.y] > 0.0 And RndFloat() < systemsDamage Then DamageSystem(x, systemsDamage, geTarget)
				Next
				For Local x:TXY = EachIn geTarget.vessel.missiles
					If geTarget.condition[x.x, x.y] > 0.0 And RndFloat() < systemsDamage Then DamageSystem(x, systemsDamage, geTarget)
				Next
				For Local x:TXY = EachIn geTarget.vessel.guns
					If geTarget.condition[x.x, x.y] > 0.0 And RndFloat() < systemsDamage Then DamageSystem(x, systemsDamage, geTarget)
				Next
				
				' Apply any damage
				If geTarget.ApplyDamage(gd, g, ms) = 1 Then
					destroyed :+ 1
					Destroy(geTarget, "self-destructed.", ms)
				End If
				If ge.w.radarSeeking = 1 Then paint = 1
			End If
		Next
		If paint = 1 Then PaintTargets(ms)
		?debug
   			TProfiler.Leave("Game::DamageTestVessel")
  		?
	End Method
	
	Method Destroy(ge:TGameEntity, msg:String, ms:Long)
		?debug
   			TProfiler.Enter("Game::Destroy")
  		?
		ge.Destroy(gd, g, msg, ms, 1)
		If selectedVessel = ge Then selectedVessel = Null
		?debug
   			TProfiler.Leave("Game::Destroy")
  		?
	End Method

	Method PaintTargets(ms:Long)
		?debug
   			TProfiler.Enter("Game::PaintTargets")
  		?
		timeLastPainted = ms
		radar.Clear()
		radar.CalcRadar()
		radar.SetVisible(0)
		?debug
   			TProfiler.Leave("Game::PaintTargets")
  		?
	End Method
	
End Type
