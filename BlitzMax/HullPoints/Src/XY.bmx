SuperStrict

Type TXY
	Field x:Int, y:Int
	
	Function Create:TXY(x:Int, y:Int)
		Local o:TXY = New TXY
		o.x = x
		o.y = y
		Return o
	End Function
End Type
