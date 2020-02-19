Strict
Import mojo
Import Globals

Class TPoint
	Field latitude:Float, longitude:Float
	
	Method New(_longitude:Float, _latitude:Float)
		latitude = _latitude
		longitude = _longitude
	End
End