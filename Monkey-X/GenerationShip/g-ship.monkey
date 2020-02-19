Strict
Import mojo
Import Globals
Import Library.Glfw2
Import Library.GFX
Import Library.AppGlobals
Import Render.Galaxies
Import Render.Nebulae
Import Render.Stars
Import Ship

Class TGame Extends App
	Const UPDATE_RATE:Int = 60
	Field fGFX:TGFX
	Field fGalaxies:TGalaxies, fNebulae:TNebulae, fStars:TStars
	Field fShip:TShip
    
    Method OnCreate:Int()
    	GL_SetWindowSize()
    	SetUpdateRate(UPDATE_RATE)	
    	fGFX = New TGFX()
    	fGalaxies = New TGalaxies()
    	fNebulae = New TNebulae()
    	fStars = New TStars()
    	fShip = New TShip()
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
		fGalaxies.Render()
		fNebulae.Render()
		fStars.Render()
'		fShip.Render()
		Return(0)
	End
End	
	
Function Main:Int()
	GL_SetAA()
	New TGame
	Return 0
End
