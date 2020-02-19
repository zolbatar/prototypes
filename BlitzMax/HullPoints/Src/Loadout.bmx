SuperStrict
Import "Helper.bmx"
Import "GameData.bmx"
Import "GFX.bmx"
Import "Starfield.bmx"
Import "Vessel.bmx"
Import "WeaponClass.bmx"
Type TLoadout
	Const zoom:Int = 48, spacer:Int = 12
	Field width:Int, height:Int, title:String, text:String, page:Int = 0, loadoutSaved:Int[], v:TVessel

	Function Create:TLoadout(text:String, title:String, v:TVessel)
		Local o:TLoadout= New TLoadout
		o.width = 850
		o.title = title
		o.text = text
		o.v = v
		o.loadoutSaved = New Int[TWeaponClass.NumberOfClasses]
		For Local i:Int = 0 To TWeaponClass.NumberOfClasses - 1
			o.loadoutSaved[i] = v.loadout[i]
		Next
		Return o
	End Function

	Method Render:Int(gfx:TGFX, ret:Int, gd:TGameData)
		SetOrigin(0, 0)
		Local numPerPage:Int = 6
		Local bs:Int = ((zoom + spacer) * numPerPage)
		height = 220 + bs
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
		gfx.SetFontSize(TGFX.FontLarge)
		Local l:Int = (gfx.width / 2) - (width / 2.0)
		Local ht:Float = gfx.GetCachedFontHeight("Text")
		Local k:Int
		If ret = 0 Then gd.sf.p = MilliSecs()
		If ret = 0 Then FlushKeys()
		Repeat
			If ret = 0 Then gd.sf.Render(1.0)
			SetOrigin(0, 0)
			gd.buttons.ClearButtons()

			' Title
			gfx.SetFontSize(TGFX.FontXXLarge)
			SetAlpha(1.0)
			SetColor(255, 255, 255)
			DrawText(title, Int((gfx.width / 2) - (gfx.GetCachedFontWidth(title) / 2.0)), top + 25)
		
			' Grid positions
			Local l:Int = ((gfx.width - width) / 2) + 75
			Local r:Int = l + width - 150
			Local t:Int = ((gfx.height - height) / 2) + 145
			Local b:Int = t + ((zoom + spacer) * gd.weapons.Length)
		
			' Mouse position on grid
			Local pos:Int = -1
			If MouseX() > (l - (zoom / 2)) And MouseX() < (r + (zoom / 2)) And MouseY() > (t - (zoom / 2))  And MouseY() < (b + (zoom / 2)) Then
				pos = (MouseY() - t + (zoom / 2)) / (zoom + spacer)
			End If
	
			' Display modules			
			SetAlpha(1.0)
			Local i:Int = 0 
			Local id:Int = 0
			For Local w:TWeaponClass = EachIn gd.weapons
				If w.id >= TWeaponClass.fragmentID Then Continue
				Select page
				Case 0
					If w.t = TWeaponClass.bulletType Then Continue
				Case 1
					If w.t = TWeaponClass.missileType Then Continue
				End Select
				
				If pos = i Then
					id = w.id
					SetAlpha(0.5)
					SetColor(0, 0, 160)
					DrawRect(l - 50, t + (i * (zoom + spacer)) - (zoom / 2) - (spacer / 2), r - l + 100, (zoom + spacer))
					SetAlpha(1.0)
				End If
				
				' Colour image
				SetScale(Double(zoom) / Double(TWeaponClass.ImgSize), Double(zoom) / Double(TWeaponClass.ImgSize))
				SetColor(255, 255, 255)
				DrawImage(w.img, l, t + (i * (zoom + spacer)))
				SetScale(1.0, 1.0)

				' Counter	
				Local aa:Int = t + (i * (zoom + spacer)) - (zoom / 2) + 1
				gfx.SetFontSize(TGFX.FontXLarge)
				SetAlpha(1.0)
				SetColor(255, 255, 255)
				Local s:String = String(v.loadout[w.id] / 10) + String(v.loadout[w.id] Mod 10)
				DrawText(s, r - 40, aa + 8)
				
				Local suffix:String = " missile(s)"
				If w.t = TWeaponClass.bulletType Then suffix = " shot(s)"
				gfx.LeftText(TGFX.FontMedium, w.number + " " + w.name + suffix, l + zoom + 10, aa)
				s = ""
				If w.t = TWeaponClass.missileType Then
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
				Local h:Float = gfx.GetCachedFontHeight(s) - 2
				SetColor(0, 255, 0)
				gfx.LeftText(TGFX.FontMediumSmall, w.description, l + zoom + 10, aa + h + 2)
				Local wt:Int = gfx.GetCachedFontWidth(" " +w.description)
				SetColor(0, 0, 255)
				gfx.LeftText(TGFX.FontMediumSmall, s, l + zoom + 10, aa + h + 2 + h)
				SetColor(255, 0, 0)
				gfx.LeftText(TGFX.FontMediumSmall, "Cost: " + w.cost, l + zoom + 10 + wt, aa + h + 2)
				i :+ 1
				If i = numPerPage Then Exit
			Next
			
			' Buttons
			gd.buttons.AddButtonBordered("Configure", "Missiles", 3, (gfx.width / 2) - 300, top + height - 90, 300, "ConfigureMissiles", page = 0)
			gd.buttons.AddButtonBordered("Configure", "Projectiles", 4, (gfx.width / 2), top + height - 90, 300, "ConfigureProjectiles", page = 1)
		
			' Message
			SetColor(0, 255, 0)
			gfx.SetFontSize(TGFX.FontLarge)
			Local s:String = "(Left click To increase, Right click To decrease, Return to accept, Esc To cancel)"
			DrawText(s, Int((gfx.width / 2) - (gfx.GetCachedFontWidth(s) / 2.0)), top + height - 35)
			If ret = 0 Then
				gfx.UIScanlines()
				Flip
				PollSystem()
				gd.sf.Cycle()
			End If
			SetOrigin(0, 0)

			If MouseHit(1) Then 
				If gd.buttons.CheckClick(MouseX(), MouseY()) = 0 Then
					If pos <> -1 Then v.loadout[id] :+ 1
				End If
			End If
			If MouseHit(2) And pos <> -1 Then v.loadout[id] :- 1
			If v.loadout[id] < 0 Then v.loadout[id] = 0
			If v.loadout[id] > 99 Then v.loadout[id] = 99
			Local click:String = gd.buttons.Clicked()
			If click = "ConfigureMissiles" Then page = 0
			If click = "ConfigureProjectiles" Then page = 1
			Local k:Int = GetChar()
			If k = 0 Then
			ElseIf k = KEY_RETURN Then 
				Return -3
			ElseIf k = KEY_ESCAPE Then 
				For Local i:Int = 0 To TWeaponClass.NumberOfClasses - 1
					v.loadout[i] = loadoutSaved[i]
				Next
				Return -2
			End If
			Return -1
		Forever
	End Method

End Type
