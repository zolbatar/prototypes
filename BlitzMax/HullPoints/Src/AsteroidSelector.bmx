SuperStrict
Import "Buttons.bmx"
Import "GFX.bmx"
Import "Starfield.bmx"

Type TAsteroidSelector
	Field imgs:TImage[], width:Int, title:String, s:String = "", sizeAsteroid:Int = 1
	Const size:Double = 128, length:Int = 30
	
	Function Create:TAsteroidSelector(imgs:TImage[], width:Int, title:String)
		Local ui:TAsteroidSelector = New TAsteroidSelector
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
			Local h:Float = 250 + (y * size)
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
				
			Local bt:Int = t + 125 
			ui.AddButtonL("Small", "Size", 5, (gfx.width / 2.0) - 225, bt, 150, "SmallSize", sizeAsteroid <> 0)
			ui.AddButtonL("Medium", "Size", 5, (gfx.width / 2.0) - 75, bt, 150, "MediumSize", sizeAsteroid <> 1)
			ui.AddButtonL("Large", "Size", 5, (gfx.width / 2.0) + 75, bt, 150, "LargeSize", sizeAsteroid <> 2)

			' Draw grid of shit
			Local lX:Double = (gfx.width / 2) - (Double(x) / 2.0 * size) + (size / 2)
			Local tY:Double = t + 250
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
			Local text:String = "You can add an asteroid quickly on the mission builder screen by pressing 1/2/3"
			DrawText(text, Int((gfx.width / 2) - (gfx.GetCachedFontWidth(text) / 2.0)), t + h - 30 - gfx.GetCachedFontHeight(text))
			text = "Select a size and then Click an asteroid style to add (Esc to cancel)"
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
			If click = "SmallSize" Then sizeAsteroid = 0
			If click = "MediumSize" Then sizeAsteroid = 1
			If click = "LargeSize" Then sizeAsteroid = 2
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

