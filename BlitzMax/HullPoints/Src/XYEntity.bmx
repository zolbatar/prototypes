SuperStrict
Import "GameEntity.bmx"

Type TXYEntity
	Field x:Int, y:Int, t:Long, s:Double
	
	Function Create:TXYEntity(x:Int, y:Int, t:Long, s:Double)
		Local o:TXYEntity = New TXYEntity
		o.x = x
		o.y = y
		o.t = t
		o.s = s
		Return o
	End Function
End Type

