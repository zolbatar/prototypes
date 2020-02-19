Type TTarget
	Field target:TGameEntity, dist:Double, angle:Double, angleDiff:Double, score:Double
	
	Function Create(lst:TList, target:TGameEntity, dist:Double, angle:Double, angleDiff:Double)
		?debug
   			TProfiler.Enter("Target::Create")
  		?
		Local t:TTarget = New TTarget
		t.target = target
		t.dist = dist
		t.angle = angle
		t.angleDiff = angleDiff
		If target.owningPlayerNo = 0 Then
			If GameDifficulty = DifficultyHard Then
				t.score = 10000.0 / dist / Abs(angleDiff) * (target.targetedCount + 1)
			Else
				t.score = 10000.0 / dist / Abs(angleDiff)
			End If
		Else
			If GameDifficulty = DifficultyHard Then
				t.score = 10000.0 / dist / Abs(angleDiff)
			Else
				t.score = 10000.0 / dist / Abs(angleDiff) * (target.targetedCount + 1)
			End If
		End If
		ListAddFirst(lst, t)
		?debug
   			TProfiler.Leave("Target::Create")
  		?
	End Function
	
	Method Compare:Int(p:Object)
		?debug
   			TProfiler.Enter("Target::Compare")
  		?
		If score > TTarget(p).score Return 1
		?debug
   			TProfiler.Leave("Target::Compare")
  		?
	End Method
End Type

Type TAI
	Const ProfileStandGround:Int = 0, ProfileApproach:Int = 1, ProfilePatrol:Int = 2, ProfileEscort:Int = 3, PersonalityTypes:Int = 4
	Field ge:TGameEntity, timeLastUpdated:Long = 0, personality:Int = 0, ignoreStartingWaypoint:Int = 0, waypointIndex:Int = 0
	Field escortID:Int = -1, escort:TGameEntity, escortAngle:Double = -1
	Field facingN:Int = 0, facingE:Int = 0, facingS:Int = 0, facingW:Int = 0
	
	Function Create:TAI(ge:TGameEntity)
		?debug
   			TProfiler.Enter("AI::Create")
  		?
		Local ai:TAI = New TAI
		ai.ge = ge
		ai.WorkOutBestFacing()
		?debug
   			TProfiler.Leave("AI::Create")
  		?
		Return ai	
	End Function
	
	Method Update(gs:TGameState, ms:Long)
		?debug
   			TProfiler.Enter("AI::Update")
  		?
		Select personality
		Case ProfileStandGround
			FindTarget(gs, ms, 0, 0)
		Case ProfileApproach
			FindTarget(gs, ms, 0, 1)
		Case ProfileEscort
			' Do we have an angle?
			If escortAngle = -1 Then
				Select ge.ai.escort.escortCount
				Case 0
					escortAngle = -30
				Case 1
					escortAngle = 30
				Case 2
					escortAngle = -150
				Case 3
					escortAngle = 150
				Case 4
					escortAngle = -60
				Case 5
					escortAngle = 60
				Case 4
					escortAngle = -120
				Case 5
					escortAngle = 120
				Default
					escortAngle = 180
				End Select
			End If
			ge.ai.escort.escortCount :+ 1
			
			If ge.ai.escortID <> -1 Then
				ge.RemoveCurrentOrder(ms)
				ge.AddPursueOrder(ge.ai.escort, 2500.0, escortAngle, ms, 0, 1)
			End If
		Case ProfilePatrol
			If ge.orders.Count() = 0 And ge.waypoints.Count() > 0 Then
				Local xy:TXY
				If waypointIndex = ge.waypoints.Count() Then
					If ge.ai.ignoreStartingWaypoint = 0 Then
						ge.AddMoveOrder(ge.startX, ge.StartY, 1.0, ms)
						waypointIndex = 0
					Else
						xy = TXY(ge.waypoints.ValueAtIndex(0))
						ge.AddMoveOrder(xy.x, xy.y, 1.0, ms)
						waypointIndex = 1
					End If
				Else
					xy = TXY(ge.waypoints.ValueAtIndex(waypointIndex))
					ge.AddMoveOrder(xy.x, xy.y, 1.0, ms)
					waypointIndex :+ 1
				End If
			End If
			FindTarget(gs, ms, 1, 1)
		End Select
		?debug
   			TProfiler.Leave("AI::Update")
  		?
	End Method
	
	Method FindTarget:Int(gs:TGameState, ms:Long, first:Int, move:Int)
		?debug
   			TProfiler.Enter("AI::FindTarget")
  		?

		' Do we have a target?
		If ge.orders.Count() = 0 Then 
			timeLastUpdated = ms
			
			' Search for target
			Local targets:TList = CreateList()
			FindTargetAI(gs, targets)
			SortList(targets)
			
			' Best facing
			Local m:Int = -1
			Local f:Int = 0
			If facingN > m Then 
				m = facingN
				f = 0
			End If
			If facingE > m Then 
				m = facingE
				f = 1
			End If
			If facingW > m Then 
				m = facingW
				f = 2
			End If
			If facingS > m Then 
				m = facingS
				f = 3
			End If

			' Select
			If targets.Count() > 0 Then 
				Local t:TTarget
				If ge.vessel.fighter = 0 Then
					t = TTarget(targets.Last())
				Else
					Local c:Int = 5
					If c > targets.Count() Then c = targets.Count()
					c = Rand(0, c - 1)
					t = TTarget(targets.ValueAtIndex(c))
				End If
				ge.orders = CreateList()
				If move = 1 And ge.speed > 0 Then 
					If ge.vessel.fighter = 0 Then
						ge.AddPursueOrder(t.target, 1500, 0, ms, 0, 1)
					Else
						ge.AddPursueOrder(t.target, 1000, 0, ms, 0, 1)
					End If
				End If
				If ge.vessel.fighter = 0 Then ge.AddFireOrder(t.target, 2, f, t.target.owningPlayerNo, ms, -1.0, first)
				?debug
		   			TProfiler.Leave("AI::FindTarget")
		  		?
				Return 1
			End If
		End If
		Return 0
	End Method
	
	Function ReturnAIProfileName:String(p:Int)
		Select p
		Case ProfileStandGround
			Return "Stand Ground"
		Case ProfileApproach
			Return "Seek & Destroy"
		Case ProfilePatrol
			Return "On Patrol"
		Case ProfileEscort
			Return "Escort"
		End Select
	End Function
	
	Function ReturnAIProfileDescription:String(p:Int)
		Select p
		Case ProfileStandGround
			Return "Attack nearby enemy vessels, rotating as necessary for best arc of fire."
		Case ProfileApproach
			Return "Move towards and attack enemy vessels."
		Case ProfilePatrol
			Return "Follow patrol route, attacking any enemy vessels encountered."
		Case ProfileEscort
			Return "Escort vessel at 2500m range, providing fire support as necessary."
		End Select
	End Function

	Method WorkOutBestFacing()
		?debug
   			TProfiler.Enter("AI::WorkOutBestFacing")
  		?
		facingN = 0
		facingE = 0
		facingS = 0
		facingW = 0
		For Local x:TXY = EachIn ge.vessel.missiles
			Select ge.shape[x.x, x.y].rot
			Case 0
				facingN :+ 1
			Case 1
				facingE :+ 1
			Case 2
				facingS :+ 1
			Case 3
				facingW :+ 1
			End Select
		Next
		For Local x:TXY = EachIn ge.vessel.guns
			Select ge.shape[x.x, x.y].rot
			Case 0
				facingN :+ 1
			Case 1
				facingE :+ 1
			Case 2
				facingS :+ 1
			Case 3
				facingW :+ 1
			End Select
		Next
		?debug
   			TProfiler.Leave("AI::WorkOutBestFacing")
  		?
	End Method
	
	Method FindTargetAI(gs:TGameState, lstMain:TList)
		?debug
   			TProfiler.Enter("AI::FindTargetAI")
  		?
		Local closestDistanceEntity:TGameEntity
		Local closestDistance:Double = 30000.0
		Local closestAngleEntity:TGameEntity
		Local closestAngle:Double = 9999999999
		For Local get:TGameEntity = EachIn ge.TargetList(30000.0)
			Local actualAngle:Double = AdjustAngle(AngleBetweenPoints(ge.x, ge.y, get.x, get.y))
			Local dist:Double = DistanceBetweenPoints(ge.x, ge.y, get.x, get.y)
			Local d:Double = DifferenceBetweenAngles(ge.angle, actualAngle)

			' Can we see it?
			If ge.CanSeeTarget(get) = 1 Then
				TTarget.Create(lstMain, get, dist, actualAngle, d)
			End If 
		Next
		?debug
   			TProfiler.Leave("AI::FindTargetAI")
  		?
	End Method
	
End Type

