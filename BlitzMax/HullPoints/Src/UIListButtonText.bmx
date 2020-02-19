SuperStrict
Import "Buttons.bmx"
Import "GFX.bmx"
Import "Starfield.bmx"

Type TUIListButtonText
	Field listB1:String[], listB2:String[], size:Int, width:Int, title:String
	
	Function Create:TUIListButtonText(listB1:String[], listB2:String[], size:Int, width:Int, title:String)
		Local ui:TUIListButtonText = New TUIListButtonText
		ui.listB1 = listB1
		ui.listB2 = listB2
		ui.width = width
		ui.size = size
		ui.title = title
		Return ui
	End Function

	Method Render:Int(gfx:TGFX, ui:TButtons, sf:TStarfield, ret:Int)
		SetOrigin(0, 0)
		If ret = 1 Then
			SetColor(0, 0, 0)
			SetAlpha(0.75)
			DrawRect(0, 0, gfx.width, gfx.height)
		End If
		If ret = 0 Then sf.p = MilliSecs()
		If ret = 0 Then FlushKeys()
		Repeat
			If ret = 0 Then sf.Render(1.0)
			ui.ClearButtons()

			' Title
			gfx.SetFontSize(TGFX.FontXXLarge)
			SetColor(255, 255, 255)
			DrawText(title, Int((gfx.width / 2) - (gfx.GetCachedFontWidth(title) / 2.0)), 50)

			Local spacingY:Int = (gfx.height - (size * 150)) / 2
			For Local i:Int = 0 To size - 1
				ui.AddButtonBorderedL(listB1[i], listB2[i], i + 1, (gfx.width - width) / 2, spacingY + (150 * i), width, String(i))
			Next 

			' Prompt
			SetColor(0, 255, 0)
			gfx.SetFontSize(TGFX.FontXLarge)
			DrawText("(Escape To cancel)", Int((gfx.width / 2) - (gfx.GetCachedFontWidth("(Escape To cancel)") / 2.0)), gfx.height - 150)
			
			ui.Render(gfx)
			If ret = 0 Then
				gfx.UIScanlines()
				Flip
				PollSystem()
				sf.Cycle()
			End If

			If MouseHit(1) Then ui.CheckClick(MouseX(), MouseY())
			Local click:String = ui.Clicked()
			If click <> "" Then Return Int(click)
			Local k:Int = GetChar()
			If k = KEY_ESCAPE Then 
				FlushKeys()
				Return -1
			End If
			If ret = 1 Then Return -100
		Forever
	End Method

End Type
