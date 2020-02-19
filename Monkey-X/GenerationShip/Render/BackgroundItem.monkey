Strict
Import mojo
Import Globals

Class TBackgroundItem
	Const MOVEMENT_SPEED:Float = 0.1
	Field fX:Float, fY:Float, fSize:Float, fScale:Float, fRotation:Float, fRotationDelta:Float, fDepth:Float, fImage:Image, fMoves:Bool
	
	Method New(x:Float, y:Float, size:Float, image:Image, blend:Bool, moves:Bool)
		fX = x
		fY = y
		fMoves = moves
		fSize = size
		fScale = size / image.Width()
		fImage = image
		fRotation = Rnd() * 360
		fRotationDelta = (Rnd() * 0.01) - 0.005
		If blend Then fDepth = 0.25 + (Rnd() * 0.0) Else fDepth = 1.0
	End
	
	Method Render:Void()
		#If CONFIG = "debug"
			TProfiler.Enter("BackgroundItem::Render")
		#End
		SetAlpha(fDepth)
		DrawImage(fImage, fX, fY, fRotation, fScale, fScale)
		If fMoves
			fY += gCurrentVelocity * fDepth * MOVEMENT_SPEED
		Else
			fRotation += fRotationDelta
		End
		SetAlpha(1.0)
		#If CONFIG = "debug"
			TProfiler.Leave("BackgroundItem::Render")
		#End
	End
End