Strict
Import mojo
Import Globals
Import System.Glfw2
Import Library.GFX
Import World.World

Class TGame Extends App
	Const UPDATE_RATE:Int = 60
	Field fGFX:TGFX, fWorld:TWorld
    
    Method OnCreate:Int()
    	GL_SetWindowSize()
    	SetUpdateRate(UPDATE_RATE)	
    	fGFX = New TGFX()
    	fWorld = New TWorld()
		Return(0)
	End
	
	Method OnUpdate:Int()
		If KeyHit(KEY_ESCAPE) Then 
			#If CONFIG = "debug" And TARGET = "glfw"
				Print "Dumping profile information."
'				TProfiler.DumpLog("/Users/daryl/Desktop/Profiler.txt")		
'				TProfiler.DumpLogCSV("/Users/daryl/Desktop/Profiler.csv")
				TProfiler.DumpLog("D:\Profiler.txt")		
				TProfiler.DumpLogCSV("D:\Profiler.csv")
				Print "Dumped."
			#End			
			EndApp()
		End
		Return(0)
	End
	
	Method OnRender:Int()
		fGFX.Clear()
		Return(0)
	End
End	
	
Function Main:Int()
	GL_SetAA()
	New TGame
	Return 0
End