Strict
Import mojo
Import monkey
Import Library.AppGlobals
Import Globals

Class TStar
	Const MOVEMENT_SPEED:Float = 0.15
	Const COLOUR_BASE:Int = 128, COLOUR_ADJUST:Int = 127
	Field fX:Float, fY:Float, fSize:Float, fDepth:Float, fImage:Image
	Field fR:Float, fG:Float, fB:Float
	
	Method New(x:Float, y:Float)
		fX = x
		fY = y
		fSize = Rnd() * 1.25 + 0.25
		fDepth = Rnd() * 0.9 + 0.1
		fR = Rand(0, COLOUR_ADJUST) + COLOUR_BASE
		fG = Rand(0, COLOUR_ADJUST) + COLOUR_BASE
		fB = Rand(0, COLOUR_ADJUST) + COLOUR_BASE
	End
	
	Method Render:Void() 
		#If CONFIG = "debug"
			TProfiler.Enter("Star::Render")
		#End
		SetColor(fR, fG, fB)
		SetAlpha(fDepth)
		DrawCircle(fX, fY, fSize)
		fY += gCurrentVelocity * fDepth * MOVEMENT_SPEED
		#If CONFIG = "debug"
			TProfiler.Leave("Star::Render")
		#End
	End

End