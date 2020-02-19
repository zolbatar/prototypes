Strict
Import mojo.app
Import monkey.list
Import monkey.map
#If TARGET = "glfw" 
	Import brl.filestream
#End

Class TLength
	Field fTime:Int
	
	Method New()
	End
End

Class TCall
	Field fName:String
	Field fStart:Int
	Field fTimes:List<TLength>
	Field fCalls:Int
	
	Method New()
		fTimes = New List<TLength>
	End
End

Class TProfiler
	Global calls:StringMap<TCall> = New StringMap<TCall>

	Function DumpLog:Void(file:String)
		#If TARGET = "glfw"
			Local fi:FileStream = FileStream.Open(file, "w")
				For Local c:TCall = Eachin calls.Values()
					Local totTime:Int = 0
					For Local t:TLength = Eachin c.fTimes
						totTime = totTime + t.fTime
					Next
					fi.WriteString "Function:" + c.fName + " Calls:" + c.fCalls + " Total:" + totTime + " Avg:" + Float(totTime)/Float(c.fCalls) + "~n"
					fi.WriteString "Total (Seconds):"+String( Float(totTime)/Float(1000)) + "~n"
					fi.WriteString "Avg (Seconds):"+String( (Float(totTime)/Float(c.fCalls) ) / Float(1000)) + "~n"
				Next
			fi.Close
		#End
	End
			
	Function DumpLogCSV:Void(file:String)
		#If TARGET = "glfw" 
			Local fi:FileStream = FileStream.Open(file, "w")
				fi.WriteLine "Function,Calls,Total,Average"
				For Local c:TCall = Eachin calls.Values()
					Local totTime:Int = 0
					For Local t:TLength = Eachin c.fTimes
						totTime = totTime + t.fTime
					Next
					fi.WriteString c.fName + "," + c.fCalls + "," + Float(totTime) + "," + (Float(totTime)/Float(c.fCalls)) + "~n"
				Next
			fi.Close
		#Endif
	End

	Function Enter:Void(func:String)
		#If TARGET = "glfw" 
			Local call:TCall = TCall(calls.Get(func))
			If call = Null Then 
				call = New TCall
				call.fName = func
				Local a:Bool = calls.Add(func, call)
			End If
			call.fStart = Millisecs()
			call.fCalls = call.fCalls + 1
		#End
	End

	Function Leave:Void(func:String)
		#If TARGET = "glfw" 
			Local call:TCall = TCall(calls.Get(func))
			If call = Null Then 
				Print "Unknown function"
				EndApp()
			End
			Local l:TLength = New TLength
			l.fTime = Millisecs() - call.fStart
			call.fTimes.AddFirst(l)
		#End
	End
End