Strict
Import mojo
Import monkey
Import Library.AppGlobals
Import Globals
Import Star

Class TStars
	Const DENSITY:Float = 0.0005
	Field fStars:TStar[], fNumber:Int

	Method New()
		#If CONFIG = "debug"
			TProfiler.Enter("Stars::New")
		#End
		fNumber = gScreenWidth * gScreenHeight * DENSITY
		fStars = New TStar[fNumber]
		For Local i:Int = 0 Until fNumber
			Local x:Float = Rnd() * gScreenWidth
			Local y:Float = Rnd() * gScreenHeight
			Local s:TStar = New TStar(x, y)
			fStars[i] = s
		Next
		#If CONFIG = "debug"
			TProfiler.Leave("Stars::New")
		#End
	End
	
	Method Render:Void() 
		#If CONFIG = "debug"
			TProfiler.Enter("Stars::Render")
		#End
		For Local i:Int = 0 Until fNumber
			Local s:TStar = fStars[i]
			s.Render()

			' Are we off screen?
			If s.fY > gScreenHeight + s.fSize
				s.fX = Rnd() * gScreenWidth
				s.fY = -s.fSize
			End
		Next
		#If CONFIG = "debug"
			TProfiler.Leave("Stars::Render")
		#End
	End

End