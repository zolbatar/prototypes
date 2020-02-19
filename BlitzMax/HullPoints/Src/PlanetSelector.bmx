SuperStrict
Import "Buttons.bmx"
Import "GFX.bmx"
Import "Starfield.bmx"

Type TPlanetSelector
	Field imgs:TImage[], width:Int, title:String, s:String = "", sizePlanet:Int = 1
	Const size:Double = 128, length:Int = 30
	
	Function Create:TPlanetSelector(imgs:TImage[], width:Int, title:String)
		Local ui:TPlanetSelector = New TPlanetSelector
		ui.imgs = imgs
		ui.width = width
		ui.title = title
		FlushKeys()
		Return ui
	End Function
	
	Method Render:Int(gfx:TGFX, scale:Double, x:Int, y:Int, ui:TButtons, sf:TStarfield, ret:Int)
		SetOrigin(0, 0)
		If ret = 0 Then sf.p = MilliSecs()
		If ret = 0 Then FlushKeys()
		Repeat
			If ret = 0 Then sf.Render(1.0)
			If ret = 0 Then ui.ClearButtons()

			' Render
			Local l:Int = (gfx.width / 2) - (width / 2.0)
			Local h:Float = 350 + (y * size)
			Local t:Int = (gfx.height / 2) - (h / 2)

			' Shape
			SetAlpha(1.0)
			SetColor(0, 0, 64)
			DrawRect(l + 1, t + 1, width - 2, h - 2)
			SetColor(255, 255, 255)
			SetLineWidth(2.0)
			DrawLine(l + 1, t + 1, l + width - 1, t + 1)
			DrawLine(l + 1, t + h - 1, l + width - 1, t + h - 1)
			DrawLine(l + 1, t + 1, l + 1, t + h - 1)
			DrawLine(l - 1 + width, t + 1, l - 1 + width, t + h - 1)
			SetLineWidth(1.0)

			' Title
			gfx.SetFontSize(TGFX.FontXXLarge)
			SetColor(255, 255, 255)
			DrawText(title, Int((gfx.width / 2) - (gfx.GetCachedFontWidth(title) / 2.0)), t + 25)
				
			' Text
			gfx.SetFontSize(TGFX.FontXLarge)
			SetColor(220, 220, 220)
			Local text:String = "Enter the Planet Name"
			DrawText(text, Int((gfx.width / 2) - (gfx.GetCachedFontWidth(text) / 2.0)), t + 125)

			' Box
			gfx.SetFontSize(TGFX.FontLarge)
			Local ht:Float = gfx.GetCachedFontHeight("Text")
			SetColor(255, 255, 255)
			DrawRect((gfx.width / 2) - (400 / 2.0), t + 175, 400, ht + 10)
			SetColor(0, 0, 0)
			DrawText(s, Int((gfx.width / 2) - (gfx.GetCachedFontWidth(s) / 2.0)), t + 175 + (ht / 2) - 5)

			Local bt:Int = t + 225 
			ui.AddButtonL("Small", "Size", 5, (gfx.width / 2.0) - 225, bt, 150, "SmallSize", sizePlanet <> 0)
			ui.AddButtonL("Medium", "Size", 5, (gfx.width / 2.0) - 75, bt, 150, "MediumSize", sizePlanet <> 1)
			ui.AddButtonL("Large", "Size", 5, (gfx.width / 2.0) + 75, bt, 150, "LargeSize", sizePlanet <> 2)

			' Draw grid of shit
			Local lX:Double = (gfx.width / 2) - (Double(x) / 2.0 * size) + (size / 2)
			Local tY:Double = t + 350
			Local i:Int = 0
			gfx.SetFontSize(TGFX.FontMedium)
			For Local yC:Int = 0 To y -1
				For Local xC:Int = 0 To x - 1
					SetColor(255, 255, 255)
					SetScale(scale, scale)
					DrawImage(imgs[i], lX + (Double(xC) * size), tY + (Double(yC) * size))
					SetScale(1.0, 1.0)
					i :+ 1
				Next
			Next
				
			' Message
			SetColor(0, 255, 0)
			text = "Enter the planet name, select a size"
			DrawText(text, Int((gfx.width / 2) - (gfx.GetCachedFontWidth(text) / 2.0)), t + h - 30 - gfx.GetCachedFontHeight(text))
			text = "and then Click a planet style to add (Esc to cancel)"
			DrawText(text, Int((gfx.width / 2) - (gfx.GetCachedFontWidth(text) / 2.0)), t + h - 25)
				
			' Render
			If ret = 0 Then
				ui.Render(gfx)
				gfx.UIScanlines()
				Flip
				PollSystem()
				sf.Cycle()
			End If

			Local k:Int = GetChar()
			If k = 0 Then
			ElseIf k = KEY_ESCAPE Then 
				FlushKeys()
				Return -1
			ElseIf k = KEY_BACKSPACE And Len(s) > 0 Then
				s = Left(s, Len(s) - 1)
			Else
				If s = "(NEW)" Then s = ""
				s :+ Chr(k)
			End If
			If Len(s) > length Then s = Left(s, length)
			Local click:String = ui.Clicked()
			If click = "SmallSize" Then sizePlanet = 0
			If click = "MediumSize" Then sizePlanet = 1
			If click = "LargeSize" Then sizePlanet = 2
			If MouseHit(1) Then
				If ui.CheckClick(MouseX(), MouseY()) = 0 Then
					Local xL:Int = ((MouseX() - lX) + (size / 2)) / size
					Local yL:Int = ((MouseY() - tY) + (size / 2)) / size
					If xL >= 0 And xL < X And yL >= 0 And yL <= y Then Return (yL * x) + xL
				End If
			End If
			If ret = 1 Then Return -100
		Forever
	End Method
			
End Type
