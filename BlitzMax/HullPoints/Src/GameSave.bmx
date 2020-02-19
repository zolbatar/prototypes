SuperStrict
Import "GameData.bmx"
Import "GameEntity.bmx"
Import "GameScenery.bmx"
Import "GameState.bmx"
Import "Profiler.bmx"
Import "XY.bmx"

Type TGameSave

	Function SaveMission(name:String, gs:TGameState)
		?debug
   			TProfiler.Enter("GameSave::SaveMission")
  		?

		' Open file
		Local file:TStream = WriteFile("Missions/" + name  + ".mis")
		If Not file RuntimeError "Failed to save Missions/" + name  + ".mis"

		' Data		
		WriteLine file, gs.fleets[0].name + "," + gs.fleets[1].name
		WriteLine file, gs.p1PointsLimit
		WriteLine file, gs.victoryCondition
		WriteLine file, gs.victoryHoldOut
		WriteLine file, gs.victoryX
		WriteLine file, gs.victoryY
		WriteLine file, gs.victoryPointList.Count()
		For Local xy:TXY = EachIn gs.victoryPointList
			WriteLine file, xy.x + "," + xy.y
		Next
		WriteLine file, gs.victoryEntityList.Count()
		For Local i:TGameEntity = EachIn gs.victoryEntityList
			WriteLine file, i.index
		Next
		
		' Map
		WriteLine file, gs.worldSizeX
		WriteLine file, gs.worldSizeY
		WriteLine file, gs.mapSectionSize
		
		' Vessels
		WriteLine file, gs.entities[0].Count() + gs.entities[1].Count()
		Local found:Int = 0
		For Local player:Int = 0 To 1
			For Local e:TGameEntity = EachIn gs.entities[player]
			
				' Check escort ID
				found = 0
				For Local e2:TGameEntity = EachIn gs.entities[player]
					If e2.index = e.ai.escortID Then
						found = 1
						Exit
					End If
				Next
				If found = 0 Then e.ai.escortID = -1
			
				Local s:String = e.name + "," + e.owningPlayerNo + "," + e.index + "," + e.x + "," + e.y + "," + e.angle + ","
				s :+ e.vessel.name + "," 
				s :+ e.armourremaining + "," + e.shieldremaining + "," + e.computerControlled + "," + e.ai.personality + ","
					s :+ e.ai.ignoreStartingWaypoint + "," + e.ai.escortID
				WriteLine file, s
				
				' Waypoints
				WriteLine file, e.waypoints.Count()
				For Local wp:TXY = EachIn e.waypoints
					WriteLine file, wp.x + "," + wp.y
				Next
				
				' Script
				WriteLine file, e.script.Count()
				For Local sc:TScriptItem = EachIn e.script
					WriteLine file, sc.t + "," + sc.time
				Next
			Next
		Next 

		' Objects
		WriteLine file, gs.entitiesObjects.Count()
		For Local e:TGameScenery = EachIn gs.entitiesObjects
			Local s:String = e.name + "," + e.t + "," + e.index + "," + e.objectType + "," + e.size + "," + e.x + "," + e.y + "," + e.angle
			WriteLine file, s
		Next 
		
		' Close file
		CloseStream file

		?debug
   			TProfiler.Leave("GameSave::SaveMission")
  		?
	End Function
	
	Function LoadMission:TGameState(f:String, gd:TGameData, reset:Int = 1)
		?debug
   			TProfiler.Enter("GameSave::LoadMission")
  		?

		Local ms:Int = MilliSecs()

		' Open file
		Local file:TStream = ReadFile("Missions/" + f + ".mis")
		If Not file RuntimeError "Failed to load " + f

		' Import fleet
		Local sa:String[] = (String(ReadLine(file))).split(",")
		Local gs:TGameState = TGameState.Create()

		' Fleets
		gs.fleets[0] = TFleet.FindFleet(gd.fleets, sa[0])
		If gs.fleets[0] = Null Then Return Null
		gs.fleets[1] = TFleet.FindFleet(gd.fleets, sa[1])
		If gs.fleets[0] = Null Then Return Null
		gs.p1PointsLimit = Int(ReadLine(file)) 
		gs.victoryCondition = Int(ReadLine(file))
		gs.victoryHoldOut = Int(ReadLine(file))
		gs.victoryX = Double(ReadLine(file))
		gs.victoryY = Double(ReadLine(file))
		Local vpc:Int = Int(ReadLine(file))
		For Local i:Int = 0 To vpc - 1
			sa = (String(ReadLine(file))).split(",")
			Local xy:TXY = TXY.Create(Double(sa[0]), Double(sa[1]))
			ListAddLast(gs.victoryPointList, xy)
		Next
		vpc = Int(ReadLine(file))
		Local vel:TList = CreateList()
		For Local i:Int = 0 To vpc - 1
			sa = (String(ReadLine(file))).split(",")
			ListAddLast(vel, TInt.Create(Int(sa[0])))
		Next

		' Map
		gs.worldSizeX = Double(ReadLine(file))
		gs.worldSizeY = Double(ReadLine(file))
		gs.mapSectionSize = Double(ReadLine(file))
		
		' Import entities
		Local c:Int = Int(ReadLine(file))
		Local maxID:Int = 0
		For Local i:Int = 0 To c - 1
			sa = (String(ReadLine(file))).split(",")
			Local playerNo:Int = Int(sa[1])
			Local id:Int = Int(sa[2])
			Local v:TVessel
			v = gs.fleets[playerNo].FindVessel(sa[6])
			If v = Null Then 
				i :+ 1
				Continue
			End If
			Local x:Double = Double(sa[3])
			Local y:Double = Double(sa[4])
			Local a:Double = Double(sa[5])
			Local ar:Double = Double(sa[7])
			Local sr:Double = Double(sa[8])
			If id > maxID Then maxID = id
			Local e:TGameEntity = TGameEntity.Create(gs, id, gd.pieces, playerNo, v, x, y, gd.weapons, ms)
			e.name = sa[0]
			e.angle = a
			e.targetAngle = a
			If reset = 1 Then
				e.armourremaining = e.armour
				e.shieldremaining = e.shield
			Else
				e.armourremaining = ar
				e.shieldremaining = sr
			End If
			e.computerControlled = Int(sa[9])
			e.ai.personality = Int(sa[10])
			e.ai.ignoreStartingWaypoint = Int(sa[11])
			e.ai.escortID = Int(sa[12])

			' Waypoints
			Local wp:Int = Int(ReadLine(file))
			For Local j:Int = 0 To wp - 1
				sa = (String(ReadLine(file))).split(",")
				ListAddLast(e.waypoints, TXY.Create(Double(sa[0]), Double(sa[1])))
			Next
			
			' Script
			wp = Int(ReadLine(file))
			For Local j:Int = 0 To wp - 1
				sa = (String(ReadLine(file))).split(",")
				ListAddLast(e.script, TScriptItem.Create(Int(sa[0]), Int(sa[1])))
			Next

			ListAddLast(gs.entities[e.owningPlayerNo], e)
		Next
		
		' Match up AI escorts etc
		For Local player:Int = 0 To 1
			For Local e:TGameEntity = EachIn gs.entities[player]
				If e.ai.escortID > -1 Then
					For Local e2:TGameEntity = EachIn gs.entities[player]
						If e2.index = e.ai.escortID Then 
							e.ai.escort = e2
							Exit
						End If
					Next
				End If
			Next
		Next

		' If mission is protect, get entities
		For Local i:TInt = EachIn vel
			For Local ge:TGameEntity = EachIn gs.entities[0]
				If ge.index = i.i Then ListAddFirst(gs.victoryEntityList, ge)
			Next
		Next
		
		' Import objects
		c = Int(ReadLine(file))
		For Local i:Int = 0 To c - 1
			sa = (String(ReadLine(file))).split(",")
			Local name:String = sa[0]
			Local t:Int = Int(sa[1])
			Local id:Int = Int(sa[2])
			If id > maxID Then maxID = id
			Local objectType:Int = Int(sa[3])
			Local size:Double = Double(sa[4])
			Local x:Double = Double(sa[5])
			Local y:Double = Double(sa[6])
			Local angle:Double = Double(sa[7])
			Local e:TGameScenery = TGameScenery.Create(name, t, id, objectType, size, x, y, angle)
			ListAddLast(gs.entitiesObjects, e)
		Next 
		gs.entityID = maxID + 1
		
		' Work out some stuff
		TGameEntity.CalcPoints(gd, gs)

		' Close file
		CloseStream file

		?debug
   			TProfiler.Leave("GameSave::LoadMission")
  		?

		Return gs
	End Function
	
End Type

