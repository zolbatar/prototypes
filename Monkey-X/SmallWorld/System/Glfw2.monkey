Strict

Extern
    Function glfwOpenWindowHint:Void(target:Int, hint:Int)
    Function glfwSetWindowSize:Void(width:Int, height:Int)
    Function glfwSetWindowPos:Void(x:Int, y:Int)
    Function glfwEnable:Void(feature:Int)
    Function glfwDisable:Void(feature:Int)
Public

Const GL_TRUE:Int  = 1
Const GL_FALSE:Int = 0
Const GLFW_STEREO:Int           = $00020011
Const GLFW_WINDOW_NO_RESIZE:Int = $00020012
Const GLFW_FSAA_SAMPLES:Int     = $00020013	
Const GLFW_FULLSCREEN:Int       = $00010002
Const GLFW_MOUSE_CURSOR:Int		= $00030001
Const GLFW_CURSOR_NORMAL:Int	= $00034001
Const GLFW_CURSOR_HIDDEN:Int    = $00034002
Const GLFW_CURSOR_DISABLED:Int  = $00034003

Function GL_SetAA:Void()
	#If TARGET = "glfw"
		glfwOpenWindowHint(GLFW_FSAA_SAMPLES, 8)
	#End	
End
	
Function GL_SetWindowSize:Void()
	#If TARGET = "glfw"
		glfwSetWindowPos(0, 0)
    	glfwSetWindowSize(1366, 768)
'		glfwDisable(GLFW_MOUSE_CURSOR);
    #End	
End

