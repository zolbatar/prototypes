SuperStrict
Import "GameData.bmx"
Import "GFX.bmx"
Import "Starfield.bmx"

Type TUIInputBox
	Field text:String, existing:String, width:Int, title:String, length:Int
	
	Function Create: TUIInputBox(text:String, existing:String, width:Int, title:String, length:Int)
		Local ui: TUIInputBox = New TUIInputBox
		ui.text = text
		ui.existing = existing
		ui.width = width
		ui.title = title
		ui.length = length
		Return ui
	End Function
	
	Method Render:String(gfx:TGFX, gd:TGameData, ret:Int)
		SetOrigin(0, 0)
		If ret = 1 Then
			SetColor(0, 0, 0)
			SetAlpha(0.75)
			DrawRect(0, 0, gfx.width, gfx.height)
			SetOrigin(0, ((gfx.height - 350) / 2) - 25)
			SetColor(0, 0, 160)
			SetAlpha(1.0)
			DrawRect((gfx.width - 700) / 2, 25, 700, 350)
			SetColor(0, 0, 32)
			SetAlpha(1.0)
			DrawRect(((gfx.width - 700) / 2) + 2, 27, 696, 346)
		End If
		gfx.SetFontSize(TGFX.FontLarge)
		Local l:Int = (gfx.width / 2) - (width / 2.0)
		Local ht:Float = gfx.GetCachedFontHeight("Text")
		Local s:String = existing
		Local k:Int
		If ret = 0 Then gd.sf.p = MilliSecs()
		If ret = 0 Then FlushKeys()
		Repeat
			If ret = 0 Then gd.sf.Render(1.0)
			gd.buttons.ClearButtons()

			' Title
			gfx.SetFontSize(TGFX.FontXXLarge)
			SetAlpha(1.0)
			SetColor(255, 255, 255)
			DrawText(title, Int((gfx.width / 2) - (gfx.GetCachedFontWidth(title) / 2.0)), 50)
	
			' Text
			gfx.SetFontSize(TGFX.FontXLarge)
			SetColor(220, 220, 220)
			DrawText(text, Int((gfx.width / 2) - (gfx.GetCachedFontWidth(text) / 2.0)), 200)
			Local i:Int = 0
			
			' Box
			SetColor(255, 255, 255)
			DrawRect(l, 250, width, ht + 10)
			SetColor(0, 0, 0)
			gfx.SetFontSize(TGFX.FontLarge)
			DrawText(s, Int((gfx.width / 2) - (gfx.GetCachedFontWidth(s) / 2.0)), 250 + ht / 2 - 5)

			' Message
			SetColor(0, 255, 0)
			DrawText("(Return to accept, Esc to cancel)", Int((gfx.width / 2) - (gfx.GetCachedFontWidth("(Return to accept, Esc to cancel)") / 2.0)), 300)
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
				Return existing
			ElseIf k = KEY_RETURN Then
				Return Trim(s)
			ElseIf k = KEY_BACKSPACE And Len(s) > 0 Then
				s = Left(s, Len(s) - 1)
			Else
				If s = "(NEW)" Then s = ""
				s :+ Chr(k)
			End If
			If Len(s) > length Then s = Left(s, length)
			If ret = 1 Then 
				existing = s
				Return Null
			End If
		Forever
	End Method
			
End Type


