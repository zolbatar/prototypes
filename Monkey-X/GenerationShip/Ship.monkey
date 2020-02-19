Strict
Import mojo
Import monkey
Import Globals

Class TShip
	Const NUMBER_SECTIONS:Int = 4
	Field fImgSections:Image[]

	Method New() 
		#If CONFIG = "debug"
			TProfiler.Enter("Ship::New")
		#End

		fImgSections = New Image[NUMBER_SECTIONS]
		For Local i:Int = 0 Until NUMBER_SECTIONS
	    	fImgSections[i] = LoadImage("images/sections/Section" + (i + 1) + ".png", 1, Image.MidHandle)
	 	Next
		#If CONFIG = "debug"
	 		Print "INIT: " + NUMBER_SECTIONS + " sections loaded."
 		#End

		#If CONFIG = "debug"
			TProfiler.Leave("Ship::New")
		#End
	End
	
	Method Render:Void()
		#If CONFIG = "debug"
			TProfiler.Enter("Ship::Render")
		#End
		SetAlpha(1.0)
		SetColor(255, 255, 255)
		DrawImage(fImgSections[0], 64, 128)
		DrawImage(fImgSections[1], 128, 128)
		DrawImage(fImgSections[2], 64, 64)
		DrawImage(fImgSections[3], 128, 64)
		#If CONFIG = "debug"
			TProfiler.Leave("Ship::Render")
		#End
	End

End