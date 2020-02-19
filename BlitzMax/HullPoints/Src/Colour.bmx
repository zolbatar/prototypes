SuperStrict

Type TColour
	Field r:Int, g:Int, b:Int
	
	Function Create:TColour(r:Int, g:Int, b:Int)
		Local o:TColour = New TColour
		o.r = r
		o.g = g
		o.b = b
		Return o
	End Function

End Type


