SuperStrict

Type TScriptItem
	Const ScriptJumpIn:Int = 0, ScriptJumpOut:Int = 1, ScriptTypes:Int = 2
	Field t:Int, time:Long, stage:Int = 0
	
	Function Create:TScriptItem(t:Int, time:Long)
		Local o:TScriptItem = New TScriptItem
		o.t = t
		o.time = time
		Return o
	End Function

	Function ReturnScriptName:String(p:Int)
		Select p
		Case ScriptJumpIn
			Return "Jump In"
		Case ScriptJumpOut
			Return "Jump Out"
		End Select
	End Function
	
	Function ReturnScriptDescription:String(p:Int)
		Select p
		Case ScriptJumpIn
			Return "Jump into the battle at a specified time and location."
		Case ScriptJumpOut
			Return "Jump out of the battle at a specified time."
		End Select
	End Function
End Type
