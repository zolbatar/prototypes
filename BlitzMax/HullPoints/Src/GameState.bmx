SuperStrict
Import "Buttons.bmx"
Import "Fleet.bmx"
Import "Helper.bmx"
Import "Piece.bmx"
Import "VictoryConditions.bmx"
Import "VesselBullet.bmx"
Import "VesselFighter.bmx"
Import "VesselMissile.bmx"
Import "VesselShrapnel.bmx"
Import "WeaponClass.bmx"

Type TMessage
	Field time:String, ms:Long, s:String, playerNo:Int
End Type

Const DifficultyEasy:Int = 0, DifficultyHard:Int = 1
Global GameDifficulty:Int = DifficultyHard

Type TGameState

	' Fleets
	Field fleets:TFleet[2]
	
	' Entities
	Field entityID:Int = 0
	Field entitiesObjects:TList = CreateList()
	Field entities:TList[2], entitiesReserve:TList = CreateList(), entitiesDead:TList = CreateList()
	Field entitiesProjectiles:TList[2], entitiesProjectilesDead:TList = CreateList()
	Field jumpPoints:TList = CreateList()
	
	' Game stuff
	Field milliStart:Long = 0
	Field p1PointsInitial:Int, p2PointsInitial:Int, p1PointsLimit:Int
	Field p1Points:Int, p1PointsReserve:Int, p2Points:Int, p2PointsReserve:Int, victoryCondition:Int = 0, victoryHoldOut:Long = 0
	Field victoryX:Double, victoryY:Double, victoryPointList:TList = CreateList()
	Field victoryEntityList:TList = CreateList(), lastMissionCheck:Long = 0, remaining:Int = 0
	
	' View
	Field worldSizeX:Double = 1500000.0, worldSizeY:Double = 1000000.0, mapSectionSize:Double = 50000
	Field centreX:Double, centreY:Double, rotate:Double = 0.0, mapViewCentreX:Double, mapViewCentreY:Double
	Field ScaleLevels:Int = 15
	Field scale:Double, strategicScale:Double = 100.0, scaleSet:Double, scaleSetDiff:Double, scalePortionIndex:Int = 0, scalePortionRange:Double[]

	' Map view sizing
	Field ratioX:Double, ratioY:Double, sizeX:Double, sizeY:Double, size:Int
	
	' UI
	Field frameTime:Long = 0, calcTime:Long = 0
	
	' Options
	Field optionShowAllMessages:Int = 1, optionShowEnemyInfo:Int = 0, showStats:Int = 1, showMessages:Int = 0, missilesFindNewTarget:Int = 1
	Field showRadar:Int = 1, showOrders:Int = 0, showMissileTargets:Int = 0, cinematicMode:Int = 1, showStars:Int = 1, showTrails:Int = 1
	Field allowAIEnemySelection:Int = 0, bulletsInColour:Int = 1, showFightersIconView:Int = 1
	
	' Orders
	Field moveOrderStep:Int = 0, pursueOrderStep:Int = 0, fireTargetStep:Int = 0, addProtectVesselStep:Int = 0
	Field fireChosen:String = "", headingOrderStep:Int = 0, addScriptStep:Int = 0, setVictoryConditionStep:Int = 0
	Field autoBow:Int = 0, autoStern:Int = 0, autoStarboard:Int = 0, autoPort:Int = 0, removeOrderWhenArrived:Int = 0, pursueDistance:Double = 0
	Field rateWeapon:Int = 0, rateFull:Int = 0, rateHalf:Int = 0, rateQuarter:Int = 0, rateHarassing:Int = 0, pursueIsEscort:Int = 0

	' Missiles, bullets
	Field missile:TVessel = TVesselMissile.Create()
	Field bullet:TVessel = TVesselBullet.Create()
	Field shrapnel:TVessel = TVesselShrapnel.Create()
	Field fighter:TVessel = TVesselFighter.Create()
	
	' Mission builder stuff
	Field addPlanetMode:Int = 0, addVesselMode:Int = 0, moveItemMode:Int = 0, addEscortStep:Int = 0, chooseAIStep:Int = 0, addWaypointStep:Int = 0
	Field addAsteroidMode:Int = 0
	
	' Messages
	Field messages:TList = CreateList(), messageCount:Int = 0
	Const MessageRepeat:Int = 30000
		
	Function Create:TGameState()
		Local gs:TGameState = New TGameState
		gs.entities[0] = CreateList()
		gs.entities[1] = CreateList()
		gs.entitiesProjectiles[0] = CreateList()
		gs.entitiesProjectiles[1] = CreateList()
		Return gs
	End Function
	
	Method ConfigureZoom()
		Select worldSizeX
		Case 60000
			ScaleLevels = 15
		Case 150000
			ScaleLevels = 17
		Case 300000
			ScaleLevels = 19
		End Select
		scalePortionRange = New Double[ScaleLevels]
		Local prev:Double = strategicScale
		For Local i:Int = 0 To ScaleLevels - 1
			If i  = 0 Then 
				scalePortionRange[i] = prev
			Else
				scalePortionRange[i] = prev * 0.75
			End If
			prev = scalePortionRange[i]
		Next
		ResetScale()
	End Method
	
	Method TranslateXY(x:Double, y:Double, tX:Double Var, tY:Double Var)
'		?debug
'  			TProfiler.Enter("GameState::TranslateXY")
'  		?
		tX = (x - centreX) / scale
		tY = (centreY - y) / scale
'		?debug
'  			TProfiler.Leave("GameState::TranslateXY")
'  		?
	End Method
	
	Method AddMessage(s:String, ms:Long, player:Int)
		?debug
   			TProfiler.Enter("GameState::AddMessage")
  		?
		Local m:TMessage = New TMessage
		m.time = CurrentTime()
		m.ms = ms
		m.s = s
		m.playerNo = player
		ListAddFirst(messages, m)
		messageCount :+ 1
		?debug
   			TProfiler.Enter("GameState::AddMessage")
  		?
	End Method
	
	Method ZoomIn()	
		If scalePortionIndex = ScaleLevels - 1 Then Return
		scalePortionIndex :+ 1
		scaleSet = scalePortionRange[scalePortionIndex]
		scaleSetDiff = scaleSet - scale
	End Method
	
	Method ZoomOut()
		If scalePortionIndex = 0 Then Return
		scalePortionIndex :- 1
		scaleSet = scalePortionRange[scalePortionIndex]
		scaleSetDiff = scaleSet - scale 
	End Method

	Method Zoom(frameTime:Double)
		?debug
   			TProfiler.Enter("GameState::Zoom")
  		?
		If scale < scaleSet Then 
			scale :+ scaleSetDiff * (frameTime * 5.0)
			If scale > scaleSet Then scale = scaleSet  
		End If
		If scale > scaleSet Then 
			scale :+ scaleSetDiff * (frameTime * 5.0)
			If scale < scaleSet Then scale = scaleSet  
		End If
		?debug
   			TProfiler.Enter("GameState::Zoom")
  		?
	End Method
	
	Method ResetScale()
		scale = scalePortionRange[0]
		scaleSet = scalePortionRange[0]
		scalePortionIndex = 0
	End Method
	
	Method CanScroll(gfx:TGFX, dX:Int Var, dY:Int Var, missionBuilder:Int)
		?debug
   			TProfiler.Enter("GameState::CanScroll")
  		?
		Local ToolbarHeight:Int = 60
		If missionBuilder = 0 Then ToolbarHeight = 0
		Local borderX:Int = gfx.width / 2
		Local borderY:Int = gfx.height / 2
		Local x1:Double, y1:Double, x2:Double, y2:Double
		TranslateXY(-worldSizeX / 2, -worldSizeY / 2, x1, y1)
		TranslateXY(worldSizeX / 2, worldSizeY / 2, x2, y2)
		If x1 + mapViewCentreX + dX > borderX Then 
			dX = borderX - (x1 + mapViewCentreX)
		ElseIf x2 - mapViewCentreX + dX < -borderX Then 
			dX = -(Int(x2 - mapViewCentreX) + borderX)
		End If
		If y2 + mapViewCentreY + dY > borderY Then 
			dY = borderY - (y2 + mapViewCentreY)
		ElseIf y1 - mapViewCentreY + ToolbarHeight + dY < -borderY Then 
			dY = -(Int(y1 - mapViewCentreY + ToolbarHeight) + borderY)
		End If
		?debug
   			TProfiler.Leave("GameState::CanScroll")
  		?
	End Method
	
End Type

