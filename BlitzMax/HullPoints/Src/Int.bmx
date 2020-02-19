SuperStrict 

Type TInt
	Field i:Int
	Function Create:TInt(i:Int)
		Local o:TInt = New TInt
		o.i = i
		Return o
	End Function
End Type

