Strict
Import mojo
Import Globals
Import Pixel

Class TWorld
	Public Const WORLD_WIDTH:Int = 1024, WORLD_HEIGHT:Int = 1024
	Field fWorld:TPixel[]
	
	Method New()
		fWorld = New TPixel[WORLD_WIDTH * WORLD_HEIGHT]
	End
	
End