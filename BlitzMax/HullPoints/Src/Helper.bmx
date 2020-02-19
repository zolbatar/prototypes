SuperStrict
Import "Colour.bmx"
Import "Profiler.bmx"

Function SetPlayerColour(player:Int, colours:TColour[])
	SetColor(colours[player].r, colours[player].g, colours[player].b)
End Function		

Function ListFiles:TList(root:String, ext:String, lst:TList)
	Local dir:Int = ReadDir(root)
	If Not dir Then Return lst
	If Not root.EndsWith("/") Then root :+ "/"
	Repeat
		Local fn:String = NextFile(dir)
		If Not fn Then Exit
		If fn = "." Or fn = ".." Then Continue
		If FileType(root + fn) = FILETYPE_DIR Then
			ListFiles(root + fn, ext, lst)
		Else
			If ExtractExt(fn) = ext Then ListAddLast(lst, root + fn)
		EndIf
	Forever
	CloseDir dir
	Return lst
End Function

Const EPSILON:Double = 0.001
Const EPSILON3:Double = 0.01
Const EPSILON2:Double = 0.1

Function Same:Int(n1:Double, n2:Double)
	Return Abs(n1 - n2) < EPSILON
End Function

Function Same3:Int(n1:Double, n2:Double)
	Return Abs(n1 - n2) < EPSILON
End Function

Function Same2:Int(n1:Double, n2:Double)
	Return Abs(n1 - n2) < EPSILON2
End Function

Function AdjustAngle:Double(angle:Double)	
	While angle < 0
		angle :+ 360
	End While
	Local a1:Double = angle Mod 360
	Return angle
End Function

Function RoundUpDown:Long(n:Double, v:Long, a:Double)
	If n < 0 Then
		Return Long((n - a) / v) * v
	Else
		Return Long((n + a) / v) * v
	End If
End Function

Function RoundDouble:String(n:Double, dps:Int)
	Return Left(n, Instr(n, ".") + dps)
End Function

Function RoundDoubleThousand:String(n:Double, dps:Int)
	If Abs(n) > 1000 Then
		Return String(Long(n / 1000.0)) + "K"
	Else
		Return Left(n, Instr(n, ".") + dps)
	End If
End Function

Function PolarToCartesian(l:Double, deg:Double, xC:Double Var, yC:Double Var)
	?debug
  		TProfiler.Enter("Helper::PolarToCartesian")
 	?
	xC = l * Cos(deg)
	yC = l * Sin(deg)
	?debug
  		TProfiler.Leave("Helper::PolarToCartesian")
 	?
End Function

Function AddPolarToCartesian(l:Double, deg:Double, xC:Double Var, yC:Double Var)
	?debug
  		TProfiler.Enter("Helper::AddPolarToCartesian")
 	?
	Local x:Double, y:Double
	PolarToCartesian(l, deg, x, y)
	xC :+ x
	yC :- y
	?debug
  		TProfiler.Leave("Helper::AddPolarToCartesian")
 	?
End Function

Function AngleBetweenPoints:Double(x1:Double, y1:Double, x2:Double, y2:Double)
	?debug
  		TProfiler.Enter("Helper::AngleBetweenPoints")
 	?
	Local deltaY:Double = y1 - y2
	Local deltaX:Double = x2 - x1
	Local a:Double = ATan2(deltaY, deltaX)
	?debug
  		TProfiler.Leave("Helper::AngleBetweenPoints")
 	?
	Return a
End Function

Function DistanceIsLess:Int(x1:Double, y1:Double, x2:Double, y2:Double, dist:Double)
	?debug
  		TProfiler.Enter("Helper::DistanceIsLess")
 	?
	Local deltaY:Double = y1 - y2
	Local deltaX:Double = x2 - x1
	Local a:Double = (deltaX * deltaX) + (deltaY * deltaY) < (dist * dist)
	?debug
  		TProfiler.Leave("Helper::DistanceIsLess")
 	?
	Return a
End Function

Function DistanceBetweenPoints:Double(x1:Double, y1:Double, x2:Double, y2:Double)
	?debug
  		TProfiler.Enter("Helper::DistanceBetweenPoints")
 	?
	Local deltaY:Double = y1 - y2
	Local deltaX:Double = x2 - x1
	Local a:Double = Sqr((deltaX * deltaX) + (deltaY * deltaY))
	?debug
  		TProfiler.Leave("Helper::DistanceBetweenPoints")
 	?
	Return a
End Function

Function RotateAroundPoint(x:Double Var, y:Double Var, cX:Double, cY:Double, deg:Double)
	?debug
  		TProfiler.Enter("Helper::RotateAroundPoint")
 	?
	Local pX:Double = x - cX;
	Local pY:Double = y - cY;
	x = pX * Cos(deg) - pY * Sin(deg);
	y = pX * Sin(deg) + pY * Cos(deg);
	x :+ cx
	y :+ cy
	?debug
  		TProfiler.Leave("Helper::RotateAroundPoint")
 	?
End Function

Function RotateAroundOrigin(x:Double Var, y:Double Var, deg:Double)
	?debug
  		TProfiler.Enter("Helper::RotateAroundOrigin")
 	?
	Local x2:Double = x
	Local y2:Double = y
	x = x2 * Cos(deg) - y2 * Sin(deg);
	y = x2 * Sin(deg) + y2 * Cos(deg);
	?debug
  		TProfiler.Leave("Helper::RotateAroundOrigin")
 	?
End Function

Function DifferenceBetweenAngles:Double(a1:Double, a2:Double)
	?debug
  		TProfiler.Enter("Helper::DifferenceBetweenAngles")
 	?
	a1 = AdjustAngle(a1)
	a2 = AdjustAngle(a2)
	Local a:Double = AdjustAngle(a2 - a1)
	If a > 180 Then a = a - 360
	?debug
  		TProfiler.Leave("Helper::DifferenceBetweenAngles")
 	?
	Return a
End Function

Function DifferenceBetweenAnglesAbs:Double(a1:Double, a2:Double)
	?debug
  		TProfiler.Enter("Helper::DifferenceBetweenAnglesAbs")
 	?
	Local a:Double = Abs(AdjustAngle(a1) - AdjustAngle(a2))
	?debug
  		TProfiler.Leave("Helper::DifferenceBetweenAnglesAbs")
 	?
	Return a
End Function

