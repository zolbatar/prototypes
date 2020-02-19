SuperStrict
Import "GFX.bmx"
Import "Buttons.bmx"

Type TFullScreenButtonBar

	Function CreateSave:Int(gfx:TGFX, buttons:TButtons)
		SetOrigin(0, 0)
		SetAlpha(0.75)
		SetColor(0, 0, 0)
		DrawRect(0, 0, gfx.width, gfx.height)
		
		' Buttons
		Local x:Int = (gfx.width - 900) / 2
		buttons.ClearButtons()
		buttons.AddButtonBordered("Esc - Cancel", "", 0, x, (gfx.height / 2) - 50 , 300, "Cancel")
		buttons.AddButtonBordered("S - Save changes, then quit", "", 1, x + 300, (gfx.height / 2) - 50 , 300, "Save")
		buttons.AddButtonBordered("Q - Quit to main menu", "", 2, x + 600, (gfx.height / 2) - 50 , 300, "Quit")
		buttons.Render(gfx)
		gfx.UIScanlines()
		Flip
		FlushKeys()
		Repeat
			If MouseHit(1) Then buttons.CheckClick(MouseX(), MouseY())
			Local click:String = buttons.Clicked()
			If KeyHit(KEY_ESCAPE) Or click = "Cancel" Then Return 0
			If KeyHit(KEY_S) Or click = "Save" Then Return 1
			If KeyHit(KEY_Q) Or click = "Quit" Then Return 2
			Delay(50)
		Forever
	End Function

	Function CreateEndGame:Int(gfx:TGFX, buttons:TButtons)
		SetOrigin(0, 0)
		SetAlpha(0.75)
		SetColor(0, 0, 0)
		DrawRect(0, 0, gfx.width, gfx.height)
		
		' Buttons
		Local x:Int = (gfx.width - 600) / 2
		buttons.ClearButtons()
		buttons.AddButtonBordered("Esc - Cancel", "", 0, x, (gfx.height / 2) - 50 , 300, "Cancel")
		buttons.AddButtonBordered("Q - Quit game", "", 2, x + 300, (gfx.height / 2) - 50 , 300, "Quit")
		buttons.Render(gfx)
		gfx.UIScanlines()
		Flip
		FlushKeys()
		Repeat
			If MouseHit(1) Then buttons.CheckClick(MouseX(), MouseY())
			Local click:String = buttons.Clicked()
			If KeyHit(KEY_ESCAPE) Or click = "Cancel" Then Return 0
			If KeyHit(KEY_Q) Or click = "Quit" Then Return 2
			Delay(50)
		Forever
	End Function

End Type

