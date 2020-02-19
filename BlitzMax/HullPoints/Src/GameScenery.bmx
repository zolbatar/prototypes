SuperStrict 
Import "Helper.bmx"

Type TGameScenery
	Const TypePlanet:Int = 0, TypeAsteroid:Int = 1
	Field name:String, t:Int, index:Int, objectType:Int, size:Double, x:Double, y:Double, tX:Double, tY:Double, angle:Double
	Field speed:Double, rotVel:Double, heading:Double
	
	Function Create:TGameScenery(_name:String, _t:Int, _index:Int, _type:Int, _size:Double, _x:Double, _y:Double, _r:Double = 0.0)
		Local gs:TGameScenery = New TGameScenery
		gs.name = _name
		gs.t = _t
		gs.index = _index
		gs.objecttype = _type
		gs.size = _size
		gs.x = _x
		gs.y = _y
		gs.angle = _r
		gs.rotVel = Rnd(1.0, 15.0) - 8.0
		gs.speed = Rand(5, 15)
		gs.heading = Rand(0, 359)
		Return gs
	End Function
	
	Method Animate(timeSeconds:Double)
		AddPolarToCartesian(speed * timeSeconds, heading, x, y)
	End Method
	
End Type



