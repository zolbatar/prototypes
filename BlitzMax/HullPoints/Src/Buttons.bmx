SuperStrict
Import BaH.Cairo
Import "GFX.bmx"
Import "Profiler.bmx"

Type TButton
	Field x:Int, y:Int, c:Int, width:Int, height:Int, text1:String, text2:String, event:String, disabled:Int, flag:Int = 0, img:Int = -1
	
	Function CreateAdd(_x:Int, _y: Int, _c:Int, _width:Int, _height:Int, _text1:String, _text2:String, _event:String, _disabled:Int, lst:TList, _flag:Int = 0)
		Local t:TButton = New TButton
		t.x = _x
		t.y = _y
		t.c = _c
		t.width = _width
		t.height = _height
		t.text1 = _text1
		t.text2 = _text2
		t.event = _event
		t.disabled = _disabled
		t.flag = _flag
		ListAddLast(lst, t)
	End Function

	Function CreateAddImage(_x:Int, _y: Int, _c:Int, _width:Int, _img:Int, _event:String, _disabled:Int, lst:TList, _flag:Int = 0)
		Local t:TButton = New TButton
		t.x = _x
		t.y = _y
		t.c = _c
		t.width = _width
		t.height = _width
		t.img = _img
		t.event = _event
		t.disabled = _disabled
		t.flag = _flag
		ListAddLast(lst, t)
	End Function
End Type

Type TButtons
	Const ButtonSpace:Double = 5.0, ButtonInner:Double = 4.0
	Const HeightSmall:Int = 20, HeightMediumishSmall:Int = 25, HeightMediumSmall:Int = 30, HeightMedium:Int = 50, heightSpecial:Int = 51, HeightLarge:Int = 100, types:Int = 7
	Const Widths:Int = 9, Width20:Int = 0, Width25:Int = 1, Width30:Int = 2, Width50:Int = 3, Width100:Int = 4, Width150:Int = 5, Width300:Int = 6, Width500:Int = 7, Width700:Int = 8
	Field buttons:TList, height50:TImage[,], height20:TImage[,], height25:TImage[,], height30:TImage[,], height60:TImage[,], height100:TImage[,]
	Field clickList:TList = CreateList(), rleft:TImage, rright:TImage, del:TImage

	Function Create:TButtons()
		?debug
   			TProfiler.Enter("Buttons::Create")
  		?
		Local o:TButtons = New TButtons
		o.buttons = CreateList()
		o.height100 = CreateButtonSet(heightLarge)
		o.height60 = CreateButtonSet(heightSpecial)
		o.height50 = CreateButtonSet(heightMedium)
		o.height30 = CreateButtonSet(heightMediumSmall)
		o.height25 = CreateButtonSet(HeightMediumishSmall)
		o.height20 = CreateButtonSet(heightSmall)
		o.rleft = LoadImage("Res/RotateLeft.png", FILTEREDIMAGE|MIPMAPPEDIMAGE)
		o.rright = LoadImage("Res/RotateRight.png", FILTEREDIMAGE|MIPMAPPEDIMAGE)
		o.del = LoadImage("Res/Delete.png", FILTEREDIMAGE|MIPMAPPEDIMAGE)
		?debug
   			TProfiler.Leave("Buttons::Create")
  		?
		Return o
	End Function
	
	Function CreateButtonSet:TImage[,](height:Int)
		?debug
   			TProfiler.Enter("Buttons::CreateButtonSet")
  		?
		Local array:TImage[,] = New TImage[types, widths]
		For Local i:Int = 0 To types - 1
			array[i, width20] = RenderButton(20, height, i)
			array[i, width25] = RenderButton(25, height, i)
			array[i, width30] = RenderButton(30, height, i)
			array[i, width50] = RenderButton(50, height, i)
			array[i, width100] = RenderButton(100, height, i)
			array[i, width150] = RenderButton(150, height, i)
			array[i, width300] = RenderButton(300, height, i)
			array[i, width500] = RenderButton(500, height, i)
			array[i, width700] = RenderButton(700, height, i)
		Next 
		?debug
   			TProfiler.Leave("Buttons::CreateButtonSet")
  		?
		Return array
	End Function
	
	Method CheckClick:Int(x:Int, y:Int)
		?debug
   			TProfiler.Enter("Buttons::CheckClick")
  		?
		For Local b:TButton = EachIn buttons
			If x >= b.x And x <= b.x + b.width And y >= b.y And y < b.y + b.height Then' And b.disabled = 0 Then 
				ListAddFirst(clickList, b.event)
				?debug
		   			TProfiler.Leave("Buttons::CheckClick")
		  		?
				Return 1
			End If
		Next
		?debug
   			TProfiler.Leave("Buttons::CheckClick")
  		?
		Return 0
	End Method
	
	Method Clicked:String()
		?debug
   			TProfiler.Enter("Buttons::Clicked")
  		?
		If clickList.Count() > 0 Then
			Local v:String = String(clickList.First())
			clickList.RemoveFirst()
				?debug
   					TProfiler.Leave("Buttons::Clicked")
		  		?
			Return v
		End If
		?debug
   			TProfiler.Leave("Buttons::Clicked")
  		?
		Return ""
	End Method
	
	Method ClearButtons()
		buttons = CreateList()
	End Method
	
	Method AddButtonImage(i:Int, c:Int, x:Int, y:Int, width:Int, event:String, disabled:Int = 0)
		TButton.CreateAddImage(x, y, c, width, i, event, disabled, buttons)
	End Method

	Method AddButtonBordered(text1:String, text2:String, c:Int, x:Int, y:Int, width:Int, event:String, disabled:Int = 0)
		TButton.CreateAdd(x, y, c, width, heightMedium, text1, text2, event, disabled, buttons)
	End Method
	
	Method AddButtonBorderedL(text1:String, text2:String, c:Int, x:Int, y:Int, width:Int, event:String, disabled:Int = 0)
		TButton.CreateAdd(x, y, c, width, heightLarge, text1, text2, event, disabled, buttons)
	End Method

	Method AddButtonL(text1:String, text2:String, c:Int, x:Int, y:Int, width:Int, event:String, disabled:Int = 0)
		TButton.CreateAdd(x, y, c, width, heightSpecial, text1, text2, event, disabled, buttons)
	End Method

	Method AddButtonBorderedXL(text1:String, text2:String, c:Int, x:Int, y:Int, width:Int, event:String, disabled:Int = 0)
		TButton.CreateAdd(x, y, c, width, heightLarge, text1, text2, event, disabled, buttons, 1)
	End Method

	Method AddButtonMS(text1:String, c:Int, x:Int, y:Int, width:Int, event:String, disabled:Int = 0)
		TButton.CreateAdd(x, y, c, width, heightMediumSmall, text1, "", event, disabled, buttons)
	End Method

	Method AddButtonS(text1:String, c:Int, x:Int, y:Int, width:Int, event:String, disabled:Int = 0)
		TButton.CreateAdd(x, y, c, width, heightSmall, text1, "", event, disabled, buttons)
	End Method

	Function RoundedButton(cairo:TCairo, x:Double, y:Double, width:Double, height:Double, fill:Int, radius:Double)
		cairo.NewSubPath()
		cairo.Arc(x + width - radius - buttonSpace, y + radius + buttonSpace, radius, 270, 0)
		cairo.Arc(x + width - radius - buttonSpace, y + height - radius - buttonSpace, radius, 0, 90)
		cairo.Arc(x + radius + buttonSpace, y + height - radius - buttonSpace, radius, 90, 180)
		cairo.Arc(x + radius + buttonSpace, y + radius + buttonSpace, radius, 180, 270)
		cairo.ClosePath()
		If fill = 1 Then 
			cairo.FillPreserve()
			cairo.Fill()
		End If
		cairo.Stroke()
	End Function
	
	Function RenderButton:TImage(width:Int, height:Int, c:Int)
		?debug
   			TProfiler.Enter("Buttons::RenderButton")
  		?
		Local cairo:TCairo = TCairo.Create(TCairoImageSurface.CreateForPixmap(width, height))
		cairo.SetSourceRGBA(1.0, 1.0, 1.0, 1.0)
		If height = 50 Then
			cairo.SetLineWidth(3.0)
			RoundedButton(cairo, 0, 0, width, height, 0, 3.0)
		ElseIf height = 100 Then
			cairo.SetLineWidth(3.0)
			RoundedButton(cairo, 0, 0, width, height, 0, 5.0)
		End If
		Select c
		Case 0
			cairo.SetSourceRGBA(27.0 / 256.0 * 1.10, 69.0 / 256.0 * 1.10, 128.0 / 256.0 * 1.10, 0.5)
		Case 1
			cairo.SetSourceRGBA(0.0, 1.0, 0.0, 0.5)
		Case 2
			cairo.SetSourceRGBA(1.0, 0.0, 0.0, 0.5)
		Case 3
			cairo.SetSourceRGBA(0.5, 0.0, 0.5, 0.5)
		Case 4
			cairo.SetSourceRGBA(0.5, 0.5, 0.5, 0.5)
		Case 5
			cairo.SetSourceRGBA(1.0, 0.75, 0.0, 0.5)
		Case 6
			cairo.SetSourceRGBA(102.0 / 256.0, 51.0 / 256.0, 153.0 / 256.0, 0.5)
		End Select
		Select height
		Case heightSmall
			RoundedButton(cairo, 0, 0, width, height, 1, 3.0)
		Case heightMediumishSmall
			RoundedButton(cairo, 0, 0, width, height, 1, 3.0)
		Case heightMediumSmall
			RoundedButton(cairo, 0, 0, width, height, 1, 3.0)
		Case heightMedium
			cairo.SetLineWidth(3.0)
			RoundedButton(cairo, buttonInner, buttonInner, width - buttonInner * 2, height - buttonInner * 2, 1, 0)
		Case heightLarge
			RoundedButton(cairo, 0, 0, width, height, 1, 5)
		Case heightSpecial
			cairo.SetLineWidth(0.0)
			RoundedButton(cairo, 0, 0, width, height, 1, 3)
		End Select
		Cls
		Local image:TImage = LoadImage(TCairoImageSurface(cairo.getTarget()).pixmap())
		cairo.Destroy()
		?debug
   			TProfiler.Leave("Buttons::RenderButton")
  		?
		Return image
	End Function
	
	Method Render(gfx:TGFX)
		?debug
   			TProfiler.Enter("Buttons::Render")
  		?
		SetOrigin(0, 0)
		SetBlend(ALPHABLEND)
		SetColor(255, 255, 255)
		For Local b:TButton = EachIn buttons
			Local set:TImage[,]
			Select b.height
			Case heightLarge
				set = height100
			Case heightSmall
				set = height20
			Case heightMediumishSmall
				set = height25
			Case heightMediumSmall
				set = height30
			Case heightMedium
				set = height50
			Case heightSpecial
				set = height60
			End Select
			Local h:Int = 0
			Select b.width
			Case 20
				h = width20
			Case 25
				h = width25
			Case 30
				h = width30
			Case 50
				h = width50
			Case 100
				h = width100
			Case 150
				h = width150
			Case 300
				h = width300
			Case 500
				h = width500
			Case 700
				h = width700
			End Select
			If b.disabled = 1 Then SetAlpha(0.25) Else SetAlpha(1.0)
			DrawImage(set[b.c, h], b.x + (b.width / 2), b.y + (b.height / 2))

			' Label
			If b.img = -1 Then
				Select b.height
				Case heightSmall
					Local w:Int = gfx.TextSize(TGFX.FontSmall, b.text1)
					gfx.LeftText(TGFX.FontSmall, b.text1, b.x + ((b.width - w) / 2), b.y + 5)
				Case heightMediumSmall
					Local w:Int = gfx.TextSize(TGFX.FontSmall, b.text1)
					gfx.LeftText(TGFX.FontSmall, b.text1, b.x + ((b.width - w) / 2), b.y + 10)
				Case heightMedium
					If b.width >= 150 Then
						Local w:Int = gfx.TextSize(TGFX.FontMediumLarge, b.text1 + " " + Trim(b.text2))
						gfx.LeftText(TGFX.FontMediumLarge, b.text1 + " " + Trim(b.text2), b.x + ((b.width - w) / 2), b.y + 15)
					Else
						Local w:Int = gfx.TextSize(TGFX.FontMedium, b.text1)
						gfx.LeftText(TGFX.FontMedium, b.text1, b.x + ((b.width - w) / 2), b.y + 10)
						w = gfx.TextSize(TGFX.FontMedium, b.text2)
						gfx.LeftText(TGFX.FontMedium, b.text2, b.x + ((b.width - w) / 2), b.y + 25)
					End If
				Case heightLarge
					If b.flag = 0 Then
						SetColor(255, 255, 0)
						Local w:Int = gfx.TextSize(TGFX.FontXLarge, b.text1)
						gfx.LeftText(TGFX.FontXLarge, b.text1, b.x + ((b.width - w) / 2), b.y + 17)
						SetColor(255, 255, 255)
						w = gfx.TextSize(TGFX.FontMediumLarge, b.text2)
						gfx.LeftText(TGFX.FontMediumLarge, b.text2, b.x + ((b.width - w) / 2), b.y + 58)
					Else
						Local w:Int = gfx.TextSize(TGFX.FontLarge, b.text1)
						gfx.LeftText(TGFX.FontLarge, b.text1, b.x + ((b.width - w) / 2), b.y + 20)
					End If
				Case heightSpecial
					Local w:Int = gfx.TextSize(TGFX.FontMedium, b.text1)
					gfx.LeftText(TGFX.FontMedium, b.text1, b.x + ((b.width - w) / 2), b.y + 10)
					w = gfx.TextSize(TGFX.FontMedium, b.text2)
					gfx.LeftText(TGFX.FontMedium, b.text2, b.x + ((b.width - w) / 2), b.y + 25)
				End Select
			Else
				Select b.img
				Case 0
					SetScale(0.2, 0.2)
					DrawImage(rleft, b.x + (b.width / 2), b.y + (b.height / 2))
				Case 1
					SetScale(0.2, 0.2)
					DrawImage(rright, b.x + (b.width / 2), b.y + (b.height / 2))
				Case 2
					SetScale(0.2, 0.2)
					DrawImage(del, b.x + (b.width / 2), b.y + (b.height / 2))
				End Select
				SetScale(1.0, 1.0)
			End If
		Next 
		SetAlpha(1.0)
		?debug
   			TProfiler.Leave("Buttons::Render")
  		?
	End Method
End Type

