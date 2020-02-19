Const OrderHeading:Int = 0
Const OrderMove:Int = 1
Const OrderAccelerate:Int = 2
Const OrderFire:Int = 3
Const OrderPursue:Int = 4

Type TOrder
	Field t:Int = 0, x:Float, y:Float, percent:Float, start:Long, playerNo:Int, rate:Double
	Field heading:Double, target:TGameEntity, level:Int, autoDirection:Int, distance:Double, nextOrder:Int = 0, removeWhenArrived:Int = 0
	Field lastUpdate:Long = -1
	
	Function CreateMoveOrder:TOrder(x:Float, y:Float, percent:Float)
		Local o:TOrder = New TOrder
		o.t = OrderMove
		o.x = x
		o.y = y
		o.percent = percent
		Return o		
	End Function

	Function CreateHeadingOrder:TOrder(x:Float, y:Float)
		Local o:TOrder = New TOrder
		o.t = OrderHeading
		o.x = x
		o.y = y
		Return o		
	End Function

	Function CreateFireOrder:TOrder(t:TGameEntity, level:Int, autoDirection:Int, playerNo:Int, rate:Double)
		Local o:TOrder = New TOrder
		o.t = OrderFire
		o.target = t
		o.level = level
		o.playerNo = playerNo
		o.rate = rate
		o.autoDirection = autoDirection
		Return o		
	End Function

	Function CreateFireOrderXY:TOrder(x:Double, y:Double, level:Int, autoDirection:Int, playerNo:Int, rate:Double)
		Local o:TOrder = New TOrder
		o.t = OrderFire
		o.target = Null
		o.x = x
		o.y = y
		o.level = level
		o.playerNo = playerNo
		o.rate = rate
		o.autoDirection = autoDirection
		Return o		
	End Function

	Function CreatePursueOrder:TOrder(t:TGameEntity, distance:Double)
		Local o:TOrder = New TOrder
		o.t = OrderPursue
		o.target = t
		o.distance = distance
		Return o		
	End Function

	Function CreateAccelerateOrder:TOrder(percent:Float)
		Local o:TOrder = New TOrder
		o.t = OrderAccelerate
		o.percent = percent
		Return o		
	End Function
	
	Method GetRate:String()
		Select rate
		Case -1.0
			Return "Weapon Specific"
		Case 1.0
			Return "Full Rate"
		Case 0.5
			Return "Half Rate"
		Case 0.25
			Return "Quarter Rate"
		Case 0.1
			Return "Harassing Fire"
		End Select
	End Method
	
	Method GetLevel:String()
		Select level
		Case 0
			Return "Guns Only"
		Case 1
			Return "Missiles Only"
		Case 2
			Return "All Weapons"
		End Select
	End Method
	
	Method GetDirection:String()
		Select autoDirection
		Case -1
			Return "No Auto"
		Case 0
			Return "Auto Bow"
		Case 1
			Return "Auto Port"
		Case 2
			Return "Auto Starboard"
		Case 3
			Return "Auto Stern"
		End Select
	End Method

End Type



