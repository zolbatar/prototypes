Strict
Import mojo
Import Library.AppGlobals
Import Globals
Import brl.filestream
Import brl.filesystem
Import Country
Import Portion
Import Point

Class TGIS
	Field fCountries:StringMap<TCountry> = New StringMap<TCountry>()
	
	Method Load:Void()
		#If CONFIG = "debug"
			TProfiler.Enter("GIS::Load")
		#End
		For Local s:String = Eachin LoadDir("data/GIS", False, False)
			Local sa:String[] = s.Split(".txt")
			LoadCountry(sa[0])
		Next
		#If CONFIG = "debug"
			TProfiler.Leave("GIS::Load")
		#End
	End
	
	Method LoadCountry:Void(filename:String)
		#If CONFIG = "debug"
			TProfiler.Enter("GIS::LoadCountry")
		#End
		Local f:FileStream = FileStream.Open("data/GIS/" + filename + ".txt", "r")
		If f = Null Then
			Print "Error opening GIS file: " + filename
		Else
			Local country:TCountry = New TCountry()
			Local portion:TPortion = New TPortion()
			Local px:Float, py:Float, previous:Bool = false
			While Not f.Eof()
				Local s:String = f.ReadLine()
				If s = "---" Then
					country.fPortions.AddLast(portion)
					portion = New TPortion()
					previous = False
				Else
					Local ps:String[] = s.Split(",")
					Local x:Float = (Int(Float(ps[1]) * gInitialRound) / gInitialRound) 
					Local y:Float = (Int(Float(ps[0]) * gInitialRound) / gInitialRound)
					Local p:TPoint = New TPoint(x, y)
'					If previous Then
'						If x <> px And y <> py Then
'							portion.fPoints.AddLast(p)
'						End
'					Else
'						portion.fPoints.AddLast(p)
'					End
					portion.fPoints.AddLast(p)
					previous = True
					px = x
					py = y
				End
			End
			country.fPortions.AddLast(portion)
			fCountries.Add(filename, country)
			Print "Loaded GIS file: " + filename
			f.Close()
		End
		#If CONFIG = "debug"
			TProfiler.Leave("GIS::LoadCountry")
		#End
	End
	
	Method Render:Void()
		#If CONFIG = "debug"
			TProfiler.Enter("GIS::Render")
		#End
		Local x:Float, y:Float, pr1:Int = 0, pr2:Int = 0
		For Local c:TCountry = Eachin fCountries.Values()
			For Local p:TPortion = Eachin c.fPortions
				Local i:Int = 0
				For Local po:TPoint = Eachin p.fPoints
					Local pt:TPoint = Translate(po)
					If i = 0 Then
						x = pt.longitude
						y = pt.latitude
					Else
						If pt.longitude = x And pt.latitude = y Then
							pr1 += 1
						Else
							DrawLine x, y, pt.longitude, pt.latitude
							x = pt.longitude
							y = pt.latitude
							pr2 += 1
						End
					End
					i += 1
				Next
			Next
		Next 
		Print "Rendered " + pr2 + ", ignored " + pr1
		#If CONFIG = "debug"
			TProfiler.Leave("GIS::Render")
		#End
	End
	
	Method Translate:TPoint(p:TPoint)
		#If CONFIG = "debug"
			TProfiler.Enter("GIS::Translate")
		#End
		Local x:Float = (Int(p.longitude * gRound) / gRound) * gScale + gCentreX + gHalfScreenWidth 
		Local y:Float = -(Int(p.latitude * gRound) / gRound) * gScale + gCentreY + gHalfScreenHeight 
		Local po:TPoint = New TPoint(x, y)
		#If CONFIG = "debug"
			TProfiler.Leave("GIS::Translate")
		#End
		Return po
	End

End