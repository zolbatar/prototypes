Strict
Import mojo
Import monkey
Import Library.AppGlobals
Import Globals
Import BackgroundItem

Class TGalaxies
	Const NUMBER_IMAGES:Int = 14, DENSITY:Float = 0.0000075
	Field fImg:Image[] = New Image[NUMBER_IMAGES]
	Field fList:TBackgroundItem[]
	Field fNumber:Int

	Method New()
		#If CONFIG = "debug"
			TProfiler.Enter("Galaxies::New")
		#End

		' Load renders
		For Local i:Int = 0 Until NUMBER_IMAGES
	    	fImg[i] = LoadImage("images/galaxy/Galaxy" + (i + 1) + ".png", 1, Image.MidHandle)
	 	Next
		#If CONFIG = "debug"
	 		Print "INIT: " + NUMBER_IMAGES + " galaxies loaded."
 		#End
	 	
	 	' Create galaxies
	 	fNumber = gScreenWidth * gScreenHeight * DENSITY
	 	If (fNumber > NUMBER_IMAGES) Then fNumber = NUMBER_IMAGES
	 	fList = New TBackgroundItem[fNumber]
	 	
	 	' Store numbers so we don't use the same galaxy image twice
	 	Local gn:IntList = New IntList()
	 	For Local i:Int = 0 Until NUMBER_IMAGES
			gn.AddLast(i) 	
	 	Next
	 	
	 	For Local i:Int = 0 Until fNumber
	 		' Work out image to use
	 		Local n:Int = Rand(0, gn.Count())
	 		Local img:Image = fImg[n]
	 		gn.RemoveEach(n)
	 		Local size:Float = 16 + (Rnd() * (200))
	 		
	 		' Are we too close to others?
	 		Local want:Bool, x:Float, y:Float
	 		Repeat
	 			x = (Rnd() * (gScreenWidth - 100)) + 50
	 			y = (Rnd() * (gScreenHeight - 100)) + 50
	 			
	 			want = True
	 			For Local j:Int = 0 Until i
					Local g:TBackgroundItem = fList[j]
	 				Local dist:Float = DistanceBetweenPoints(x, y, g.fX, g.fY)
	 				If dist < (g.fSize + size) * 0.75 Then want = False; Continue
	 			Next
	 		Until want
			Local g:TBackgroundItem = New TBackgroundItem(x, y, size, img, False, False)	
			fList[i] = g
	 	Next

		#If CONFIG = "debug"
			TProfiler.Leave("Galaxies::New")
		#End
	End
	
	Method Render:Void()
		#If CONFIG = "debug"
			TProfiler.Enter("Galaxies::Render")
		#End
		SetAlpha(1.0)
		SetColor(255, 255, 255)
		For Local g:TBackgroundItem = Eachin fList
			g.Render()
		Next
		#If CONFIG = "debug"
			TProfiler.Leave("Galaxies::Render")
		#End
	End
	
End