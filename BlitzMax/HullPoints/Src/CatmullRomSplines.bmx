SuperStrict
Import "Helper.bmx"

Type TPoint
	Field x:Double, y:Double
	
	Function Create:TPoint(x:Double, y:Double)
		Local o:TPoint=New TPoint
		o.x = x
		o.y = y
		Return o
	End Function
End Type

'Spline type
Type TRomSpline
	Field points:TList = CreateList()
	
	Method AddPoint(p:TPoint) 'Call this to add a point to the end of the list
		points.addlast p
	End Method
	
	Method Draw()
		Local num:Int = points.count()
		If num < 4 Then Return
		
		' Get first 3 points
		Local pl:TLink = points.firstlink()
		Local p0:TPoint = TPoint(pl.value() )
		pl = pl.nextlink()
		Local p1:TPoint = TPoint(pl.value() )
		pl = pl.nextlink()
		Local p2:TPoint = TPoint(pl.value() )
		pl = pl.nextlink()
		Local a:Double = 1.0
		While pl <> Null 
			Local p3:TPoint = TPoint(pl.value() )
			Local ox:Double = p1.x
			Local oy:Double = p1.y
			Local d:Double = DistanceBetweenPoints(p0.x, p0.y, p1.x, p1.y) + DistanceBetweenPoints(p1.x, p1.y, p2.x, p2.y) + DistanceBetweenPoints(p2.x, p2.y, p3.x, p3.y)
'			Local aD:Double = 0.0005 * d
			Local aD:Double = 0.2
			For Local t:Double = 0 To 1 Step .01
				SetAlpha(a)
				Local x:Double = .5 * ( (2 * p1.x) + (p2.x - p0.x) * t + (2 * p0.x - 5 * p1.x + 4 * p2.x - p3.x) * t * t + (3 * p1.x - p0.x - 3 * p2.x + p3.x) * t * t * t)
				Local y:Double = .5 * ( (2 * p1.y) + (p2.y - p0.y) * t + (2 * p0.y - 5 * p1.y + 4 * p2.y - p3.y) * t * t + (3 * p1.y - p0.y - 3 * p2.y + p3.y) * t * t * t)
				DrawLine(ox, oy, x, y)
				ox = x
				oy = y
			Next
			a :- aD
			
			' Move one place along the list
			p0 = p1
			p1 = p2
			p2 = p3
			pl = pl.nextlink()
		Wend
	End Method
End Type
