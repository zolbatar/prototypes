SuperStrict

Type TLength
	Field time:Int
End Type

Type TCall
	Field name:String
	Field start:Int
	Field times:TList
	Field calls:Int
	Method New()
		times = CreateList()
	End Method
End Type

Type TProfiler
	Global calls:TMap = CreateMap()

	Function DumpLog( file:String )
		Local fi:TStream = WriteFile( file )
			WriteLine fi,"Profiler Log V1.0"
			For Local c:TCall = EachIn MapValues(calls)
				WriteLine fi,"---------------------"
				Local totTime:Int = 0
				For Local t:TLength = EachIn c.times
					totTime :+ t.time
				Next
				WriteLine fi,"Function:" + C.name + " Calls:" + c.calls + " Total:" + TotTime + " Avg:" + Float(TotTime)/Float(c.calls)
				WriteLine fi,"Total (Seconds):"+String( Float(tottime)/Float(1000) )
				WriteLine fi,"Avg (Seconds):"+String( (Float(TotTime)/Float(c.calls) ) / Float(1000) )
			Next
		CloseFile fi	
	End Function
			
	Function DumpLogCSV( file:String )
		Local fi:TStream = WriteFile( file )
			WriteLine fi, "Function,Calls,Total,Average"
			For Local c:TCall = EachIn MapValues(calls)
				Local totTime:Int = 0
				For Local t:TLength = EachIn c.times
					totTime :+ t.time
				Next
				WriteLine fi, C.name + "," + c.calls + "," + Float(tottime) + "," + (Float(TotTime)/Float(c.calls))
			Next
		CloseFile fi	
	End Function

	Function Enter( func:String )
		Local call:TCall = TCall(MapValueForKey(calls, func))
		If call = Null Then 
			call = New TCall
			call.name = func
			MapInsert(calls, func, call)
		End If
		call.start = MilliSecs()
		call.calls:+1
	End Function

	Function Leave( func:String )
		Local call:TCall = TCall(MapValueForKey(calls, func))
		If call = Null Then RuntimeError "Unknown function"
		Local l:TLength = New tlength
		l.time = MilliSecs()-call.start
		call.times.AddFirst(l)
	End Function
End Type

?debug
	OnEnd( EndHook )

	Function EndHook()
		Print "Dumping profile information."
		TProfiler.DumpLog("Profiler.txt")
		TProfiler.DumpLogCSV("Profiler.csv")
		Print "Dumped."
	End Function
?
