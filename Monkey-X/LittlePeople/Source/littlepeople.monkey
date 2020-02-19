Strict
Import mojo
Import monkey
Import Globals
Import Library.AppGlobals
Import Library.Glfw2
Import Library.GFX

Class TGame Extends App
	Const UPDATE_RATE:Int = 60
	Field fGFX:TGFX
	Const MAXIMUM_WIDTH:Int = 8, MAXIMUM_HEIGHT:Int = 8, NUMBER_IMAGES:Int = 6, NUMBER_FOUNDATION:Int = 1
	Field fImage:Image[NUMBER_IMAGES], fMap:Int[MAXIMUM_WIDTH * MAXIMUM_HEIGHT]
    
    Method OnCreate:Int()
	    Seed = Millisecs()
    	GL_SetWindowSize()
    	SetUpdateRate(UPDATE_RATE)
    	fGFX = New TGFX()
    	fImage[0] = LoadImage("Tiles/Kerb/Kerb-a.png", 1, Image.MidHandle)
    	fImage[1] = LoadImage("Tiles/Road/Road-a.png", 1, Image.MidHandle)
    	fImage[2] = LoadImage("Tiles/Grass/Grass-a.png", 1, Image.MidHandle)
    	fImage[3] = LoadImage("Tiles/Tree/Tree-a.png", 1, Image.MidHandle)
    	fImage[4] = LoadImage("Tiles/TreeBunch/TreeBunch-a.png", 1, Image.MidHandle)
    	fImage[5] = LoadImage("Tiles/KerbBush/KerbBush-a.png", 1, Image.MidHandle)
    	SetMap()
		Return(0)
	End
	
	Method OnUpdate:Int()
		If KeyHit(KEY_ESCAPE) Then 
			#If CONFIG = "debug" And TARGET = "glfw"
				Print "Dumping profile information."
				TProfiler.DumpLog("/Users/daryl/Desktop/Profiler.txt")		
				TProfiler.DumpLogCSV("/Users/daryl/Desktop/Profiler.csv")
				Print "Dumped."
			#End			
			EndApp()
		End
		Return(0)
	End
	
	Method OnRender:Int()
		fGFX.Clear()
		RenderTiles(1.0, gHalfScreenWidth + 200, gHalfScreenHeight + 400, 3, 3)
		Return(0)
	End
	
	Method SetMap:Void() 
		For Local y:Int = 0 Until MAXIMUM_HEIGHT
			For Local x:Int = 0 Until MAXIMUM_WIDTH
				SetTile(x, y, (Rnd() * (NUMBER_IMAGES - NUMBER_FOUNDATION)) + NUMBER_FOUNDATION)
			Next
		Next
	End
	
	Method GetTile:Int(x:Int, y:Int)
		Return fMap[(y * MAXIMUM_WIDTH) + x]
	End
	
	Method SetTile:Void(x:Int, y:Int, tile:Int)
		fMap[(y * MAXIMUM_WIDTH) + x] = tile
	End

	Method RenderTiles:Void(zoom:Float, xStart:Int, yStart:Int, xRange:Int, yRange:Int)
		Local sX:Float = 216 * zoom, sY:Float = sX * 0.5
		For Local y:Int = yRange To 0 Step -1
			For Local x:Int = xRange To 0 Step -1
				Local idx:Int = GetTile(x, y)
				Select idx
					Case 5
						DrawImage(fImage[0], xStart + (sX * x - (y * sX)), yStart - (sY * x + (y * sY)), 0.0, zoom, zoom)
					Case 3,4
						DrawImage(fImage[2], xStart + (sX * x - (y * sX)), yStart - (sY * x + (y * sY)), 0.0, zoom, zoom)
				End
				Local img:Image = fImage[idx]
				DrawImage(img, xStart + (sX * x - (y * sX)), yStart - (sY * x + (y * sY)), 0.0, zoom, zoom)
			Next
		Next
	End
End	
	
Function Main:Int()
	GL_SetAA()
	New TGame
	Return 0
End
