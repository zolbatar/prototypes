Strict
Import Library.Profiler

Global gScreenWidth:Int, gScreenHeight:Int, gHalfScreenWidth:Int, gHalfScreenHeight:Int

Function Rand:Int(vmin:Int, vmax:Int)
     Return Rnd(vmin, vmax+1)
End Function

Function PolarToCartesian:TPoint(l:Float, deg:Float)
	#If CONFIG = "debug"
		TProfiler.Enter("Globals::PolarToCartesian")
	#End
	Local o:TPoint = New TPoint
	o.x = l * Cos(deg)
	o.y = l * Sin(deg)
	#If CONFIG = "debug"
		TProfiler.Leave("Globals::PolarToCartesian")
	#End
	Return o
End Function

Function DistanceIsLess:Bool(x1:Float, y1:Float, x2:Float, y2:Float, dist:Float)
	#If CONFIG = "debug"
		TProfiler.Enter("Globals::DistanceIsLess")
	#End
	Local deltaY:Float = y1 - y2
	Local deltaX:Float = x2 - x1
	Local a:Bool = (deltaX * deltaX) + (deltaY * deltaY) < (dist * dist)
	#If CONFIG = "debug"
		TProfiler.Leave("Globals::DistanceIsLess")
	#End
	Return a
End Function

Function DistanceBetweenPoints:Float(x1:Float, y1:Float, x2:Float, y2:Float)
	#If CONFIG = "debug"
		TProfiler.Enter("Globals::DistanceBetweenPoints")
	#End
	Local deltaY:Float = y1 - y2
	Local deltaX:Float = x2 - x1
	Local a:Float = Sqrt((deltaX * deltaX) + (deltaY * deltaY))
	#If CONFIG = "debug"
		TProfiler.Leave("Globals::DistanceBetweenPoints")
	#End
	Return a
End Function
