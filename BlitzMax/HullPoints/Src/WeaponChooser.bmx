SuperStrict
Import "Helper.bmx"
Import "GameData.bmx"
Import "GFX.bmx"
Import "Piece.bmx"
Import "Starfield.bmx"
Import "WeaponClass.bmx"

Type TWeaponChooser
	Const zoom:Int = 48, spacer:Int = 12
	Field x:Int, y:Int, width:Int, height:Int, title:String, text:String

	Function Create:TWeaponChooser(x:Int, y:Int, text:String, title:String)
		Local o:TWeaponChooser = New TWeaponChooser
		o.x = x
		o.y = y
		o.width = 850
		o.title = title
		o.text = text
		Return o
	End Function
	
	Method Render:Int(gfx:TGFX, ret:Int, gd:TGameData, vessel:TVessel)
		SetOrigin(0, 0)
		Local numPerPage:Int = 6
		Local bs:Int = ((zoom + spacer) * numPerPage)
		height = 150 + bs
		Local top:Int = (gfx.height - height) / 2
		If ret = 1 Then
			SetColor(0, 0, 0)
			SetAlpha(0.75)
			DrawRect(0, 0, gfx.width, gfx.height)
			SetColor(0, 0, 160)
			SetAlpha(1.0)
			DrawRect((gfx.width - width) / 2, top, width, height)
			SetColor(0, 0, 64)
			DrawRect(((gfx.width - width) / 2) + 2, top + 2, width - 4, height - 4)
		End If
		Repeat
			If ret = 0 Then gd.sf.Render(1.0)
			SetOrigin(0, 0)
			gd.buttons.ClearButtons()

			' Title
			gfx.SetFontSize(TGFX.FontXXLarge)
			SetAlpha(1.0)
			SetColor(255, 255, 255)
			DrawText(title, Int((gfx.width / 2) - (gfx.GetCachedFontWidth(title) / 2.0)), top + 25)

			' Preferences
			SetColor(255, 255, 255)
			gfx.SetFontSize(TGFX.FontXLarge)
			DrawText("Preference 1", (gfx.width / 2) - (width / 2.0) + 30, top + 120)
			gfx.SetFontSize(TGFX.FontXLarge)
			DrawText("Preference 2", (gfx.width / 2) - (width / 2.0) + 30, top + 220)
			gfx.SetFontSize(TGFX.FontXLarge)
			DrawText("Preference 3", (gfx.width / 2) - (width / 2.0) + 30, top + 320)
			
			Local b:TBlock = vessel.shapeV[x, y]
			Local p:TPiece = gd.pieces[b.piece]
			
			' Default weapons?
			If vessel.shapeV[x, y].preferredAmmo1V = - 1 Then
				ShowWeapon(gd, p.isMissile, gfx, Null, 0, (gfx.width / 2) - (width / 2.0) + 30, top + 160, vessel) 
			Else
				ShowWeapon(gd, p.isMissile, gfx, gd.weapons[vessel.shapeV[x, y].preferredAmmo1V], 0, (gfx.width / 2) - (width / 2.0) + 30, top + 160, vessel) 
			End If
			If vessel.shapeV[x, y].preferredAmmo2V = - 1 Then
				ShowWeapon(gd, p.isMissile, gfx, Null, 1, (gfx.width / 2) - (width / 2.0) + 30, top + 260, vessel) 
			Else
				ShowWeapon(gd, p.isMissile, gfx, gd.weapons[vessel.shapeV[x, y].preferredAmmo1V], 1, (gfx.width / 2) - (width / 2.0) + 30, top + 260, vessel) 
			End If
			If vessel.shapeV[x, y].preferredAmmo3V = - 1 Then
				ShowWeapon(gd, p.isMissile, gfx, Null, 2, (gfx.width / 2) - (width / 2.0) + 30, top + 360, vessel) 
			Else
				ShowWeapon(gd, p.isMissile, gfx, gd.weapons[vessel.shapeV[x, y].preferredAmmo1V], 2, (gfx.width / 2) - (width / 2.0) + 30, top + 360, vessel) 
			End If
		
			' Auto fire rate
			Local x1:Int = (gfx.width / 2) - 325
			gd.buttons.AddButtonL("Full", "Auto", 4, x1, top + 410, 100, "AutoFull", vessel.shapeV[x, y].autoFire = 1.0)
			gd.buttons.AddButtonL("Half", "Auto", 4, x1 + 100, top + 410, 100, "AutoHalf", vessel.shapeV[x, y].autoFire = 0.5)
			gd.buttons.AddButtonL("Quarter", "Auto", 4, x1 + 200, top + 410, 100, "AutoQuarter", vessel.shapeV[x, y].autoFire = 0.25)
			gd.buttons.AddButtonL("Harassing", "Auto", 4, x1 + 300, top + 410, 100, "AutoHarassing", vessel.shapeV[x, y].autoFire = 0.1)
			gd.buttons.AddButtonL("Manual", "Only", 2, x1 + 400, top + 410, 100, "Manual", vessel.shapeV[x, y].autoFire = 0.0)
			gd.buttons.AddButtonL("Strafing", "Fire", 3, x1 + 550, top + 410, 100, "Strafe", vessel.shapeV[x, y].strafe = 0.0)

			' Message
			SetColor(0, 255, 0)
			gfx.SetFontSize(TGFX.FontLarge)
			Local s:String = "(Return to accept, Esc To cancel)"
			DrawText(s, Int((gfx.width / 2) - (gfx.GetCachedFontWidth(s) / 2.0)), top + height - 35)
			If ret = 0 Then
				gfx.UIScanlines()
				Flip
				PollSystem()
				gd.sf.Cycle()
			End If
			SetOrigin(0, 0)
			If MouseHit(1) Then gd.buttons.CheckClick(MouseX(), MouseY())
			Local click:String = gd.buttons.Clicked()
			If click = "AutoFull" Then
				vessel.shapeV[x, y].autoFire = 1.0
			ElseIf click = "AutoHalf" Then
				vessel.shapeV[x, y].autoFire = 0.5
			ElseIf click = "AutoQuarter" Then
				vessel.shapeV[x, y].autoFire = 0.25
			ElseIf click = "AutoHarassing" Then
				vessel.shapeV[x, y].autoFire = 0.1
			ElseIf click = "Manual" Then
				vessel.shapeV[x, y].autoFire = 0.0
			ElseIf click = "Strafe" Then
				vessel.shapeV[x, y].strafe = vessel.shapeV[x, y].strafe ~ 1
			ElseIf Left(click, 15) = "PreviousMissile" Then
				Local i:Int = Int(Right(click, 1))
				If i = 0 And vessel.shapeV[x, y].preferredAmmo1V = -1 Or vessel.shapeV[x, y].preferredAmmo1V = TWeaponClass.DefaultMissile Then Continue
				If i = 1 And vessel.shapeV[x, y].preferredAmmo2V = -1 Or vessel.shapeV[x, y].preferredAmmo2V = TWeaponClass.DefaultMissile Then Continue
				If i = 2 And vessel.shapeV[x, y].preferredAmmo3V = -1 Or vessel.shapeV[x, y].preferredAmmo3V = TWeaponClass.DefaultMissile Then Continue
				If i = 0 Then vessel.shapeV[x, y].preferredAmmo1V :- 1
				If i = 1 Then vessel.shapeV[x, y].preferredAmmo2V :- 1
				If i = 2 Then vessel.shapeV[x, y].preferredAmmo3V :- 1
			ElseIf Left(click, 14) = "PreviousBullet" Then
				Local i:Int = Int(Right(click, 1))
				If i = 0 And vessel.shapeV[x, y].preferredAmmo1V = -1 Or vessel.shapeV[x, y].preferredAmmo1V = TWeaponClass.DefaultBullet Then Continue
				If i = 1 And vessel.shapeV[x, y].preferredAmmo2V = -1 Or vessel.shapeV[x, y].preferredAmmo2V = TWeaponClass.DefaultBullet Then Continue
				If i = 2 And vessel.shapeV[x, y].preferredAmmo3V = -1 Or vessel.shapeV[x, y].preferredAmmo3V = TWeaponClass.DefaultBullet Then Continue
				If i = 0 Then vessel.shapeV[x, y].preferredAmmo1V :- 1
				If i = 1 Then vessel.shapeV[x, y].preferredAmmo2V :- 1
				If i = 2 Then vessel.shapeV[x, y].preferredAmmo3V :- 1
			ElseIf Left(click, 11) = "NextMissile" Then
				Local i:Int = Int(Right(click, 1))
				If i = 0 And vessel.shapeV[x, y].preferredAmmo1V = TWeaponClass.LastMissile Then Return -1
				If i = 1 And vessel.shapeV[x, y].preferredAmmo2V = TWeaponClass.LastMissile Then Return -1
				If i = 2 And vessel.shapeV[x, y].preferredAmmo3V = TWeaponClass.LastMissile Then Return -1
				If i = 0 And vessel.shapeV[x, y].preferredAmmo1V = -1 Then 
					vessel.shapeV[x, y].preferredAmmo1V  = TWeaponClass.DefaultMissile
				ElseIf i = 1 And vessel.shapeV[x, y].preferredAmmo2V = -1 Then 
					vessel.shapeV[x, y].preferredAmmo2V  = TWeaponClass.DefaultMissile
				ElseIf i = 2 And vessel.shapeV[x, y].preferredAmmo3V = -1 Then 
					vessel.shapeV[x, y].preferredAmmo3V  = TWeaponClass.DefaultMissile
				ElseIf i = 0 Then 
					vessel.shapeV[x, y].preferredAmmo1V :+ 1
				ElseIf i = 1 Then
					vessel.shapeV[x, y].preferredAmmo2V :+ 1
				ElseIf i = 2 Then
					vessel.shapeV[x, y].preferredAmmo3V :+ 1
				End If
			ElseIf Left(click, 10) = "NextBullet" Then
				Local i:Int = Int(Right(click, 1))
				If i = 0 And vessel.shapeV[x, y].preferredAmmo1V = TWeaponClass.LastBullet Then Return -1
				If i = 1 And vessel.shapeV[x, y].preferredAmmo2V = TWeaponClass.LastBullet Then Return -1
				If i = 2 And vessel.shapeV[x, y].preferredAmmo3V = TWeaponClass.LastBullet Then Return -1
				If i = 0 And vessel.shapeV[x, y].preferredAmmo1V = -1 Then 
					vessel.shapeV[x, y].preferredAmmo1V  = TWeaponClass.DefaultBullet
				ElseIf i = 1 And vessel.shapeV[x, y].preferredAmmo2V = -1 Then 
					vessel.shapeV[x, y].preferredAmmo2V  = TWeaponClass.DefaultBullet
				ElseIf i = 2 And vessel.shapeV[x, y].preferredAmmo3V = -1 Then 
					vessel.shapeV[x, y].preferredAmmo3V  = TWeaponClass.DefaultBullet
				ElseIf i = 0 Then 
					vessel.shapeV[x, y].preferredAmmo1V :+ 1
				ElseIf i = 1 Then
					vessel.shapeV[x, y].preferredAmmo2V :+ 1
				ElseIf i = 2 Then
					vessel.shapeV[x, y].preferredAmmo3V :+ 1
				End If
			End If
			Local k:Int = GetChar()
			If k = 0 Then
			ElseIf k = KEY_RETURN Then 
				Return -3
			ElseIf k = KEY_ESCAPE Then 
				Return -2
			End If
			Return -1
		Forever
	End Method
	
	Method ShowWeapon(gd:TGameData, missile:Int, gfx:TGFX, w:TWeaponClass, i:Int, x:Int, top:Int, vessel:TVessel)
		If w = Null Then
			gfx.SetFontSize(TGFX.FontLarge)
			SetColor(255, 0, 0)
			DrawText("No preference set", Int((gfx.width / 2) - (gfx.GetCachedFontWidth("No preference set") / 2.0)), top)
		Else
			Local s:String = ""
			If missile = 1 Then 
				If w.defensive = 0 Then 
					s = "Damage = " + Int(w.damage) + ", Speed = " + Int(w.targetSpeed) + " m/s, " + Int(w.dps) + " DPS, Trigger/Blast Radius = " + Int(w.hitRadius) + "/" +  Int(w.blastRadius) + " m, Range = " + Int(w.maxRange) + " m"
				Else
					s = "Maximum Velocity = " + Int(w.targetSpeed) + " m/s, " + Int(w.dps) + " DPS, Trigger/Blast Radius = " + Int(w.hitRadius) + "/" +  Int(w.blastRadius) + " m, Range = " + Int(w.maxRange) + " m"
				End If
			Else
				If w.defensive = 0 Then 
					s = "Damage = " + Int(w.damage) + ", Velocity = " + Int(w.targetSpeed) + " m/s, Trigger/Blast Radius = " + Int(w.hitRadius) + "/" +  Int(w.blastRadius) + " m, Range = " + Int(w.maxRange) + " m"
				Else
					s = "Velocity = " + Int(w.targetSpeed) + " m/s, Trigger/Blast Radius = " + Int(w.hitRadius) + "/" +  Int(w.blastRadius) + " m, Range = " + Int(w.maxRange) + " m"
				End If
			End If					

			' Colour image
			SetScale(Double(zoom) / Double(TWeaponClass.ImgSize), Double(zoom) / Double(TWeaponClass.ImgSize))
			SetColor(255, 255, 255)
			DrawImage(w.img, x + (zoom / 2), top + (zoom / 2))
			SetScale(1.0, 1.0)

			' Text
			gfx.SetFontSize(TGFX.FontXLarge)
			SetColor(255, 255, 255)
			DrawText(String(vessel.loadout[w.id] / 10) + String(vessel.loadout[w.id] Mod 10), ((gfx.width + width) / 2) - 230, top)
			If missile = 1 Then 
				gfx.LeftText(TGFX.FontMedium, w.number + " " + w.name + " missile(s)", x + zoom + 25, top)
			Else
				gfx.LeftText(TGFX.FontMedium, w.number + " " + w.name + " shot(s)", x + zoom + 25, top)
			End If
			Local h:Float = gfx.GetCachedFontHeight(s) - 2
			SetColor(0, 255, 0)
			gfx.LeftText(TGFX.FontMediumSmall, w.description, x + zoom + 25, top + h + 2)
			Local wt:Int = gfx.GetCachedFontWidth(" " + w.description)
			SetColor(0, 0, 255)
			gfx.LeftText(TGFX.FontMediumSmall, s, x + zoom + 25, top + h + 2 + h)
			SetColor(255, 0, 0)
			gfx.LeftText(TGFX.FontMediumSmall, "Cost: " + w.cost, x + zoom + 25 + wt, top + h + 2)
		End If

		' Buttons
		If missile = 1 Then
			If w = Null Then
				gd.buttons.AddButtonMS("Default Missile", 2, (gfx.width + width) / 2 - 175, top + 20, 150, "NextMissile:" + i)
			Else
				gd.buttons.AddButtonMS("Previous Missile", 1, (gfx.width + width) / 2 - 175, top - 10, 150, "PreviousMissile:" + i, w = Null Or w.id = TWeaponClass.DefaultMissile)
				gd.buttons.AddButtonMS("Next Missile", 2, (gfx.width + width) / 2 - 175, top + 20, 150, "NextMissile:" + i, w.id = TWeaponClass.LastMissile)
			End If
		Else
			If w = Null Then
				gd.buttons.AddButtonMS("Default Projectile", 2, (gfx.width + width) / 2 - 175, top + 20, 150, "NextBullet:" + i)
			Else
				gd.buttons.AddButtonMS("Previous Projectile", 1, (gfx.width + width) / 2 - 175, top - 10, 150, "PreviousBullet:" + i, w = Null Or w.id = TWeaponClass.DefaultBullet)
				gd.buttons.AddButtonMS("Next Projectile", 2, (gfx.width + width) / 2 - 175, top + 20, 150, "NextBullet:" + i, w.id = TWeaponClass.LastBullet)
			End If
		EndIf
	End Method
	
End Type

