SuperStrict
Import "CatmullRomSplines.bmx"
Import "GameData.bmx"
Import "GameState.bmx"
Import "Helper.bmx"
Import "Profiler.bmx"
Import "ScriptItem.bmx"
Import "Vessel.bmx"
Import "WeaponClass.bmx"
Import "XY.bmx"
Include "AI.bmx"
Include "Order.bmx"

Type TGameEntity
	Const reachedTarget:Double = 10.0, SectionSizeX:Double = 95.0, SectionSizeY:Double = 95.0
	Const NumberFighters:Int = 20, FighterSpeedStart:Double = 100.0, FighterSpeedMax:Double = 400.0, FighterDPS:Double = 40.0
	Field name:String, owningPlayerNo:Int, index:Long, orders:TList, ordersHeld:Int = 0
	Field vessel:TVessel, x:Double, y:Double, tX:Double, tY:Double, angle:Double = AdjustAngle(-90), startX:Double, startY:Double
	Field distanceTravelled:Double = 0, distanceToDecelerate:Double = 0, slowSpeed:Double 
	Field dps:Double, mass:Int, propulsion:Int, speed:Double, currentSpeed:Double, targetSpeed:Double
	Field targetPainted:Int = 1, visible:Int = 0, targetable:Int = 1, lastExplosion:Long
	Field armour:Double, armourRemaining:Double, shield:Double, shieldRemaining:Double, shieldRegenerate:Double = 1.0, repairRate:Double = 1.0 
	Field pwrIn:Int, pwrOut:Int, radar:Double = 0.0, ecm:Int
	Field lastAttack:Long, w:TWeaponClass = Null, died:Long = 0, removeWhen:Long = 0, initialLoadout:Int[], loadout:Int[], collisionSize:Double, alreadyTargeted:Int = 0
	Field targetedCount:Int = 0, escortCount:Int = 0, targets:TMap, timeSinceLastCheck:Long = 0, launching:TList = CreateList()
	Field condition:Double[,], onOff:Int[,], autoFire:Double[,], shape:TBlock[,], computerControlled:Int = 0
	Field fighterL:TBlock = New TBlock, returningToCarrier:Int = 0, carrier:TGameEntity, lastOrderCheck:Long
	Field preferredAmmo1:Int[,], preferredAmmo2:Int[,], preferredAmmo3:Int[,], strafe:Int[,], script:TList
	Field haloActive:Long = 0, lastEMP:Long = 0, electricActive:Long = 0, jumping:Long = 0, born:Long, lastJump:Long = 0
	Field autoN:Int = 0, autoS:Int = 0, autoE:Int = 0, autoW:Int = 0
	Field missilesCount:Int = 0, gunsCount:Int = 0, outOfAmmoMessage:Int = 0
	Field trail:TList = CreateList(), lastTrailPoint:TPoint
	Field firstX:Int = -1, firstY:Int = -1, lastX:Int = -1, lastY:Int = -1, width:Int, height:Int, centreX:Double, centreY:Double
	Field ai:TAI, waypoints:TList = CreateList(), timeLastAI:Long = 0
	Field targetsWithinRangeCollision:TList, targetsWithinRange250:TList, targetsWithinRange500:TList
	Field targetsWithinRange2500:TList, targetsWithinRange5000:TList
	Field targetsWithinRange10000:TList, targetsWithinRange15000:TList, targetsWithinRange30000:TList

	' Target
	Field targetAngle:Double = AdjustAngle(-90), initialTargetDistance:Double = 0, targetDistance:Double = 0, targetX:Double, targetY:Double
	
	Function CalcPoints(gd:TGameData, g:TGameState)
		?debug
   			TProfiler.Enter("GameEntity::CalcPoints")
  		?
		g.p1points = 0
		g.p2points = 0
		g.p1pointsReserve = 0
		g.p2pointsReserve = 0
		For Local player:Int = 0 To 1
			For Local ge:TGameEntity = EachIn g.entities[player]
				Local c:Int = ge.vessel.CalcCostTotal(gd.pieces, gd.weapons, ge.loadout)
				If ge.owningPlayerNo = 0 Then g.p1points :+ c
				If ge.owningPlayerNo = 1 Then g.p2points :+ c
			Next
		Next
		For Local ge:TGameEntity = EachIn g.entitiesReserve
			Local c:Int = ge.vessel.CalcCostTotal(gd.pieces, gd.weapons, ge.loadout)
			If ge.owningPlayerNo = 0 Then g.p1pointsReserve :+ c
			If ge.owningPlayerNo = 1 Then g.p2pointsReserve :+ c
		Next
		?debug
   			TProfiler.Leave("GameEntity::CalcPoints")
  		?
	End Function
	
	Function Create:TGameEntity(g:TGameState, _index:Int, pieces:TPiece[], _no:Int, _vessel:TVessel, _x:Double, _y:Double, weapons:TWeaponClass[], ms:Long)
		?debug
   			TProfiler.Enter("GameEntity::Create")
  		?
		Local ge:TGameEntity = New TGameEntity
		ge.born = ms
		ge.index = _index
		ge.owningPlayerNo = _no
		ge.vessel = _vessel
		ge.name = ge.vessel.name
		ge.x = _x
		ge.y = _y
		ge.StartTrail()
		ge.orders = CreateList()
		ge.targets = CreateMap()
		ge.script = CreateList()
		
		' Arrays
		ge.condition = ge.vessel.BuildConditionArray()
		ge.onOff = ge.vessel.BuildOnOffArray()
		ge.autoFire = ge.vessel.BuildAutofireArray()
		ge.shape = New TBlock[TVessel.maxShapeX, TVessel.maxShapeY]
		ge.preferredAmmo1 = New Int[TVessel.maxShapeX, TVessel.maxShapeY]
		ge.preferredAmmo2 = New Int[TVessel.maxShapeX, TVessel.maxShapeY]
		ge.preferredAmmo3 = New Int[TVessel.maxShapeX, TVessel.maxShapeY]
		ge.strafe = New Int[TVessel.maxShapeX, TVessel.maxShapeY]
		ge.loadout = New Int[TWeaponClass.NumberOfClasses]
		ge.initialLoadout = New Int[TWeaponClass.NumberOfClasses]
		
		' Loadout
		For Local i:Int = 0 To TWeaponClass.NumberOfClasses - 1
			ge.loadout[i] = ge.vessel.loadout[i]
			ge.initialLoadout[i] = ge.vessel.loadout[i]
		Next

		' Stats
		ge.mass = ge.vessel.CalcMass(pieces)
		ge.propulsion = ge.vessel.CalcPropulsion(pieces, ge.onOff)
		ge.speed = ge.vessel.CalcSpeed(ge.propulsion, ge.mass)
		ge.currentSpeed = 0
		ge.dps = ge.vessel.CalcDPS(ge.propulsion, ge.mass)
		ge.pwrIn = ge.vessel.CalcPowerOutput(pieces, ge.condition, ge.onOff)
		ge.pwrOut = ge.vessel.CalcPower(pieces, ge.onOff)
		ge.armour = ge.vessel.CalcArmour(ge.mass)
		ge.shieldRegenerate = ge.vessel.CalcRegeneration(pieces, ge.condition, ge.onOff)
		ge.repairRate = ge.vessel.CalcRepairRate(pieces, ge.condition, ge.onOff)
		ge.armourRemaining = ge.armour
		ge.shield = ge.vessel.CalcShield(pieces, ge.condition, ge.onOff)
		ge.shieldRemaining = ge.shield
		ge.radar = ge.vessel.CalcRadarRange(pieces, ge.condition, ge.onOff)
		ge.ecm = ge.vessel.CalcECM(pieces, ge.condition, ge.onOff)
		ge.lastAttack = ms
		ge.collisionSize = ge.vessel.RealDimension(ge.firstX, ge.firstY, ge.lastX, ge.lastY, ge.width, ge.height) * SectionSizeX
		ge.centreX = ((ge.lastX - ge.firstX) / 2.0) + ge.firstX
		ge.centreY = ((ge.lastY - ge.firstY) / 2.0) + ge.firstY
		
		' Copy stuff
		For Local y:Int = 0 To TVessel.MaxShapeY - 1 
			For Local x:Int = 0 To TVessel.MaxShapeX - 1 
				Local ob:TBlock = ge.vessel.shapeV[x, y]
				Local b:TBlock = New TBlock
				b.piece = ob.piece
				b.variant = ob.variant
				b.rot = ob.rot
				ge.shape[x, y] = b
				ge.onOff[x, y] = 1
				ge.autoFire[x, y] = _vessel.shapeV[x, y].autofire	
				ge.condition[x, y] = 1.0
				ge.preferredAmmo1[x, y] = _vessel.shapeV[x, y].preferredAmmo1V
				ge.preferredAmmo2[x, y] = _vessel.shapeV[x, y].preferredAmmo2V
				ge.preferredAmmo3[x, y] = _vessel.shapeV[x, y].preferredAmmo3V
				ge.strafe[x, y] = _vessel.shapeV[x, y].strafe
			Next
		Next 

		' Load weapons
		For Local x:TXY = EachIn ge.vessel.missiles
			ge.LoadAmmo(x.x, x.y, weapons, ms, g, 1)
			ge.missilesCount :+ 1
		Next
		For Local x:TXY = EachIn ge.vessel.guns
			ge.LoadAmmo(x.x, x.y, weapons, ms, g, 1)
			ge.gunsCount :+ 1
		Next

		' Fill launchers
		For Local x:TXY = EachIn ge.vessel.launchers
			ge.shape[x.x, x.y].numberRemaining = NumberFighters
		Next

		ge.CalculateAutoFireArcs()		
		ge.ai = TAI.Create(ge)
		?debug
   			TProfiler.Leave("GameEntity::Create")
  		?
		Return ge
	End Function
	
	Function CreateFighter:TGameEntity(_index:Int, _owner:Int, _vessel:TVessel, _x:Double, _y:Double, angle:Double, weapons:TWeaponClass[], ms:Long)
		?debug
   			TProfiler.Enter("GameEntity::CreateFighter")
  		?
		Local ge:TGameEntity = New TGameEntity
		ge.born = ms
		ge.index = _index
		ge.owningPlayerNo = _owner
		ge.vessel = _vessel
		ge.name = ge.vessel.name
		ge.x = _x
		ge.y = _y
		ge.fighterL.weapon = weapons[TWeaponClass.fighterID]
		ge.fighterL.numberRemaining = ge.fighterL.weapon.number
		ge.w = ge.fighterL.weapon
		ge.fighterL.fired = ms - ge.fighterL.weapon.coolDown
		ge.StartTrail()
		ge.orders = CreateList()
		ge.targets = CreateMap()
		ge.script = CreateList()
		ge.angle = angle
		ge.targetAngle = angle
		ge.speed = FighterSpeedMax
		ge.targetSpeed = FighterSpeedMax
		ge.currentSpeed = FighterSpeedStart
		ge.dps = FighterDPS
		ge.collisionSize = 25.0
		ge.distanceTravelled = 0
		ge.shieldRegenerate = 0.01
		ge.shield = 10
		ge.shieldRemaining = 10
		ge.armour = 10
		ge.armourRemaining = 10
		ge.radar = TVessel.DefaultRadarRange
		ge.autoN = 1
		ge.computerControlled = 1
		ge.ai = TAI.Create(ge)
		ge.ai.personality = TAI.ProfileApproach
		Return ge
		?debug
   			TProfiler.Leave("GameEntity::CreateFighter")
  		?
	End Function

	Function CreateExplosion:TGameEntity(_index:Int, pieces:TPiece[], _owner:Int, _vessel:TVessel, _x:Double, _y:Double, weapons:TWeaponClass[], ms:Long)
		?debug
   			TProfiler.Enter("GameEntity::CreateExplosion")
  		?
		Local ge:TGameEntity = New TGameEntity
		ge.born = ms
		ge.index = _index
		ge.owningPlayerNo = _owner
		ge.x = _x
		ge.y = _y
		ge.w = weapons[TWeaponClass.explosionID]
		ge.removeWhen = ms + 2500
		ge.died = ms
		?debug
   			TProfiler.Leave("GameEntity::CreateExplosion")
  		?
		Return ge
	End Function
	
	Function CreateExplosionSmall:TGameEntity(_index:Int, pieces:TPiece[], _owner:Int, _vessel:TVessel, _x:Double, _y:Double, weapons:TWeaponClass[], ms:Long)
		?debug
   			TProfiler.Enter("GameEntity::CreateExplosionSmall")
  		?
		Local ge:TGameEntity = New TGameEntity
		ge.born = ms
		ge.index = _index
		ge.owningPlayerNo = _owner
		ge.x = _x
		ge.y = _y
		ge.w = weapons[TWeaponClass.explosionSmallID]
		ge.removeWhen = ms + 2500
		ge.died = ms
		?debug
   			TProfiler.Leave("GameEntity::CreateExplosionSmall")
  		?
		Return ge
	End Function

	Function CreateMissile:TGameEntity(_index:Int, pieces:TPiece[], _owner:Int, _vessel:TVessel, _x:Double, _y:Double, angle:Double, target:TGameEntity, w:TWeaponClass, ms:Long)
		?debug
   			TProfiler.Enter("GameEntity::CreateMissile")
  		?
		Local ge:TGameEntity = New TGameEntity
		ge.born = ms
		ge.index = _index
		ge.owningPlayerNo = _owner
		ge.vessel = _vessel
		ge.targetable = w.targetable
		ge.x = _x
		ge.y = _y
		ge.StartTrail()
		ge.orders = CreateList()
		ge.targets = CreateMap()
		ge.angle = angle
		ge.w = w
		ge.speed = w.targetSpeed
		ge.targetSpeed = w.targetSpeed
		ge.currentSpeed = w.currentSpeed
		ge.dps = w.dps
		ge.collisionSize = 100.0
		Local o:TOrder = TOrder.CreatePursueOrder(target, 0.0)
		o.percent = 1.0
		ListAddFirst(ge.orders, o)
		?debug
   			TProfiler.Leave("GameEntity::CreateMissile")
  		?
		Return ge
	End Function
	
	Function CreateBullet:TGameEntity(_index:Int, pieces:TPiece[], _owner:Int, _vessel:TVessel, _x:Double, _y:Double, angle:Double, w:TWeaponClass, ms:Long)
		?debug
   			TProfiler.Enter("GameEntity::CreateBullet")
  		?
		Local ge:TGameEntity = New TGameEntity
		ge.born = ms
		ge.index = _index
		ge.owningPlayerNo = _owner
		ge.vessel = _vessel
		ge.x = _x
		ge.y = _y
		ge.StartTrail()
		ge.targetable = w.targetable
		ge.orders = CreateList()
		ge.angle = angle
		ge.targetAngle = angle
		ge.w = w
		ge.speed = w.targetSpeed
		ge.targetSpeed = w.targetSpeed
		ge.currentSpeed = w.currentSpeed
		ge.dps = w.dps
		ge.collisionSize = 100.0
		ge.distanceTravelled = 0
		?debug
   			TProfiler.Leave("GameEntity::CreateBullet")
  		?
		Return ge
	End Function
	
	Method StartTrail()
		If vessel.ship = 1 And vessel.fighter = 0 Then Return
		?debug
   			TProfiler.Enter("GameEntity::StartTrail")
  		?
		trail = CreateList()
		lastTrailPoint = TPoint.Create(x, y)
		ListAddFirst(trail, lastTrailPoint)
		?debug
   			TProfiler.Leave("GameEntity::StartTrail")
  		?
	End Method

	Method CheckTrail()
		If vessel.ship = 1 And vessel.fighter = 0 Then Return
		?debug
   			TProfiler.Enter("GameEntity::CheckTrail")
  		?
		lastTrailPoint = TPoint.Create(x, y)
		ListAddFirst(trail, lastTrailPoint)
		?debug
   			TProfiler.Leave("GameEntity::CheckTrail")
  		?
	End Method
	
	Method AmmoRemaining:Int(x:Int, y:Int)
		?debug
   			TProfiler.Enter("GameEntity::AmmoRemaining")
  		?
		Local p1:Int = preferredAmmo1[x, y]
		Local p2:Int = preferredAmmo2[x, y]
		Local p3:Int = preferredAmmo3[x, y]
		Local ammo:Int = 0
		If p1 <> -1 Then ammo :+ loadout[p1]
		If p2 <> -1 Then ammo :+ loadout[p2]
		If p3 <> -1 Then ammo :+ loadout[p3]
		?debug
   			TProfiler.Leave("GameEntity::AmmoRemaining")
  		?
		Return ammo
	End Method

	Method LoadAmmo(x:Int, y:Int, weapons:TWeaponClass[], ms:Long, gs:TGameState, initial:Int)
		?debug
   			TProfiler.Enter("GameEntity::LoadAmmo")
  		?
		' Go through each ammo type in turn and load
		If preferredAmmo1[x, y] > - 1 Then
			If loadout[preferredAmmo1[x, y]] > 0 Then
				If initial Then shape[x, y].fired = -weapons[preferredAmmo1[x, y]].coolDown Else shape[x, y].fired = ms + weapons[preferredAmmo1[x, y]].coolDown * 3
				shape[x, y].numberRemaining = weapons[preferredAmmo1[x, y]].number
				shape[x, y].weapon = weapons[preferredAmmo1[x, y]]
				shape[x, y].reloadNeeded = 0
				loadout[preferredAmmo1[x, y]] :- 1
				?debug
   					TProfiler.Leave("GameEntity::LoadAmmo")
  				?
				Return
			End If
		End If
		If preferredAmmo2[x, y] > - 1 Then
			If loadout[preferredAmmo2[x, y]] > 0 Then
				If initial Then shape[x, y].fired = -weapons[preferredAmmo1[x, y]].coolDown Else shape[x, y].fired = ms + weapons[preferredAmmo2[x, y]].coolDown * 3
				shape[x, y].numberRemaining = weapons[preferredAmmo2[x, y]].number
				shape[x, y].weapon = weapons[preferredAmmo2[x, y]]
				shape[x, y].reloadNeeded = 0
				loadout[preferredAmmo2[x, y]] :- 1
				?debug
   					TProfiler.Leave("GameEntity::LoadAmmo")
  				?
				Return
			End If
		End If
		If preferredAmmo3[x, y] > - 1 Then
			If loadout[preferredAmmo3[x, y]] > 0 Then
				If initial Then shape[x, y].fired = -weapons[preferredAmmo1[x, y]].coolDown Else shape[x, y].fired = ms + weapons[preferredAmmo3[x, y]].coolDown * 3
				shape[x, y].numberRemaining = weapons[preferredAmmo3[x, y]].number
				shape[x, y].weapon = weapons[preferredAmmo3[x, y]]
				shape[x, y].reloadNeeded = 0
				loadout[preferredAmmo3[x, y]] :- 1
				?debug
   					TProfiler.Leave("GameEntity::LoadAmmo")
  				?
				Return
			End If
		End If
'		shape[x, y].weapon = Null
		If outOfAmmoMessage = 0 Then
			gs.AddMessage("<" + name + "> is out of ammo.", ms, owningPlayerNo)
			outOfAmmoMessage = 1
		End If
		?debug
   			TProfiler.Leave("GameEntity::LoadAmmo")
  		?
	End Method
	
	Method HoldOrders()
		ordersHeld = 1
		targetAngle = angle
		targetSpeed = 0
	End Method
	
	Method UnholdOrders(ms:Long)
		ordersHeld = 0
		If orders.Count() > 0 Then
			Local o:TOrder = TOrder(orders.First())
			ProcessOrder(o, ms)
		End If
	End Method

	Method CheckEscortOrder(g:TGameState, o:TOrder)
		If o.t = OrderPursue And o.target.died = 0 Then
			o.target.escortCount :- 1
			If o.target.escortCount < 0 Then o.target.escortCount = 0
		End If
	End Method

	Method CancelOrder(i:Int, g:TGameState, ms:Long)
		?debug
   			TProfiler.Enter("GameEntity::CancelOrder")
  		?
		If i = 0 Then
			Local v:TOrder = TOrder(orders.RemoveFirst())
			CheckEscortOrder(g, v)
			targetSpeed = 0
			targetAngle = angle
			If orders.Count() > 0 Then
				Local o:TOrder = TOrder(orders.First()) 
				ProcessOrder(o, ms)
			End If
		Else
			If i < orders.Count() Then
				Local v:TOrder = TOrder(orders.ValueAtIndex(i))
				orders.Remove(v)
				CheckEscortOrder(g, v)
			End If
		End If 
		?debug
   			TProfiler.Leave("GameEntity::CancelOrder")
  		?
	End Method
	
	Method ApplyDamage:Int(gd:TGameData, g:TGameState, ms:Long)
		?debug
   			TProfiler.Enter("GameEntity::ApplyDamage")
  		?
		If vessel.fighter = 1 Then Return 0
	
		' Any modules/weapons below 25% are shutdown
		For Local y:Int = 0 To TVessel.MaxShapeY - 1
			For Local x:Int = 0 To TVessel.MaxShapeX - 1
				If condition[x, y] < 0.25 And onOff[x, y] > 0.0 Then 
					If owningPlayerNo = 0 Or g.optionShowAllMessages = 1 Then g.AddMessage("<" + name + "> had a module disabled for repair.", ms, owningPlayerNo)
					onOff[x, y] = 0.0
				End If
			Next
		Next

		propulsion = vessel.CalcPropulsion(gd.pieces, onOff)
		speed = vessel.CalcSpeed(propulsion, mass)
		If targetSpeed > speed Then targetSpeed = speed
		shieldRegenerate = vessel.CalcRegeneration(gd.pieces, condition, onOff)
		shield = vessel.CalcShield(gd.pieces, condition, onOff)
		repairRate = vessel.CalcRepairRate(gd.pieces, condition, onOff)
		If shieldRemaining > shield Then shieldRemaining = shield 
		radar = vessel.CalcRadarRange(gd.pieces, condition, onOff)
		pwrIn = vessel.CalcPowerOutput(gd.pieces, condition, onOff)
		pwrOut = vessel.CalcPower(gd.pieces, onOff)
		ecm = vessel.CalcECM(gd.pieces, condition, onOff)
		
		' Do we have guns?
		If speed = 0 Then
			For Local x:TXY = EachIn vessel.missiles
				If condition[x.x, x.y] > 0.0 Then 
					?debug
	   					TProfiler.Leave("GameEntity::ApplyDamage")
			  		?
					Return 0
				End If
			Next
			For Local x:TXY = EachIn vessel.guns
				If condition[x.x, x.y] > 0.0 Then 
					?debug
	   					TProfiler.Leave("GameEntity::ApplyDamage")
			  		?
					Return 0
				End If
			Next
			Return 1
		End If
		Return 0
		?debug
   			TProfiler.Leave("GameEntity::ApplyDamage")
  		?
	End Method
	
	Method AddMoveOrder(x:Double, y:Double, percent:Double, ms:Long)
		Local o:TOrder = TOrder.CreateMoveOrder(x, y, percent)
		ListAddLast(orders, o)
		If orders.Count() = 1 Then ProcessOrder(o, ms)
	End Method
	
	Method AddHeadingOrder(x:Double, y:Double, ms:Long)
		Local o:TOrder = TOrder.CreateHeadingOrder(x, y)
		ListAddLast(orders, o)
		If orders.Count() = 1 Then ProcessOrder(o, ms)
	End Method

	Method AddFireOrder(ge:TGameEntity, level:Int, autoDirection:Int, targetPlayer:Int, ms:Long, rate:Double, first:Int = 0)
		Local o:TOrder = TOrder.CreateFireOrder(ge, level, autoDirection, targetPlayer, rate)
		If first Then ListAddFirst(orders, o) Else ListAddLast(orders, o)
		If orders.Count() = 1 Then ProcessOrder(o, ms)
	End Method

	Method AddFireOrderXY(x:Double, y:Double, level:Int, autoDirection:Int, targetPlayer:Int, ms:Long, rate:Double, first:Int = 0)
		Local o:TOrder = TOrder.CreateFireOrderXY(x, y, level, autoDirection, targetPlayer, rate)
		If first Then ListAddFirst(orders, o) Else ListAddLast(orders, o)
		If orders.Count() = 1 Then ProcessOrder(o, ms)
	End Method

	Method AddPursueOrder:TOrder(ge:TGameEntity, distance:Double, angle:Double, ms:Long, nextOrder:Int, removeWhenArrived:Int)
		Local o:TOrder = TOrder.CreatePursueOrder(ge, distance)
		o.nextOrder = nextOrder
		o.heading = angle
		o.removeWhenArrived = removeWhenArrived
		ListAddLast(orders, o)
		If orders.Count() = 1 Then ProcessOrder(o, ms)
	End Method

	Method AddAccelerateOrder(percent:Double, ms:Long)
		Local o:TOrder = TOrder.CreateAccelerateOrder(percent)
		ListAddLast(orders, o)
		If orders.Count() = 1 Then ProcessOrder(o, ms)
	End Method
	
	Method ProcessOrder(o:TOrder, ms:Long)
		?debug
   			TProfiler.Enter("GameEntity::ProcessOrder")
  		?
		o.start = ms
		Select o.t
		Case OrderHeading
			targetSpeed = 0.0
		Case OrderMove
			targetAngle = AdjustAngle(AngleBetweenPoints(x, y, o.x, o.y))
			If targetAngle > angle And Abs(angle - targetAngle) > 180 Then targetAngle :- 360
			If targetAngle < angle And Abs(angle - targetAngle) > 180 Then targetAngle :+ 360
			targetDistance = DistanceBetweenPoints(x, y, o.x, o.y)
			initialTargetDistance = targetDistance
			If targetDistance / speed < o.percent Then 
				o.percent = targetDistance / speed
			End If
			slowSpeed = o.percent / 10.0
			targetSpeed = 0.0 
			distanceTravelled = 0
			distanceToDecelerate = 0
			targetX = o.x
			targetY = o.y
		Case OrderAccelerate
			targetSpeed = speed * o.percent
			slowSpeed = o.percent / 10.0
			distanceTravelled = 0
		End Select
		?debug
   			TProfiler.Leave("GameEntity::ProcessOrder")
  		?
	End Method

	'0.0376990438
	Method UpdateOrder(o:TOrder, gs:TGameState, ms:Long, gd:TGameData)
		?debug
   			TProfiler.Enter("GameEntity::UpdateOrder")
  		?
		Local removeOrder:Int = 0
		
		Select o.t
		Case OrderPursue
			PerformPursueTarget(o, gs, ms)
		Case OrderFire
			PerformFireOnTarget(o, gs, ms, gd)
		Case OrderHeading
			targetAngle = AdjustAngle(AngleBetweenPoints(x, y, o.x, o.y))
			If targetAngle > angle And Abs(angle - targetAngle) > 180 Then targetAngle :- 360
			If targetAngle < angle And Abs(angle - targetAngle) > 180 Then targetAngle :+ 360
			If Same(angle, targetAngle) = 1 Then
				removeOrder = 1
			End If
			o.heading = targetAngle
		Case OrderMove
			targetAngle = AdjustAngle(AngleBetweenPoints(x, y, o.x, o.y))
			If targetAngle > angle And Abs(angle - targetAngle) > 180 Then targetAngle :- 360
			If targetAngle < angle And Abs(angle - targetAngle) > 180 Then targetAngle :+ 360
			targetDistance = DistanceBetweenPoints(x, y, o.x, o.y)

			If targetDistance < reachedTarget Then
				'Print "Remove Order"
				'Print "Time for order: " + String(ms - o.start)
				targetSpeed = 0
				removeOrder = 1
			ElseIf distanceTravelled > initialTargetDistance Then
				'Print "Got there"
				targetSpeed = 0
				removeOrder = 1
			ElseIf targetDistance < distanceToDecelerate Then 
				' Decelerate
				'Print "Slowing"
				targetSpeed = speed * slowSpeed
			ElseIf currentSpeed < targetSpeed Then
				' Accelerating but ran out of room to go faster, decelerate
				'Print ":" + distanceTravelled
				If targetDistance < distanceTravelled Then
					'Print "Slowing, ran out of room"
					targetSpeed = speed * slowSpeed
				End If
			End If
		End Select
		'Print "X:" + String(x) + ",Y:" + String(y)
		'Print "Angle: " + String(Angle) + "/target: " + String(targetAngle) + ",targetDist: " + String(targetDistance) + ",speed: " + String(currentSpeed) + "/target: " + String(targetSpeed)
		
		If removeOrder = 1 Then RemoveCurrentOrder(ms)
		?debug
   			TProfiler.Leave("GameEntity::UpdateOrder")
  		?
	End Method
	
	Method RemoveCurrentOrder(ms:Long)
		?debug
   			TProfiler.Enter("GameEntity::RemoveCurrentOrder")
  		?
		orders.RemoveFirst()
		targetAngle = angle
		If vessel.ship = 1 And vessel.fighter = 0 Then targetSpeed = 0
		If vessel.ship = 1 And vessel.fighter = 1 Then targetSpeed = speed
		If orders.Count() > 0 Then
			Local o:TOrder = TOrder(orders.First())
			ProcessOrder(o, ms)
		End If
		?debug
   			TProfiler.Leave("GameEntity::RemoveCurrentOrder")
  		?
	End Method
	
	Method SetTargetAngle(_angle:Double)
		targetAngle = _angle
	End Method
	
	'0.0128492173
	Method PerformPursueTarget(o:TOrder, gs:TGameState, ms:Long)
		?debug
   			TProfiler.Enter("GameEntity::PerformPursueTarget")
  		?
		
		' Dead?
		Local found:Int = 0
		If o.target.died = 0 Then found = 1

		' Reprocess?
		Local actualAngle:Double 
		Local close:Int = 0, tooClose:Int = 0
		Local change:Int = 0
		If (vessel.ship = 1 Or vessel.missile = 1) And found = 1 And ms > (o.lastUpdate + 250) Then
			o.lastUpdate = ms
			change = 1
			
			If vessel.ship = 0 And w.defensive = 1 Then
				Local dX:Double = o.target.x - x
				Local dY:Double = y - o.target.y
				Local sta:Double = ATan2(dY, dX)
				Local a:Double = ASin(Sin(-(o.target.targetAngle + Pi - sta)) * (o.target.currentSpeed / currentSpeed)) + sta
				actualAngle = AdjustAngle(AngleBetweenPoints(x, y, o.target.x, o.target.y))

				' ECM
				If ms > (timeSinceLastCheck + 2500) And o.target.ecm > 0 Then
					timeSinceLastCheck = ms
					If Rand(0, o.target.ecm) > 55 Then 
						found = 0
						MapInsert(targets, o.target, Null)
						If owningPlayerNo = 0 Or gs.optionShowAllMessages = 1 Then
							gs.AddMessage("<" + w.name + "> lost target to <" + o.target.name + "> due to ECM.", ms, owningPlayerNo)
						End If
					End If
				End If
			Else 
				If w <> Null Then
					If w.radarSeeking = 1 And o.target.radar = TVessel.DefaultRadarRange Then 
						' Lost radar, need new target
					found = 0	
					End If
				End If
				If found = 1 Then
					Local dist:Double = DistanceBetweenPoints(x, y, o.target.x, o.target.y)
					If o.removeWhenArrived = 1 And dist < o.distance Then
						found = 0
					End If
				
					' Work out position to move to
					If found = 1 Then
						Local cX:Double, cY:Double
						If o.heading <> 0 Then
							Local dist2:Double = DistanceBetweenPoints(x, y, o.x, o.y)
							AddPolarToCartesian(o.distance * 0.9, o.target.angle + o.heading, cX, cY)
							o.x = o.target.x +  cX
							o.y = o.target.y +  cY
							actualAngle = AdjustAngle(AngleBetweenPoints(x, y, o.x, o.y))
							If dist2 < (o.distance * 0.25) Then close = 1
							If dist2 < (o.distance * 0.05) Then tooClose = 1
						Else
							' Work out intersection angle
							actualAngle = AdjustAngle(AngleBetweenPoints(x, y, o.target.x, o.target.y))
							If dist < (o.distance * 2.0) Then close = 1
							If dist < (o.distance) Then tooClose = 1
						End If
					End If
				End If
			End If
			targetAngle = actualAngle
			If targetAngle > angle And Abs(angle - targetAngle) > 180 Then targetAngle :- 360
			If targetAngle < angle And Abs(angle - targetAngle) > 180 Then targetAngle :+ 360
		End If
		
		If found = 0 Then 
			RemoveCurrentOrder(ms)

			' Find another target if missile
			If gs.missilesFindNewTarget = 1 Then
				If vessel.ship = 0 And w.defensive = 1 Then
					Local t:TGameEntity = FindTargetNoTube(gs, w)
					If t <> Null Then
						Local o:TOrder = TOrder.CreatePursueOrder(t, 0.0)
						o.percent = 1.0
						ListAddFirst(orders, o)
					End If
				ElseIf vessel.ship = 0 Then
					Local t:TGameEntity = FindTargetVesselNoTube(gs, w)
					If t <> Null Then
						Local o:TOrder = TOrder.CreatePursueOrder(t, 0.0)
						o.percent = 1.0
						ListAddFirst(orders, o)
					End If
				End If
				Return
			Else
				ListRemove(gs.entitiesProjectiles[owningPlayerNo], Self)
			End If
		ElseIf change = 1 Then
			' If close and a ship then speed match
			If vessel.ship = 1 Then
				If tooClose = 1 Then
					If vessel.fighter = 1 Then targetSpeed = speed / 4 Else targetSpeed = 0
			 	ElseIf close = 1 Then					
					If vessel.fighter = 1 Then targetSpeed = speed / 2 Else targetSpeed = o.target.targetSpeed
				Else
					targetSpeed = speed
				End If 
			End If
		End If 
		?debug
   			TProfiler.Leave("GameEntity::PerformPursueTarget")
  		?
	End Method
	
	Method PerformFireOnTarget(o:TOrder, gs:TGameState, ms:Long, gd:TGameData)
		?debug
   			TProfiler.Enter("GameEntity::PerformFireOnTarget")
  		?
		Local found:Int = 0
		Local actualAngle:Double 
		Local dist:Double
		If o.target = Null Then
			actualAngle = AdjustAngle(AngleBetweenPoints(x, y, o.x, o.y))
			dist = DistanceBetweenPoints(x, y, o.x, o.y)			

			' Do we have orders to auto-align?
			Select o.autoDirection
			Case -1
				targetAngle = angle
			Case 0
				targetAngle = AdjustAngle(actualAngle)
			Case 1
				targetAngle = AdjustAngle(actualAngle - 90)
			Case 2
				targetAngle = AdjustAngle(actualAngle + 90)
			Case 3
				targetAngle = AdjustAngle(actualAngle + 180)
			End Select
			If targetAngle > angle And Abs(angle - targetAngle) > 180 Then targetAngle :- 360
			If targetAngle < angle And Abs(angle - targetAngle) > 180 Then targetAngle :+ 360
		Else
			If o.target.died = 0 Then
				found = 1
				actualAngle = AdjustAngle(AngleBetweenPoints(x, y, o.target.x, o.target.y))
				dist = DistanceBetweenPoints(x, y, o.target.x, o.target.y)			

				' Can we still see it?
				If CanSeeTarget(o.target) = 0 Then 
					found = 0
					If owningPlayerNo = 0 Or gs.optionShowAllMessages = 1
						gs.AddMessage("<" + o.target.name + "> is not visible to <" + name + ">. Fire order cancelled.", ms, owningPlayerNo)
					End If
				End If			

				If found = 1 Then
					' Do we have orders to auto-align?
					Select o.autoDirection
					Case -1
						targetAngle = angle
					Case 0
						targetAngle = AdjustAngle(actualAngle)
					Case 1
						targetAngle = AdjustAngle(actualAngle - 90)
					Case 2
						targetAngle = AdjustAngle(actualAngle + 90)
					Case 3
						targetAngle = AdjustAngle(actualAngle + 180)
					End Select
					If targetAngle > angle And Abs(angle - targetAngle) > 180 Then targetAngle :- 360
					If targetAngle < angle And Abs(angle - targetAngle) > 180 Then targetAngle :+ 360
				End If
			End If
			
			If found = 0 Then 
				RemoveCurrentOrder(ms)
				Return
			End If 
		End If
		
		' Missiles
		If o.level = 1 Or o.level = 2 Then
			' Find a launch tube ready to fire and pointing the right way (all have a 90 degree arc)
			For Local x:TXY = EachIn vessel.missiles
				Local lt:TBlock = shape[x.x, x.y]
				If lt.weapon <> Null Then
					Local tubeAngle:Double = lt.TubeAngle(angle)
					Local d:Double = DifferenceBetweenAngles(tubeAngle, actualAngle)
					If VisibleCheck(d, TWeaponClass.MissileAngle, lt.weapon) Then
						Local rate:Double
						If o.rate > 0.0 Then rate = o.rate Else rate = autoFire[x.x, x.y]
						Local timeToTest:Long = lt.fired + (Double(lt.weapon.coolDown) / rate)
						If lt.weapon.defensive = 0 And ms > timeToTest And onOff[x.x, x.y] > 0.0 And dist < lt.weapon.maxRange Then
							If o.target = Null Then
								' Can't fire missiles into random space
							Else
								AttemptFireWeaponTargetMissile(gd, gs, lt, x.x, x.y, owningPlayerNo, ms, o.target)
							End If
						End If
					End If
				End If
			Next
		End If

		' Guns
		If o.level = 0 Or o.level = 2 Then
			For Local x:TXY = EachIn vessel.guns
				Local lt:TBlock = shape[x.x, x.y]
				If lt.weapon <> Null Then
					Local tubeAngle:Double = lt.TubeAngle(angle)
					Local d:Double = DifferenceBetweenAngles(tubeAngle, actualAngle)
					If VisibleCheck(d, TWeaponClass.RailgunAngle, lt.weapon) Then
						Local rate:Double
						If o.rate > 0.0 Then rate = o.rate Else rate = autoFire[x.x, x.y]
						Local timeToTest:Long = lt.fired + (Double(lt.weapon.coolDown) / rate)
						If lt.weapon.defensive = 0 And ms > timeToTest And onOff[x.x, x.y] > 0.0 And dist < lt.weapon.maxRange Then
							If o.target = Null Then
								AttemptFireWeaponTargetProjectileXY(gd, gs, lt, x.x, x.y, owningPlayerNo, ms, o.x, o.y)
							Else
								AttemptFireWeaponTargetProjectile(gd, gs, lt, x.x, x.y, owningPlayerNo, ms, o.target)
							End If
						End If
					End If
				End If
			Next
		End If
			
		?debug
   			TProfiler.Leave("GameEntity::PerformFireOnTarget")
  		?
	End Method
	
	Method AnimateSimple(timeSeconds:Double, gs:TGameState, ms:Long, gd:TGameData)
		?debug
   			TProfiler.Enter("GameEntity::AnimateSimple")
  		?

		' Accelerate/decelerate
		If currentSpeed < targetSpeed Then 
			Local a:Double = speed * timeSeconds * 0.1
			currentSpeed :+ a
			If currentSpeed > (targetSpeed - a) Then 
				'Print "Achieved velocity"
				currentSpeed = targetSpeed 
				distanceToDecelerate = distanceTravelled
				'Print distanceToDecelerate
			End If
		ElseIf currentSpeed > targetSpeed Then 
			Local a:Double = speed * timeSeconds * 0.1
			currentSpeed :- a
			If currentSpeed < (targetSpeed + a) Then 
				'Print "Achieved slowdown"
				currentSpeed = targetSpeed 
				distanceToDecelerate = distanceTravelled
			End If
		End If
		
		' Work out new position
		AddPolarToCartesian(currentSpeed * timeSeconds, angle, x, y)
		
		' Add to distance
		distanceTravelled :+ currentSpeed * timeSeconds
		
		' Explosion?
		If ms - died < 1000 And vessel.fighter = 0 And lastExplosion <> -1 Then
			Local ts:Long = ms - lastExplosion
			If Rand(ts) > 50 Then
				Local cX:Double = (Rand(0, width) - (width / 2)) * SectionSizeX
				Local cY:Double = (Rand(0, height) - (height / 2)) * SectionSizeY
				Local xp:TGameEntity = TGameEntity.CreateExplosion(gs.entityID, Null, owningPlayerNo, Null, x + cX, y + cY, gd.weapons, ms)
				ListAddFirst(gs.entitiesProjectilesDead, xp)
				gs.entityID :+ 1
				lastExplosion = ms
			End If
		End If

		?debug
   			TProfiler.Leave("GameEntity::AnimateSimple")
  		?
	End Method
	
	' 0.09718
	Method Animate(timeSeconds:Double, gs:TGameState, ms:Long, gd:TGameData)
		?debug
   			TProfiler.Enter("GameEntity::Animate")
  		?

		' Work out new position
		AddPolarToCartesian(currentSpeed * timeSeconds, angle, x, y)
		
		' Add to distance
		distanceTravelled :+ currentSpeed * timeSeconds
		
		' No more actions for projectiles
		If vessel.ship = 0 And vessel.missile = 0 Then 
			?debug
	   			TProfiler.Leave("GameEntity::Animate")
  			?
			Return
		End If

		' Do we need to rotate?
		Local setNewSpeed:Int = 0
		If jumping = 1 Then
		ElseIf vessel.ship = 0 And distanceTravelled < 250 Then
		ElseIf Same(angle, targetAngle) = 1 Then
			'Print "At angle"
			If currentSpeed = 0 Then setNewSpeed = 1
		ElseIf angle > targetAngle Then
			angle :- dps * timeSeconds
			If angle < targetAngle Then 
				'Print "Achieved angle"
				angle = targetAngle
				setNewSpeed = 1
			End If
		Else 
			angle :+ dps * timeSeconds
			If angle > targetAngle Then 
				'Print "Achieved angle"
				angle = targetAngle
				setNewSpeed = 1
			End If
		End If  
		angle = AdjustAngle(angle)
		
		' Orders?
		If ms > lastOrderCheck + 100 And ordersHeld = 0 And jumping = 0 And orders.Count() > 0 Then
			Local o:TOrder = TOrder(orders.First())
			If setNewSpeed = 1 And vessel.fighter = 0 Then 
				'Print "Setting new speed"
				targetSpeed = speed * o.percent
			End If
			UpdateOrder(o, gs, ms, gd)
				If o.nextOrder = 1 And orders.Count() > 1 Then
				o = TOrder(orders.ValueAtIndex(1))
				UpdateOrder(o, gs, ms, gd)
			End If
		End If
		
		' Trail
		CheckTrail()
				
		' Accelerate/decelerate
		If jumping = 1 Then
		ElseIf currentSpeed < targetSpeed Then 
			Local a:Double = speed * timeSeconds * 0.25
			currentSpeed :+ a
			If currentSpeed > (targetSpeed - a) Then 
				'Print "Achieved velocity"
				currentSpeed = targetSpeed 
				distanceToDecelerate = distanceTravelled
				'Print distanceToDecelerate
			End If
		ElseIf currentSpeed > targetSpeed Then 
			Local a:Double = speed * timeSeconds * 0.25
			If speed = 0 Then a = 50 * timeSeconds * 0.25 
			currentSpeed :- a
			If currentSpeed < (targetSpeed + a) Then 
				'Print "Achieved slowdown"
				currentSpeed = targetSpeed 
				distanceToDecelerate = distanceTravelled
			End If
		End If
		
		' No more actions for missiles
		If vessel.ship = 0 And vessel.missile = 1 Then 
			?debug
	   			TProfiler.Leave("GameEntity::Animate")
  			?
			Return
		End If

		' AI
		If jumping = 0 And computerControlled = 1 And ms > timeLastAI + 250 Then
			If Rand(1, 10) > 7 Then
				ai.Update(gs, ms)
			End If
			timeLastAI = ms
		End If
		
		' Slow down if pulling escorts
		If escortCount > 0 And targetSpeed > speed * 0.75 Then targetSpeed = speed * 0.75
		
		' Auto-fire
		If vessel.ship = 1 Then
			If vessel.fighter = 0 Then
				AutoFireWeapons(gs, ms, gd)
			ElseIf returningToCarrier = 0 Then
				AutoFireWeaponFighter(gs, ms, gd)
			End If
		End If

		' Fighter?
		If vessel.fighter = 1 And returningToCarrier = 1 Then
			If carrier.died > 0 Then
				Destroy(gd, gs, "lost its parent carrier and is awaiting rescue.", ms, 0)
			End If
		End If
	
		' Repair & regenerate
		If vessel.ship = 1 Then
			ShieldDo(timeSeconds)
			RepairDo(gd, gs, timeSeconds, ms)
		End If
		
		?debug
   			TProfiler.Leave("GameEntity::Animate")
  		?
	End Method
	
	Method VisibleCheck:Int(d:Double, a:Double, w:TWeaponClass)
		Return Abs(d) < a
	End Method
	
	Method TargetList:TList(range:Double)
		If range = 250 Then 
			Return targetsWithinRange250
		ElseIf range = 500 Then 
			Return targetsWithinRange500
		ElseIf range = 2500 Then 
			Return targetsWithinRange2500
		ElseIf range = 5000 Then 
			Return targetsWithinRange5000
		ElseIf range = 10000 Then 
			Return targetsWithinRange10000
		ElseIf range = 15000 Then 
			Return targetsWithinRange15000
		ElseIf range = 30000 Then 
			Return targetsWithinRange30000
		End If
		Print "Unknown range: " + range
		End
	End Method
	
	Method FindTargetNoTube:TGameEntity(gs:TGameState, w:TWeaponClass)
		If w.defensive = 0 Then
			Return FindTargetVesselNoTube(gs, w)
		Else
			Return FindTargetProjectilesNoTube(gs, w)
		End If
	End Method
	
	Method FindTarget:TGameEntity(gs:TGameState, l:TBlock, defensive:Int, x:Int, y:Int)
		If defensive = 0 Then
			Return FindTargetVessel(gs, l, x, y)
		Else
			Return FindTargetProjectiles(gs, l)
		End If
	End Method
	
	Method FindTargetVessel:TGameEntity(gs:TGameState, l:TBlock, x:Int, y:Int)
		?debug
   			TProfiler.Enter("GameEntity::FindTargetVessel")
  		?
		Local lst:TList = CreateList()
		Local closest:TGameEntity
		Local closestDistance:Double = l.weapon.maxRange
		For Local get:TGameEntity = EachIn TargetList(l.weapon.maxRange)
			If l.weapon.radarSeeking = 1 And get.radar = TVessel.DefaultRadarRange Then Continue

			' Offset
			Local mX:Double, mY:Double
			Select l.rot
			Case 0
				mX = (x - centreX) * SectionSizeX
				mY = (y - centreY - 0.5) * SectionSizeY
			Case 1
				mX = (x - centreX + 0.5) * SectionSizeX
				mY = (y - centreY) * SectionSizeY
			Case 2 
				mX = (x - centreX) * SectionSizeX
				mY = (y - centreY + 0.5) * SectionSizeY
			Case 3
				mX = (x - centreX - 0.5) * SectionSizeX
				mY = (y - centreY) * SectionSizeY
			End Select
			RotateAroundOrigin(mX, mY, angle + 90)

			Local actualAngle:Double = AdjustAngle(AngleBetweenPoints(Self.x + mX, Self.y - mY, get.x, get.y))
			Local dist:Double = DistanceBetweenPoints(Self.x + mX, Self.y - mY, get.x, get.y)
			Local tb:Double = l.TubeAngle(angle)
			Local d:Double = DifferenceBetweenAngles(tb, actualAngle)

			' Can we see it?
			Local a:Double
			If l.weapon.t = TWeaponClass.missileType Then a = TWeaponClass.MissileAngle Else a = TWeaponClass.RailgunAngle
			If vessel.fighter = 0 And l.weapon.damage > 15 And get.mass < 250 Then Continue
			If VisibleCheck(d, a, l.weapon) Then
				If dist < closestDistance Then
					closestDistance = dist
					closest = get
				End If
				ListAddFirst(lst, get)
			End If 
		Next
		If lst.Count() = 0 Then 
			?debug
   				TProfiler.Leave("GameEntity::FindTargetVessel")
  			?
			Return Null
		End If

		' 75% chance of just choosing closest, but not all the time as the opponent might place a low value ship nearby to detract fire
		If Rnd() < 0.75 Then 
			?debug
   				TProfiler.Leave("GameEntity::FindTargetVessel")
  			?
			Return closest
		End If

		Local r:Int = Rand(lst.Count()) - 1
		Local g:TGameEntity = TGameEntity(lst.ValueAtIndex(r))
		?debug
   			TProfiler.Leave("GameEntity::FindTargetVessel")
		?
		Return g
	End Method
	
	Method FindTargetProjectiles:TGameEntity(gs:TGameState, l:TBlock)
		?debug
   			TProfiler.Enter("GameEntity::FindTargetProjectiles")
		?
		Local lst:TList = CreateList()
		Local closest:TGameEntity
		Local closestDistance:Double = 9999999999
		For Local get:TGameEntity = EachIn gs.entitiesProjectiles[owningPlayerNo ~ 1]
			If get.w.defensive = 0 Then

				' Offset
				Local mX:Double, mY:Double
				Select l.rot
				Case 0
					mX = (x - centreX) * SectionSizeX
					mY = (y - centreY - 0.5) * SectionSizeY
				Case 1
					mX = (x - centreX + 0.5) * SectionSizeX
					mY = (y - centreY) * SectionSizeY
				Case 2 
					mX = (x - centreX) * SectionSizeX
					mY = (y - centreY + 0.5) * SectionSizeY
				Case 3
					mX = (x - centreX - 0.5) * SectionSizeX
					mY = (y - centreY) * SectionSizeY
				End Select
				RotateAroundOrigin(mX, mY, angle + 90)
		
				Local actualAngle:Double = AdjustAngle(AngleBetweenPoints(Self.x + mX, Self.y - mY, get.x, get.y))
				Local dist:Double = DistanceBetweenPoints(Self.x + mX, Self.y - mY, get.x, get.y)
				Local tb:Double = l.TubeAngle(angle)
				Local d:Double = DifferenceBetweenAngles(tb, actualAngle)

				' Can we see it?
				Local a:Double
				If l.weapon.t = TWeaponClass.missileType Then a = TWeaponClass.MissileAngle Else a = TWeaponClass.RailgunAngle
				If VisibleCheck(d, a, l.weapon) And dist < l.weapon.maxRange And CanSeeTarget(get) = 1 Then
					If dist < closestDistance Then
						closestDistance = dist
						closest = get
					End If
					ListAddFirst(lst, get)
				End If 
			End If
		Next
		If lst.Count() = 0 Then Return Null

		' 75% chance of just choosing closest, but not all the time as the opponent might place a low value ship nearby to detract fire
		If Rnd() < 0.75 Then 
			?debug
   				TProfiler.Leave("GameEntity::FindTargetProjectiles")
			?
			Return closest
		End If

		Local r:Int = Rand(lst.Count()) - 1
		Local g:TGameEntity = TGameEntity(lst.ValueAtIndex(r))
		?debug
   			TProfiler.Leave("GameEntity::FindTargetProjectiles")
		?
		Return g
	End Method

	Method FindTargetVesselNoTube:TGameEntity(gs:TGameState, w:TWeaponClass)
		?debug
   			TProfiler.Enter("GameEntity::FindTargetVesselNoTube")
		?
		Local lst:TList = CreateList()
		Local closest:TGameEntity = Null
		Local closestDistance:Double = w.maxRange
		Local a:TList = TargetList(w.maxRange)
		For Local get:TGameEntity = EachIn TargetList(w.maxRange)
			If MapContains(targets, get) = Null Then
				If w.radarSeeking = 1 And get.radar = TVessel.DefaultRadarRange Then Continue
				Local dist:Double = DistanceBetweenPoints(x, y, get.x, get.y)
				If vessel.fighter = 0 And w.damage > 15 And get.mass < 250 Then Continue
				If dist < closestDistance Then
					closestDistance = dist
					closest = get
				End If
				ListAddFirst(lst, get)
			End If
		Next
		If lst.Count() = 0 Then Return Null

		' 75% chance of just choosing closest, but not all the time as the opponent might place a low value ship nearby to detract fire
		If Rnd() < 0.75 Then 
			?debug
   				TProfiler.Leave("GameEntity::FindTargetVesselNoTube")
			?
			Return closest
		End If

		Local r:Int = Rand(lst.Count()) - 1
		Local g:TGameEntity = TGameEntity(lst.ValueAtIndex(r))
		?debug
   			TProfiler.Leave("GameEntity::FindTargetVesselNoTube")
		?
		Return g
	End Method

	Method FindTargetProjectilesNoTube:TGameEntity(gs:TGameState, w:TWeaponClass)
		?debug
   			TProfiler.Enter("GameEntity::FindTargetProjectilesNoTube")
		?
		Local lst:TList = CreateList()
		Local closest:TGameEntity
		Local closestDistance:Double = 9999999999
		For Local get:TGameEntity = EachIn gs.entitiesProjectiles[owningPlayerNo ~ 1]
			If get.w.defensive = 0 And get.w.t = TWeaponClass.missileType Then
				Local dist:Double = DistanceBetweenPoints(x, y, get.x, get.y)
				If dist < w.maxRange And CanSeeTarget(get) = 1 Then
					If dist < closestDistance Then
						closestDistance = dist
						closest = get
					End If
					ListAddFirst(lst, get)
				End If 
			End If
		Next
		If lst.Count() = 0 Then Return Null

		' 75% chance of just choosing closest, but not all the time as the opponent might place a low value ship nearby to detract fire
		If Rnd() < 0.75 Then 
			?debug
   				TProfiler.Leave("GameEntity::FindTargetProjectilesNoTube")
			?
			Return closest
		End If

		Local r:Int = Rand(lst.Count()) - 1
		Local g:TGameEntity = TGameEntity(lst.ValueAtIndex(r))
		?debug
   			TProfiler.Leave("GameEntity::FindTargetProjectilesNoTube")
		?
		Return g
	End Method

	Method AttemptFireWeaponTargetMissile(gd:TGameData, gs:TGameState, lt:TBlock, x:Int, y:Int, owningPlayer:Int, ms:Long, target:TGameEntity)
		?debug
   			TProfiler.Enter("GameEntity::AttemptFireWeaponTargetMissile")
		?
		
		' Reload needed?
		If lt.reloadNeeded > 0 Then
			If ms < lt.reloadNeeded Then
				?debug
   					TProfiler.Leave("GameEntity::AttemptFireWeaponTargetMissile")
				?
				Return
			End If 
			LoadAmmo(x, y, gd.weapons, ms, gs, 0)
			?debug
   				TProfiler.Leave("GameEntity::AttemptFireWeaponTargetMissile")
			?
			Return
		End If

		' Empty?
		If lt.numberRemaining <= 0 And lt.numberRemaining <> -1 Then 
			?debug
   				TProfiler.Leave("GameEntity::AttemptFireWeaponTargetMissile")
			?
			Return
		End If
		
		' Offset
		Local mX:Double, mY:Double
		Select lt.rot
		Case 0
			mX = (x - centreX) * SectionSizeX
			mY = (y - centreY - 0.5) * SectionSizeY
		Case 1
			mX = (x - centreX + 0.5) * SectionSizeX
			mY = (y - centreY) * SectionSizeY
		Case 2 
			mX = (x - centreX) * SectionSizeX
			mY = (y - centreY + 0.5) * SectionSizeY
		Case 3
			mX = (x - centreX - 0.5) * SectionSizeX
			mY = (y - centreY) * SectionSizeY
		End Select
		RotateAroundOrigin(mX, mY, angle + 90)

		' Work out angle
		Local actualAngle:Double = AdjustAngle(AngleBetweenPoints(Self.x + mX, Self.y - mY, target.x, target.y))
		Local tubeAngle:Double = lt.TubeAngle(angle)

		' Misfire?
		If vessel.fighter = 1 Or RndDouble() < (condition[x, y] * onOff[x, y]) Then
			Local entity:TGameEntity = TGameEntity.CreateMissile(gs.entityID, Null, owningPlayer, gs.missile, Self.x + mX, Self.y - mY, tubeAngle, target, lt.weapon, ms)
			If entity.currentSpeed < currentSpeed Then entity.currentSpeed = currentSpeed
			ListAddFirst(gs.entitiesProjectiles[owningPlayerNo], entity)
			Local dist:Double = DistanceBetweenPoints(gs.centreX, gs.centreY, x, y)
			gd.sound.PlayGunSound(lt.weapon.sound, ms, 1.0 / (dist / gs.scale / 5000.0))
			gs.entityID :+ 1
			lt.fired = ms
			If lt.weapon.defensive = 1 Then
				' mark target as targeted
				For Local t:TGameEntity = EachIn gs.entitiesProjectiles[owningPlayerNo ~ 1]
					t.alreadyTargeted = 1
				Next
			End If 
			lt.numberRemaining :- 1
			If lt.numberRemaining = 0 Then
				lt.reloadNeeded = ms + 10000
				If vessel.fighter = 0 Then gs.AddMessage("<" + name + "> is reloading.", ms, owningPlayerNo)
			End If
		Else
			If owningPlayerNo = 0 Or gs.optionShowAllMessages = 1
				If vessel.fighter = 0 Then gs.AddMessage("<" + name + "> had a missile misfire.", ms, owningPlayerNo)
			End If
			lt.fired = ms + (lt.weapon.coolDown * 2)
		End If
		?debug
  				TProfiler.Leave("GameEntity::AttemptFireWeaponTargetMissile")
		?
	End Method
	
	Method AttemptFireWeaponTargetProjectile(gd:TGameData, gs:TGameState, lt:TBlock, x:Int, y:Int, owningPlayer:Int, ms:Long, target:TGameEntity)
		AttemptFireWeaponTargetProjectileXY(gd, gs, lt, x, y, owningPlayer, ms, target.x, target.y)
	End Method
	
	Method AttemptFireWeaponTargetProjectileXY(gd:TGameData, gs:TGameState, lt:TBlock, x:Int, y:Int, owningPlayer:Int, ms:Long, targetX:Double, targetY:Double)
		?debug
	  		TProfiler.Enter("GameEntity::AttemptFireWeaponTargetProjectileXY")
		?

		' Reload needed?
		If lt.reloadNeeded > 0 Then
			If ms < lt.reloadNeeded Then 
				?debug
			  		TProfiler.Leave("GameEntity::AttemptFireWeaponTargetProjectileXY")
				?
				Return
			End If 
			LoadAmmo(x, y, gd.weapons, ms, gs, 0)
			?debug
		  		TProfiler.Leave("GameEntity::AttemptFireWeaponTargetProjectileXY")
			?
			Return
		End If
		
		' Empty?
		If lt.numberRemaining <= 0 And lt.numberRemaining <> -1 Then 
			?debug
		  		TProfiler.Leave("GameEntity::AttemptFireWeaponTargetProjectileXY")
			?
			Return			
		End If

		' Offset
		Local mX:Double, mY:Double
		If vessel.fighter = 0 Then
			Select lt.rot
			Case 0
				mX = (x - centreX) * SectionSizeX
				mY = (y - centreY - 0.5) * SectionSizeY
			Case 1
				mX = (x - centreX + 0.5) * SectionSizeX
				mY = (y - centreY) * SectionSizeY
			Case 2 
				mX = (x - centreX) * SectionSizeX
				mY = (y - centreY + 0.5) * SectionSizeY
			Case 3
				mX = (x - centreX - 0.5) * SectionSizeX
				mY = (y - centreY) * SectionSizeY
			End Select
			RotateAroundOrigin(mX, mY, angle + 90)
		End If

		' Work out angle
		Local actualAngle:Double = AdjustAngle(AngleBetweenPoints(Self.x + mX, Self.y - mY, targetX, targetY))
		Local tb:Double = lt.TubeAngle(angle)
		Local d:Double = DifferenceBetweenAngles(tb, actualAngle)
		Local tubeAngle:Double = (tb + d)		
		
		' Misfire?
		If vessel.fighter = 1 Or RndDouble() < (condition[x, y] * onOff[x, y]) Then
			If vessel.fighter = 0 And strafe[x, y] = 1 Then tubeAngle:+ ((RndDouble() - 0.5) * 10.0)
			Local entity:TGameEntity = TGameEntity.CreateBullet(gs.entityID, Null, owningPlayer, gs.bullet, Self.x + mX, Self.y - mY, tubeAngle, lt.weapon, ms)
			If entity.currentSpeed < currentSpeed Then entity.currentSpeed = currentSpeed
			ListAddFirst(gs.entitiesProjectiles[owningPlayerNo], entity)
			Local dist:Double = DistanceBetweenPoints(gs.centreX, gs.centreY, x, y)
			gd.sound.PlayGunSound(lt.weapon.sound, ms, 1.0 / (dist / gs.scale / 5000.0))
			gs.entityID :+ 1
			lt.fired = ms
			If lt.weapon.defensive = 1 Then
				' mark target as targeted
				For Local t:TGameEntity = EachIn gs.entitiesProjectiles[owningPlayerNo ~ 1]
					t.alreadyTargeted = 1
				Next
			End If 
			lt.numberRemaining :- 1
			If lt.numberRemaining = 0 Then
				lt.reloadNeeded = ms + 10000
				If vessel.fighter = 0 Then gs.AddMessage("<" + name + "> is reloading.", ms, owningPlayerNo)
			End If
		Else
			If owningPlayerNo = 0 Or gs.optionShowAllMessages = 1
				If vessel.fighter = 0 Then gs.AddMessage("<" + name + "> had a railgun misfire.", ms, owningPlayerNo)
			End If
			lt.fired = ms + (lt.weapon.coolDown * 2)
		End If
		?debug
	 		TProfiler.Leave("GameEntity::AttemptFireWeaponTargetProjectileXY")
		?
	End Method

	Method Fire(gs:TGameState, ms:Long, l:TBlock, x:Int, y:Int, gd:TGameData)
		?debug
		 	TProfiler.Enter("GameEntity::Fire")
		?
		If ms < l.fired + l.weapon.coolDown Then 
			gs.AddMessage("<" + name + ">, not ready to launch.", ms, owningPlayerNo)
			?debug
			 	TProfiler.Leave("GameEntity::Fire")
			?
			Return
		End If
		Local tubeAngle:Double = l.TubeAngle(angle)
		Local t:TGameEntity = FindTargetVesselNoTube(gs, l.weapon)
		If t <> Null Then
			AttemptFireWeaponTargetMissile(gd, gs, l, x, y, owningPlayerNo, ms, t)
		Else
			gs.AddMessage("<" + name + ">, no valid target.", ms, owningPlayerNo)
		End If
		?debug
		 	TProfiler.Leave("GameEntity::Fire")
		?
	End Method
	
	Method AutoFireWeaponFighter(gs:TGameState, ms:Long, gd:TGameData)
		?debug
		 	TProfiler.Enter("GameEntity::AutoFireWeaponFighter")
		?
		If ms >= (fighterL.fired + fighterL.weapon.coolDown) Then
			Local t:TGameEntity = FindTarget(gs, fighterL, fighterL.weapon.defensive, 0, 0)
			If t <> Null Then
				AttemptFireWeaponTargetProjectile(gd, gs, fighterL, 0, 0, owningPlayerNo, ms, t)
				If fighterL.numberRemaining = 0 Then 
					returningToCarrier = 1
					orders = CreateList()
					AddPursueOrder(carrier, 0, 0, ms, 0, 0)
				End If
			End If
		End If
		?debug
		 	TProfiler.Leave("GameEntity::AutoFireWeaponFighter")
		?
	End Method
	
	Method AutoFireWeapons(gs:TGameState, ms:Long, gd:TGameData)
		?debug
		 	TProfiler.Enter("GameEntity::AutoFireWeapons")
		?
		
		' Loop through all missiles, if any can fire, select a target
		For Local x:TXY = EachIn vessel.missiles
			Local l:TBlock = shape[x.x, x.y]
			If l.weapon <> Null And l.weapon.manuallyFired = 0 And l.numberRemaining > 0 Then
				Local timeToTest:Long = l.fired + (Double(l.weapon.coolDown) / autoFire[x.x, x.y])
				If autoFire[x.x, x.y] > 0 And onOff[x.x, x.y] > 0.0 And ms > timeToTest Then
					Local t:TGameEntity = FindTarget(gs, l, l.weapon.defensive, x.x, x.y)
					If t <> Null Then
						AttemptFireWeaponTargetMissile(gd, gs, l, x.x, x.y, owningPlayerNo, ms, t)
					End If
				End If
			End If
		Next 

		' Loop through all guns, if any can fire, select a target
		For Local x:TXY = EachIn vessel.guns
			Local l:TBlock = shape[x.x, x.y]
			If l.weapon <> Null And l.weapon.manuallyFired = 0 And l.numberRemaining > 0 Then
				Local timeToTest:Long = l.fired + (Double(l.weapon.coolDown) / autoFire[x.x, x.y])
				If autoFire[x.x, x.y] > 0 And onOff[x.x, x.y] > 0.0 And ms > timeToTest Then
					Local t:TGameEntity = FindTarget(gs, l, l.weapon.defensive, x.x, x.y)
					If t <> Null Then
						AttemptFireWeaponTargetProjectile(gd, gs, l, x.x, x.y, owningPlayerNo, ms, t)
					End If
				End If
			End If
		Next 
		?debug
		 	TProfiler.Leave("GameEntity::AutoFireWeapons")
		?
	End Method
	
	Method CanSeeTarget:Int(target:TGameEntity)
		Return target.targetPainted
	End Method
	
	Method ShieldDo(timeSeconds:Double)
		?debug
   			TProfiler.Enter("GameEntity::ShieldDo")
  		?
		If shieldRemaining < shield Then
			shieldRemaining :+ shield * shieldRegenerate * timeSeconds
		End If
		If shieldRemaining > shield Then shieldRemaining = shield
		?debug
   			TProfiler.Leave("GameEntity::ShieldDo")
  		?
	End Method
	
	Method RepairDo(gd:TGameData, g:TGameState, timeSeconds:Double, ms:Long)
		?debug
		 	TProfiler.Enter("GameEntity::RepairDo")
		?
		If armourRemaining < armour And repairRate > 0 Then
			armourRemaining :+ armour * repairRate * timeSeconds
		End If
		If armourRemaining > armour Then armourRemaining = armour
		If vessel.fighter = 1 Then Return
		For Local y:Int = 0 To TVessel.MaxShapeY - 1
			For Local x:Int = 0 To TVessel.MaxShapeX - 1
				If condition[x, y] = 0.0 Then
					' no repair
				ElseIf condition[x, y] < 1.0 Then
					If onOff[x, y] = 0.0 Then
						condition[x, y] :+ (repairRate * timeSeconds) * 4.0
					Else
						condition[x, y] :+ repairRate * timeSeconds
					End If
				End If
				If condition[x, y] > 1.0 Then condition[x, y] = 1.0
			Next
		Next
		
		' Do we have enough power?
		Local found:Int = 0
		While pwrOut > pwrIn
			found = 0
			If found = 0 Then
				For Local x:TXY = EachIn vessel.modules
					If onOff[x.x, x.y] > 0.0 And shape[x.x, x.y].variant <> 1 Then
						onOff[x.x, x.y] = 0.0
						If owningPlayerNo = 0 Or g.optionShowAllMessages = 1 Then g.AddMessage("<" + name + "> had a module disabled due to insufficient power.", ms, owningPlayerNo)
						found = 1
						Exit
					End If
				Next
			End If
			If found = 0 Then
				For Local x:TXY = EachIn vessel.missiles
					If onOff[x.x, x.y] > 0.0 Then
						onOff[x.x, x.y] = 0.0
						If owningPlayerNo = 0 Or g.optionShowAllMessages = 1 Then g.AddMessage("<" + name + "> had a weapon disabled due to insufficient power.", ms, owningPlayerNo)
						found = 1
						Exit
					End If
				Next
			End If 
			If found = 0 Then
				For Local x:TXY = EachIn vessel.guns
					If onOff[x.x, x.y] > 0.0 Then
						onOff[x.x, x.y] = 0.0
						If owningPlayerNo = 0 Or g.optionShowAllMessages = 1 Then g.AddMessage("<" + name + "> had a weapon disabled due to insufficient power.", ms, owningPlayerNo)
						found = 1
						Exit
					End If
				Next
			End If
			If found = 0 Then
				For Local x:TXY = EachIn vessel.thrusters
					If onOff[x.x, x.y] > 0.0 Then
						onOff[x.x, x.y] = 0.0
						If owningPlayerNo = 0 Or g.optionShowAllMessages = 1 Then g.AddMessage("<" + name + "> had a thruster disabled due to insufficient power.", ms, owningPlayerNo)
						found = 1
						Exit
					End If
				Next
			End If
			If found = 0 Then 
				Exit
			End If
			ApplyDamage(gd, g, ms)
		End While
		
		?debug
		 	TProfiler.Leave("GameEntity::RepairDo")
		?
	End Method
	
	Method CalculateAutoFireArcs()
		?debug
		 	TProfiler.Enter("GameEntity::CalculateAutoFireArcs")
		?

		' Reset
		autoN = 0
		autoS = 0
		autoE = 0
		autoW = 0
		
		'Check missiles first
		For Local l:TXY = EachIn vessel.missiles
			If onOff[l.x, l.y] = 1.0 Then
				Select shape[l.x, l.y].rot
				Case 0
					autoN :| 1
				Case 1
					autoE :| 1
				Case 2
					autoS :| 1
				Case 3
					autoW :| 1
				End Select
			End If
		Next
		
		' Guns
		For Local l:TXY = EachIn vessel.guns
			If onOff[l.x, l.y] = 1.0 Then
				Select shape[l.x, l.y].rot
				Case 0
					autoN :| 2
				Case 1
					autoE :| 2
				Case 2
					autoS :| 2
				Case 3
					autoW :| 2
				End Select
			End If
		Next
		?debug
		 	TProfiler.Leave("GameEntity::CalculateAutoFireArcs")
		?
	End Method

	Method Destroy(gd:TGameData, g:TGameState, msg:String, ms:Long, explosion:Int)
		?debug
   			TProfiler.Enter("GameEntity::Destroy")
  		?
		died = ms
		removeWhen = ms + 1000000
		For Local o:TOrder = EachIn orders
			CheckEscortOrder(g, o)
		Next
		If currentSpeed < speed / 16 Then
			targetSpeed = 0
		ElseIf currentSpeed > 0 Then
			targetSpeed = speed / 16
		End If
		If explosion = 1 Then
			If vessel.fighter = 0 Then
				Local xp:TGameEntity = TGameEntity.CreateExplosion(g.entityID, Null, owningPlayerNo, Null, x, y, gd.weapons, ms)
				ListAddFirst(g.entitiesProjectilesDead, xp)
			Else
				Local xp:TGameEntity = TGameEntity.CreateExplosionSmall(g.entityID, Null, owningPlayerNo, Null, x, y, gd.weapons, ms)
				ListAddFirst(g.entitiesProjectilesDead, xp)
			End If
			g.entityID :+ 1
			lastExplosion = ms
		Else
			lastExplosion = -1
		End If
		ListAddFirst(g.entitiesDead, Self)
		ListRemove(g.entities[owningPlayerNo], Self)
		g.AddMessage("<" + name + "> " + msg, ms, owningPlayerNo)
		?debug
   			TProfiler.Leave("GameEntity::Destroy")
  		?
	End Method

End Type



