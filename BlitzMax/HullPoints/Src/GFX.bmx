SuperStrict
Import BaH.Cairo
Import "Int.bmx"
Import "Profiler.bmx"

Type TGFX
	Const FontSmall:Int = 0, FontMediumSmall:Int = 1, FontMedium:Int = 2, FontMediumLarge:Int = 3, FontLarge:Int = 4, FontXLarge:Int = 5, FontXXLarge:Int = 6, FontRadar:Int = 7
	Const FontSmallSize:Double = 9.5, FontMediumSmallSize:Double = 11.0, FontMediumSize:Double = 14.0, FontMediumLargeSize:Double = 17.0
	Const FontLargeSize:Double = 20.0, FontXLargeSize:Double = 30.0, FontXXLargeSize:Double = 75.0, FontRadarSize:Int = 9.5
	Const FontFilenameRaw:String = "Square.ttf"
	Const FontPath:String = "Res/"
	Const FontFilename:String = fontPath + fontFilenameRaw
	Const MaxSizes:Int = 400
	Field fontCache:TImageFont[MaxSizes], standardFontSizes:Int[8], fontWidthCache:TMap[MaxSizes], fontHeightCache:TMap[MaxSizes]
	Field width:Int, height:Int, maxDimension:Int, minDimension:Int, pointer:Int = 0, previousSizeIndex:Int = 0
	Field mouse:TImage, mouseTarget:TImage, mouseTarget2:TImage

	Function Create:TGFX(w:Int, h:Int)
		Local gfx:TGFX = New TGFX
		gfx.width = w
		gfx.height = h
		If w > h Then gfx.maxDimension = w Else gfx.maxDimension = h
		If w > h Then gfx.minDimension = h Else gfx.minDimension = w
		SetGraphicsDriver GLMax2DDriver()
		Graphics(w, h, 0, 60, GRAPHICS_BACKBUFFER)
		AutoMidHandle(True)
		gfx.standardFontSizes[TGFX.FontSmall] = TGFX.FontSmallSize
		gfx.standardFontSizes[TGFX.FontMediumSmall] = TGFX.FontMediumSmallSize
		gfx.standardFontSizes[TGFX.FontMedium] = TGFX.FontMediumSize
		gfx.standardFontSizes[TGFX.FontMediumLarge] = TGFX.FontMediumLargeSize
		gfx.standardFontSizes[TGFX.FontLarge] = TGFX.FontLargeSize
		gfx.standardFontSizes[TGFX.FontXLarge] = TGFX.FontXLargeSize
		gfx.standardFontSizes[TGFX.FontXXLarge] = TGFX.FontXXLargeSize
		SetBlend(ALPHABLEND)
		gfx.mouse = LoadImage("Res/Mouse.png")
		gfx.mouseTarget = LoadImage("Res/MouseTarget.png")
		gfx.mouseTarget2 = LoadImage("Res/MouseTarget2.png")
		SetImageHandle(gfx.mouse, 0, 0)
		GlEnable(GL_LINE_SMOOTH)
		HideMouse()
		Return gfx
	End Function
	
	Method GetFontFromIndex:TImageFont(size:Double)
		?debug
   			TProfiler.Enter("GFX::GetFontFromIndex")
  		?
		previousSizeIndex = Int(size * 2)
		Local f:TImageFont = fontCache[previousSizeIndex]
		If f <> Null Then 
			?debug
   				TProfiler.Leave("GFX::GetFontFromIndex")
  			?
			Return f
		End If
		fontCache[previousSizeIndex] = LoadImageFont(fontFilename, Double(previousSizeIndex	) / 2.0)
		?debug
   			TProfiler.Leave("GFX::GetFontFromIndex")
  		?
		Return fontCache[previousSizeIndex]
	End Method
	
	Method GetCachedFontWidth:Int(s:String)
		?debug
   			TProfiler.Enter("GFX::GetCachedFontWidth")
  		?
		Local m:TMap = fontWidthCache[previousSizeIndex]
		If m = Null Then 
			m = CreateMap()
			fontWidthCache[previousSizeIndex] = m
		End If
		Local r:Object = MapValueForKey(m, s)
		If r = Null Then
			Local o:TInt = TInt.Create(TextWidth(s))
			MapInsert(m, s, o)
			?debug
	   			TProfiler.Leave("GFX::GetCachedFontWidth")
  			?
			Return o.i
		Else
			?debug
   				TProfiler.Leave("GFX::GetCachedFontWidth")
  			?
			Return TInt(r).i
		End If
	End Method
	
	Method GetCachedFontHeight:Int(s:String)
		?debug
   			TProfiler.Enter("GFX::GetCachedFontHeight")
  		?
		Local m:TMap = fontHeightCache[previousSizeIndex]
		If m = Null Then 
			m = CreateMap()
			fontHeightCache[previousSizeIndex] = m
		End If
		Local r:Object = MapValueForKey(m, s)
		If r = Null Then
			Local o:TInt = TInt.Create(TextHeight(s))
			MapInsert(m, s, o)
			?debug
   				TProfiler.Leave("GFX::GetCachedFontHeight")
	  		?
			Return o.i
		Else
			?debug
   				TProfiler.Leave("GFX::GetCachedFontHeight")
	  		?
			Return TInt(r).i
		End If
	End Method
	
	Method SetSpecificFontSize(size:Double)
		SetImageFont(GetFontFromIndex(size))
	End Method

	Method SetFontSize(size:Int)
		SetImageFont(GetFontFromIndex(standardFontSizes[size]))
	End Method

	Method TextSize:Int(size:Int, s:String)
		SetFontSize(size)
		Return GetCachedFontWidth(s)
	End Method

	Method LeftText(size:Int, s:String, x:Int, y:Int)
		SetFontSize(size)
		DrawText(s, x, y)
	End Method

	Method CenteredText(size:Int, s:String, y:Int)
		SetFontSize(size)
		Local w:Int = GetCachedFontWidth(s)
		DrawText(s, (width / 2) - (w / 2), y)
	End Method

	Method UIScanlines()
		?debug
   			TProfiler.Enter("GFX::UIScanLines")
  		?
		SetColor(255, 255, 255)
		SetAlpha(1.0)
		SetScale(1.0, 1.0)
		Select pointer
		Case -1
		Case 0
			DrawImage(mouse, MouseX(), MouseY())
		Case 1
			DrawImage(mouseTarget, MouseX(), MouseY())
		Case 2
			DrawImage(mouseTarget2, MouseX(), MouseY())
		End Select
		pointer = 0
		?debug
   			TProfiler.Leave("GFX::UIScanLines")
  		?
		Return
		SetAlpha(0.25)
		For Local y:Int = 0 To height Step 2
			Local r:Int = 0
			SetColor(0 + r, 0 + r, 0 + r)
			DrawLine(0, y, width, y)
		Next 
		SetAlpha(0.05)
		For Local y:Int = 1 To height Step 2
			Local r:Int = 0
			SetColor(0 + r, 0 + r, 0 + r)
			DrawLine(0, y, width, y)
		Next 
		SetAlpha(1.0)
'		SetAlpha(0.15)
'		For Local x:Int = 0 To width Step 2
'			Local r:Int = 0
'			SetColor(0 + r, 0 + r, 0 + r)
'			DrawLine(x, 0, x, height)
'		Next 
'		SetAlpha(0.05)
'		For Local x:Int = 1 To width Step 2
'			Local r:Int = 0
'			SetColor(0 + r, 0 + r, 0 + r)
'			DrawLine(0, x, width, x)
'		Next 
	End Method

	Method Grid(cols:Int, rows:Int, sizeX:Int, sizeY:Int, selectX:Int, selectY:Int, showGrid:Int)
		If showGrid = 1 Then
			For Local i:Int = 0 To cols
				DrawLine(i * sizeX, 0, i * sizeX, sizeY * rows)
			Next
			For Local i:Int = 0 To rows
				DrawLine(0, i * sizeY, sizeX * cols, i * sizeY)
			Next
		End If
		If selectX <> -1 And selectY <> -1 Then
			SetAlpha(0.75)
			DrawRect(selectX * sizeX, selectY * sizeY, sizeX, sizeY)
		End If
	End Method

	Method GridBox(cols:Int, rows:Int, sizeX:Int, sizeY:Int, selectX:Int, selectY:Int, showGrid:Int)
		If showGrid = 1 Then
			For Local i:Int = 0 To cols
				DrawLine(i * sizeX, 0, i * sizeX, sizeY * rows)
			Next
			For Local i:Int = 0 To rows
				DrawLine(0, i * sizeY, sizeX * cols, i * sizeY)
			Next
		End If
		SetAlpha(0.5)
		If selectX <> -1 And selectY <> -1 Then
			DrawRect(selectX * sizeX, selectY * sizeY, sizeX, sizeY)
		End If
		SetAlpha(1.0)
	End Method
	
	Method GridMajorMinor(cols:Int, rows:Int, sizeX:Double, sizeY:Double, major:Int)
		For Local i:Int = 0 To cols
			If Not (i Mod 10) Then
				SetAlpha(1.0)
				SetLineWidth(2.0)
			Else
				SetAlpha(0.5)
				SetLineWidth(1.0)
			End If
			DrawLine(i * sizeX, 0, i * sizeX, sizeY * rows)
		Next
		For Local i:Int = 0 To rows
			If Not (i Mod 10) Then
				SetAlpha(1.0)
				SetLineWidth(2.0)
			Else
				SetAlpha(0.5)
				SetLineWidth(1.0)
			End If
			DrawLine(0, i * sizeY, sizeX * cols, i * sizeY)
		Next
		SetAlpha(1.0)
		SetLineWidth(1.0)
	End Method
	
End Type
