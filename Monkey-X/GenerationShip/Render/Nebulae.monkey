Strict
Import mojo
Import monkey
Import Library.AppGlobals
Import Globals
Import BackgroundItem

Class TNebulae
	Const NUMBER_IMAGES:Int = 25, DENSITY:Float = 0.00002
	Field fImg:Image[] = New Image[NUMBER_IMAGES]
	Field fList:TBackgroundItem[]
	Field fNumber:Int

	Method New()
		#If CONFIG = "debug"
			TProfiler.Enter("Nebulae::New")
		#End

		' Load renders
		For Local i:Int = 0 Until NUMBER_IMAGES
	    	fImg[i] = LoadImage("images/nebula/Nebula" + (i + 1) + ".png", 1, Image.MidHandle)
	 	Next
		#If CONFIG = "debug"
	 		Print "INIT: " + NUMBER_IMAGES + " nebulae loaded."
 		#End
	 	
	 	' Create galaxies
	 	fNumber = gScreenWidth * gScreenHeight * DENSITY
	 	If (fNumber > NUMBER_IMAGES) Then fNumber = NUMBER_IMAGES
	 	fList = New TBackgroundItem[fNumber]
	 	
	 	For Local i:Int = 0 Until fNumber
	 		Local img:Image = fImg[Rand(0, NUMBER_IMAGES)]
	 		Local size:Float = 1024 + (Rnd() * 1024)
			Local x:Float = (Rnd() * (gScreenWidth + 1000)) - 500
           	Local y:Float = (Rnd() * (gScreenHeight + 1000)) - 500
         	Local g:TBackgroundItem = New TBackgroundItem(x, y, size, img, True, True)
			fList[i] = g
	 	Next

		#If CONFIG = "debug"
			TProfiler.Leave("Nebulae::New")
		#End
	End
	
	Method Render:Void()
		#If CONFIG = "debug"
			TProfiler.Enter("Nebulae::Render")
		#End
		SetAlpha(1.0)
		SetColor(255, 255, 255)
		SetBlend(AdditiveBlend)
		For Local g:TBackgroundItem = Eachin fList
			g.Render()
			
			' Are we off screen?
			If g.fY > gScreenHeight * 2
				g.fX = (Rnd() * (gScreenWidth + 1000)) - 500
				g.fY = -(gScreenHeight)
		 		g.fImage = fImg[Rand(0, NUMBER_IMAGES)]
			End
		Next
		SetBlend(AlphaBlend)
		#If CONFIG = "debug"
			TProfiler.Leave("Nebulae::Render")
		#End
	End
	
End