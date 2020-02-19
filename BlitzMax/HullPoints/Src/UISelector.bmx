SuperStrict
Import "GFX.bmx"
Import "Buttons.bmx"
Import "Starfield.bmx"

Type TUISelector
	Field list:TList, width:Int, title:String, typ:String, add:Int, del:Int
	
	Function Create:TUISelector(list:TList, width:Int, title:String, typ:String, add:Int, del:Int)
		Local o:TUISelector = New TUISelector
		o.list = list
		o.width = width
		o.title = title
		o.typ = typ
		o.add = add
		o.del = del
		Return o
	End Function	
	
	Method Render:Int(gfx:TGFX, ui:TButtons, sf:TStarfield, ret:Int)
		SetOrigin(0, 0)
		gfx.SetFontSize(TGFX.FontLarge)
		Local ht:Float = gfx.GetCachedFontHeight("Text")
		Local width:Int = 700
		If ret = 0 Then width = gfx.width - 250
		Local height:Int = 200 + (list.Count() * ht)
		Local top:Int = (gfx.height - height) / 2
		If ret = 1 Then
			SetColor(0, 0, 0)
			SetAlpha(0.75)
			DrawRect(0, 0, gfx.width, gfx.height)
			SetColor(0, 0, 160)
			SetAlpha(1.0)
			DrawRect((gfx.width - width) / 2, top, width, height)
			SetColor(0, 0, 32)
			SetAlpha(1.0)
			DrawRect(((gfx.width - width) / 2) + 2, top + 2, width - 4, height - 4)
		End If
		If ret = 0 Then sf.p = MilliSecs()
		If ret = 0 Then FlushKeys()
		Local l:Int = (gfx.width / 2) - (width / 2.0)
		Local l2:Int = (gfx.width / 2) + (width / 2.0)
		Repeat
			If ret = 0 Then sf.Render(1.0)
			ui.ClearButtons()
	
			' Title
			gfx.SetFontSize(TGFX.FontXXLarge)
			SetColor(255, 255, 255)
			If ret = 0 Then
				DrawText(title, Int((gfx.width / 2) - (gfx.GetCachedFontWidth(title) / 2.0)), 50)
			Else
				DrawText(title, Int((gfx.width / 2) - (gfx.GetCachedFontWidth(title) / 2.0)), top + 25)
			End If
	
			' Mouse position on list
			Local t:Int = ((gfx.height - height) / 2) + 125
			If ret = 0 Then t = 150
			Local pos:Int = -1
			If MouseX() > l And MouseX() < l2 And MouseY() > t And MouseY() < t + (ht * list.Count()) Then
				pos = (MouseY() - t) / ht
			End If

			' Labels
			gfx.SetFontSize(TGFX.FontLarge)
			Local i:Int = 0
			For Local s:String = EachIn list
				If pos = i Then
					SetAlpha(0.5)
					SetColor(0, 0, 160)
					If ret = 0 Then
						DrawRect(l, (ht * i) + t, width, ht)
					Else
						DrawRect(l + 30, (ht * i) + t, width - 60, ht)
					End If
					SetAlpha(1.0)
				End If			
				SetColor(255, 255, 0)
				If ret = 0 Then
					DrawText(Chr(65 + i), l + 10, (ht * i) + t)
					SetColor(220, 220, 220)
					DrawText(s, l + 40, (ht * i) + t)
				Else
					DrawText(Chr(65 + i), l + 40, (ht * i) + t)
					SetColor(220, 220, 220)
					DrawText(s, l + 70, (ht * i) + t)
				End If
				If ret = 0 Then
					If del = 1 Then ui.AddButtonMS("Delete " + typ, 2, l - 100, (ht * i) + t - 5, 100, "Delete:" + String(i))
				Else
					If del = 1 Then ui.AddButtonMS("Delete " + typ, 2, l - 100, (ht * i) + ((gfx.height - height) / 2) - 25 + t - 5, 100, "Delete:" + String(i))
				End If
				i :+ 1
			Next
		
			' Prompt
			Local s:String = ""
			If i > 0 Then
				s = "Please press a key from A to " + Chr(65 + i - 1) + " (Escape to cancel)"
			Else
				s = "(Escape To cancel)"
			End If
			SetColor(0, 255, 0)
			If ret = 0 Then
				gfx.SetFontSize(TGFX.FontXLarge)
				DrawText(s, Int((gfx.width / 2) - (gfx.GetCachedFontWidth(s) / 2.0)), gfx.height - 150)
			Else
				gfx.SetFontSize(TGFX.FontLarge)
				DrawText(s, Int((gfx.width / 2) - (gfx.GetCachedFontWidth(s) / 2.0)), top + height - 35)
			End If
			
			' Buttons		
			If ret = 0 Then
				If add = 1 Then ui.AddButtonBordered("New", typ, 1, (gfx.width / 2) - 75, gfx.height - 100, 150, "AddNew")
			Else
				If add = 1 Then ui.AddButtonBordered("New", typ, 1, (gfx.width / 2) - 75, ((gfx.height - height) / 2) - 25 + height - 50, 150, "AddNew")
			End If
			SetColor(0, 255, 0)

			ui.Render(gfx)
			If ret = 0 Then
				gfx.UIScanlines()
				Flip
				PollSystem()
				sf.Cycle()
			End If
			
			' Keys?
			If MouseHit(1) Then 
				If ui.CheckClick(MouseX(), MouseY()) = 0 Then
					' Selected current row
					If pos <> -1 Then Return pos
				End If
			End If
			Local click:String = ui.Clicked()
			If click = "AddNew" Then Return -2
			If Left(click, 7) = "Delete:" Then 
				i = Int(Right(click, Len(click) - 7))
				Return -3 - i
			End If
			Local k:Int = GetChar()
			If k = KEY_ESCAPE Then 
				FlushKeys()
				Return -1
			End If
			If k >= Asc("a") And k <= Asc("z") Then k :- 32
			If k >= Asc("A") And k < Asc("A") + i  Then
				FlushKeys()
				Return k - Asc("A")
			End If
			If ret = 1 Then Return -100
		Forever
	End Method
		
End Type

