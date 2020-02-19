SuperStrict
Import "Helper.bmx"
Import "GameData.bmx"
Import "GFX.bmx"
Import "Starfield.bmx"

Type TModuleChooser
	Const zoom:Int = 48, spacer:Int = 8
	Field x:Int, y:Int, width:Int, height:Int, title:String, text:String

	Function Create:TModuleChooser(x:Int, y:Int, text:String, title:String)
		Local o:TModuleChooser = New TModuleChooser
		o.x = x
		o.y = y
		o.width = 650
		o.title = title
		o.text = text
		Return o
	End Function
	
	Method Render:Int(gfx:TGFX, ret:Int, gd:TGameData)
		SetOrigin(0, 0)
		Local bs:Int = ((zoom + spacer) * gd.pieces[1].maxVariant)
		height = 170 + bs
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
			gd.buttons.ClearButtons()
			SetOrigin(0, 0)

			' Title
			gfx.SetFontSize(TGFX.FontXXLarge)
			SetAlpha(1.0)
			SetColor(255, 255, 255)
			DrawText(title, Int((gfx.width / 2) - (gfx.GetCachedFontWidth(title) / 2.0)), top + 25)
		
			' Grid positions
			Local l:Int = (gfx.width - width) / 2 + 75
			Local r:Int = l + width - 150
			Local t:Int = ((gfx.height - height) / 2) + 145
			Local b:Int = t + ((zoom + spacer) * gd.pieces[1].maxVariant)
		
			' Mouse position on grid
			Local pos:Int = -1
			If MouseX() > (l - (zoom / 2)) And MouseX() < (r + (zoom / 2)) And MouseY() > (t - (zoom / 2))  And MouseY() < (b + (zoom / 2)) Then
				pos = (MouseY() - t + (zoom / 2)) / (zoom + spacer)
			End If
	
			' Display modules			
			SetAlpha(1.0)
			For Local i:Int = 0 To gd.pieces[1].maxVariant - 1
				If pos = i Then
					SetAlpha(0.5)
					SetColor(0, 0, 160)
					DrawRect(l - 50, t + (i * (zoom + spacer)) - (zoom / 2) - (spacer / 2), r - l + 100, (zoom + spacer))
					SetAlpha(1.0)
				End If			
				SetPlayerColour(2, gd.fleetColours)
				TPiece.RenderPiece(gd.pieces, zoom, 1, l, t + (i * (zoom + spacer)), 0, i)
				SetColor(255, 255, 255)
				gfx.LeftText(TGFX.FontMedium, gd.pieces[1].descriptions[i], l + zoom + 10, t + (i * (zoom + spacer)) - (zoom / 2) + 1)
				Local h:Float = gfx.GetCachedFontHeight(gd.pieces[1].longDescriptions[i]) - 2
				SetColor(0, 255, 0)
				gfx.LeftText(TGFX.FontMediumSmall, gd.pieces[1].longDescriptions[i], l + zoom + 10, t + (i * (zoom + spacer)) + h + 3- (zoom / 2))
				SetColor(255, 0, 0)
				gfx.LeftText(TGFX.FontMediumSmall, "Cost: " + gd.pieces[1].GetCost(i) + ", Mass: " + gd.pieces[1].GetMass(i), l + zoom + 10, t + (i * (zoom + spacer)) + h + h + 3 - (zoom / 2))
			Next
		
			' Message
			SetColor(0, 255, 0)
			gfx.SetFontSize(TGFX.FontLarge)
			DrawText("(Esc to cancel)", Int((gfx.width / 2) - (gfx.GetCachedFontWidth("(Esc to cancel)") / 2.0)), top + height - 35)
			If ret = 0 Then
				gfx.UIScanlines()
				Flip
				PollSystem()
				gd.sf.Cycle()
			End If
			
			SetOrigin(0, 0)
			Local k:Int = GetChar()
			If k = 0 Then
			ElseIf k = KEY_ESCAPE Then 
				Return -2
			End If
			If MouseHit(1) And pos > -1 Then Return pos
			Return -1
		Forever
	End Method
	
End Type
