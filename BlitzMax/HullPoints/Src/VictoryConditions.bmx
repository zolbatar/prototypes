SuperStrict

Type TVictoryConditions
	Const VictoryAnnihilation:Int = 0, VictoryHoldout:Int = 1, VictoryProtect:Int = 2, VictoryTypes:Int = 3

	Function ReturnVictoryName:String(p:Int)
		Select p
		Case VictoryAnnihilation
			Return "Annihilation"
		Case VictoryHoldout
			Return "Dig In And Hold"
		Case VictoryProtect
			Return "Protect"
		End Select
	End Function
	
	Function ReturnVictoryDescription:String(p:Int)
		Select p
		Case VictoryAnnihilation
			Return "The battle isn't concluded until every enemy asset is destroyed!"
		Case VictoryHoldout
			Return "Secure the target position (at least one vessel within 5km) and hold it."
		Case VictoryProtect
			Return "Protect the chosen vessel(s) until the timed end."
		End Select
	End Function
End Type
