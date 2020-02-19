Strict
Import mojo
Import Globals
Import Library.Glfw2
Import Library.GFX
Import GIS.GIS
Import Input

Class TGame Extends App
	Const UPDATE_RATE:Int = 60
	Field fGFX:TGFX, fGIS:TGIS, fInput:TInput
    
    Method OnCreate:Int()
    	GL_SetWindowSize()
    	SetUpdateRate(UPDATE_RATE)	
    	fGFX = New TGFX()
    	fGIS = New TGIS()
    	fGIS.Load()
    	fInput = New TInput()
		Return(0)
	End
	
	Method OnUpdate:Int()
		If KeyHit(KEY_ESCAPE) Then 
			#If CONFIG = "debug" And TARGET = "glfw"
				Print "Dumping profile information."
				TProfiler.DumpLog("/Users/daryl/Desktop/Profiler.txt")		
				TProfiler.DumpLogCSV("/Users/daryl/Desktop/Profiler.csv")
'				TProfiler.DumpLog("D:\Profiler.txt")		
'				TProfiler.DumpLogCSV("D:\Profiler.csv")
				Print "Dumped."
			#End			
			EndApp()
		End
		fInput.Check()
		Return(0)
	End
	
	Method OnRender:Int()
		fGFX.Clear()
		fGIS.Render()
'		If gRound < 2.0 Then
'			gRound *= 1.025
'		Else
'			EndApp()
'		End
		Return(0)
	End
End	
	
Function Main:Int()
	GL_SetAA()
	New TGame
	Return 0
End
