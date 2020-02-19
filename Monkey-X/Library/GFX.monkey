Strict
Import mojo
Import Library.AppGlobals

Class TGFX
	
	Method New() 
		gScreenWidth = DeviceWidth()
		gHalfScreenWidth = gScreenWidth / 2
		gScreenHeight = DeviceHeight()
		gHalfScreenHeight = gScreenHeight / 2
	End
	
	Method Clear:Void()
		Cls(0, 0, 0)
		SetAlpha(1.0)
		SetColor(255, 255, 255)
	End
End