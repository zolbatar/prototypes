Strict
Import mojo
Import Library.Profiler
Import Globals

Class TInput
	Field fDragging:Bool = False, fDragStartX:Float, fDragStartY:Float

	Method Check:Void()
		#If CONFIG = "debug"
			TProfiler.Enter("Input::Check")
		#End

		' Dragging map?
		If MouseDown(MOUSE_LEFT)
			If Not fDragging Then
				fDragStartX = MouseX()
				fDragStartY = MouseY()
				fDragging = True
			Else
				gCentreX -= (fDragStartX - MouseX()) * gScale / gScrollVal
				gCentreY -= (fDragStartY - MouseY()) * gScale / gScrollVal
				fDragStartX = MouseX()
				fDragStartY = MouseY()
			End If
		Else
			fDragging = False
		End
		
		' Zoom?
		If KeyHit(KEY_MINUS) Then
			gScale /= 1.1
		Else If KeyHit(KEY_EQUALS) Then
			gScale *= 1.1
		End

		#If CONFIG = "debug"
			TProfiler.Leave("Input::Check")
		#End
	End
	
End