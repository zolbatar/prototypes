SuperStrict
Import "AsteroidSelector.bmx"
Import "Game.bmx"
Import "GameData.bmx"
Import "GameEntity.bmx"
Import "GameRender.bmx"
Import "GameSave.bmx"
Import "GameState.bmx"
Import "GameScenery.bmx"
Import "PlanetSelector.bmx"
Import "Profiler.bmx"
Import "Radar.bmx"
Import "UIFullScreenButtonBar.bmx"
Import "UIInputBox.bmx"
Import "UIListButtonText.bmx"
Import "UISelector.bmx"

Type TMissionBuilder
	Field gd:TGameData, g:TGameState, selectedVessel:TGameEntity = Null, selectedObject:TGameScenery = Null, radar:TRadar
	Field scrolling:Int = 0, prevX:Int, prevY:Int, origX:Int = 0, origY:Int = 0, previousScroll:Int = 0, changes:Int = 0, filename:String
	Field originalCentreX:Double, originalCentreY:Double
	Field addVesselNo:Int = 0, addVesselID:Int = 0, addPlanetNo:Int = 0, addPlanetSize:Double = 0.0, addPlanetName:String = "", renameMode:Int = 0
	Field addAsteroidNo:Int = 0, addAsteroidSize:Double = 0.0, savedMissionType:Int = 0, savedMissionLength:Long = 0, savedScript:Int
	Field selector:TPlanetSelector, asteroidSelector:TAsteroidSelector, vesselSelector:TUISelector, renameUI:TUIInputBox, personality:TUIListButtonText
	
	Method Start(gfx:TGFX, gd:TGameData)
		?debug
   			TProfiler.Enter("MissionBuilder::Start")
  		?
		Self.gd = gd
		radar = TRadar.Create(g, gd.fleetColours)
		
		' Loop
		g.cinematicMode = 0
		gd.sf.p = MilliSecs()
		FlushKeys()
		FlushMouse()
		Local time:Long = 0
		Local ms:Long = MilliSecs()
		PaintTargets()
		Repeat
			Local m:Long = MilliSecs()
			If KeyHit(KEY_ESCAPE) Then
				g.addPlanetMode = 0
				g.addVesselMode = 0
				g.moveItemMode = 0
				g.addWaypointStep = 0
				g.addEscortStep = 0
				g.addAsteroidMode = 0
				g.addScriptStep = 0
				g.setVictoryConditionStep = 0
				g.addProtectVesselStep = 0
				selectedVessel = Null
				selectedObject = Null
			End If

			Local click:String = ""
			If g.addPlanetMode = 0 And g.addVesselMode = 0 And g.moveItemMode = 0 And g.chooseAIStep = 0 And g.addWaypointStep = 0 And g.addAsteroidMode = 0 And g.addScriptStep = 0 And g.setVictoryConditionStep = 0 Then
				click = gd.buttons.Clicked()
				If KeyHit(KEY_P) Or click = "PlayMission" Then
					TGame.CreateWithGameState(gfx, gd, g)
					Return
				ElseIf KeyHit(KEY_L) Or click = "LoadMission" Then 
					ReloadMission(gfx)
				ElseIf KeyHit(KEY_S) Or click = "SaveMission" Then 
					SaveMission(gfx)
				ElseIf KeyHit(KEY_C) And selectedVessel <> Null Then
					g.centreX = selectedVessel.x
					g.centreY = selectedVessel.y
					originalCentreX = g.centreX
					originalCentreY = g.centreY
					origX = 0
			  		origY = 0
				ElseIf KeyHit(KEY_C) And selectedObject <> Null Then
					g.centreX = selectedObject.x
					g.centreY = selectedObject.y
					originalCentreX = g.centreX
					originalCentreY = g.centreY
					origX = 0
			  		origY = 0
				ElseIf KeyHit(KEY_N) Or click = "AddPlanet" Then 
					selector = TPlanetSelector.Create(gd.planets, 550, "Add Planet")
					g.addPlanetMode = 1
				ElseIf KeyHit(KEY_T) Or click = "AddAsteroid" Then 
					asteroidSelector = TAsteroidSelector.Create(gd.asteroids, 550, "Add Asteroid")
					g.addAsteroidMode = 1
				ElseIf KeyHit(KEY_1) Then
					g.addAsteroidMode = 2
					addAsteroidSize = 500.0	
					addAsteroidNo = Rand(0, 8)
				ElseIf KeyHit(KEY_2) Then
					g.addAsteroidMode = 2
					addAsteroidSize = 1000.0	
					addAsteroidNo = Rand(0, 8)
				ElseIf KeyHit(KEY_3) Then
					g.addAsteroidMode = 2
					addAsteroidSize = 5000.0	
					addAsteroidNo = Rand(0, 8)
				ElseIf KeyHit(KEY_4) Then
					g.addAsteroidMode = 2
					addAsteroidSize = 250 + (Rand(0, 4500) * Rnd())
					addAsteroidNo = Rand(0, 8)
				ElseIf KeyHit(KEY_0) Then
					If selectedObject <> Null Then selectedObject.angle = Rand(0, 359)
					If selectedVessel <> Null Then selectedVessel.angle = Rand(0, 359)
				ElseIf KeyHit(KEY_D) Or click = "RemoveItem" Then 
					RemoveItem()
				ElseIf KeyHit(KEY_M) Or click = "MoveItem" Then
					If selectedVessel <> Null Or selectedObject <> Null Then g.moveItemMode = 1
				ElseIf KeyDown(KEY_LSHIFT) Or KeyDown(KEY_RSHIFT) And KeyHit(KEY_A) Or click = "AddVessel2" Then 
					Local s:TList = CreateList()
					For Local v:TVessel = EachIn g.fleets[1].vessels
						ListAddLast(s, v.name)
					Next
					vesselSelector = TUISelector.Create(s, 350, "Add Foe", "Vessel", 0, 0)
					g.addVesselMode = 1
					addVesselNo = 1
					FlushKeys()
				ElseIf KeyHit(KEY_A) Or click = "AddVessel1" Then 
					Local s:TList = CreateList()
					For Local v:TVessel = EachIn g.fleets[0].vessels
						ListAddLast(s, v.name)
					Next
					vesselSelector = TUISelector.Create(s, 350, "Add Friendly", "Vessel", 0, 0)
					g.addVesselMode = 1
					addVesselNo = 0
					FlushKeys()
				ElseIf click = "Rename" Then 
					FlushKeys()
					If selectedVessel <> Null Then
						renameUI = TUIInputBox.Create("Enter the vessel name:", selectedVessel.name, 360, "Rename Vessel", 30)
						renameMode = 1
					ElseIf selectedObject <> Null Then
						renameUI = TUIInputBox.Create("Enter the object name:", selectedObject.name, 360, "Rename Object", 30)
						renameMode = 1
					End If
				ElseIf click = "ShowRadar" Then
					g.showRadar = 1
				ElseIf click = "HideRadar" Then
					g.showRadar = 0
				ElseIf KeyHit(KEY_COMMA) Then 
					RotateLeft()
					changes = 1
				ElseIf KeyHit(KEY_PERIOD) Then 
					RotateRight()
					changes = 1
				ElseIf click = "ComputerControlledOn" And selectedVessel <> Null Then 
					selectedVessel.computerControlled = 1
					selectedVessel.ai.personality = 0
					selectedVessel.waypoints = CreateList()
					changes = 1
				ElseIf click = "ComputerControlledOff" And selectedVessel <> Null Then 
					selectedVessel.computerControlled = 0
					selectedVessel.ai.personality = 0
					selectedVessel.waypoints = CreateList()
					changes = 1
				ElseIf click = "ClearWaypoints" And selectedVessel <> Null Then
					selectedVessel.waypoints = CreateList()
					changes = 1
				ElseIf click = "ClearEscort" And selectedVessel <> Null Then
					selectedVessel.ai.escortID = -1
					changes = 1
				ElseIf click = "SetEscort" And selectedVessel <> Null Then
					g.addEscortStep = 1
				ElseIf click = "AddWaypoint" And selectedVessel <> Null Then
					g.addWaypointStep = 1
				ElseIf click = "IncludeStartingWaypoint" And selectedVessel <> Null Then
					selectedVessel.ai.ignoreStartingWaypoint = 0
				ElseIf click = "IgnoreStartingWaypoint" And selectedVessel <> Null Then
					selectedVessel.ai.ignoreStartingWaypoint = 1
				ElseIf click = "SetAIPersonality" And selectedVessel <> Null Then
					Local s:String[TAI.PersonalityTypes], d:String[TAI.PersonalityTypes]
					For Local i:Int = 0 To TAI.PersonalityTypes - 1
						s[i] = TAI.ReturnAIProfileName(i)
						d[i] = TAI.ReturnAIProfileDescription(i)
					Next	
					personality = TUIListButtonText.Create(s, d, TAI.PersonalityTypes, 700, "Select AI Personality")
					g.chooseAIStep = 1
				ElseIf click = "ClearScript" Then 
					selectedVessel.script = CreateList()
					changes = 1
				ElseIf click = "ClearLastScriptAction" And selectedVessel.script.Count() > 0 Then
					selectedVessel.script.RemoveLast()
					changes = 1
				ElseIf click = "AddScriptedAction" And selectedVessel <> Null Then
					Local s:String[TScriptItem.ScriptTypes], d:String[TScriptItem.ScriptTypes]
					For Local i:Int = 0 To TScriptItem.ScriptTypes - 1
						s[i] = TScriptItem.ReturnScriptName(i)
						d[i] = TScriptItem.ReturnScriptDescription(i)
					Next	
					personality = TUIListButtonText.Create(s, d, TScriptItem.ScriptTypes, 700, "Add Script Item")
					g.addScriptStep = 1
				ElseIf click = "SetVictoryCondition" Then
					Local s:String[TVictoryConditions.VictoryTypes], d:String[TVictoryConditions.VictoryTypes]
					For Local i:Int = 0 To TVictoryConditions.VictoryTypes - 1
						s[i] = TVictoryConditions.ReturnVictoryName(i)
						d[i] = TVictoryConditions.ReturnVictoryDescription:String(i)
					Next	
					personality = TUIListButtonText.Create(s, d, TVictoryConditions.VictoryTypes, 700, "Set Victory Condition")
					g.setVictoryConditionStep = 1
				ElseIf click = "ClearProtectVessels" Then
					g.victoryEntityList = CreateList()
					changes = 1
				ElseIf click = "SetHoldPosition" Then
					savedMissionType = g.victoryCondition 
					savedMissionLength = g.victoryHoldOut 
					g.setVictoryConditionStep = 3
				ElseIf click = "AddProtectVessel" Then
					g.addProtectVesselStep = 1
				ElseIf click = "PointMatch" Then
					g.p1PointsLimit = g.p1Points
					changes = 1
				ElseIf click = "PointDown" And g.p1PointsLimit > 0 Then
					g.p1PointsLimit :- 500
					changes = 1
				ElseIf click = "PointUp" Then
					g.p1PointsLimit :+ 500
					changes = 1
				End If
			End If

			' Mouse click or move?
			If g.addPlanetMode = 1 Or g.addVesselMode = 1 Or g.addAsteroidMode = 1 Or g.chooseAIStep = 1 Or g.addScriptStep = 1 Or g.addScriptStep = 2 Or g.setVictoryConditionStep = 1 Or g.setVictoryConditionStep = 2 Then
			Else
				If KeyHit(KEY_R) Or click = "ResetMapView" Then
					g.ResetScale()
					origX = 0
		 	 		origY = 0
					g.centreX = 0.0
					g.centreY = 0.0
					originalCentreX = g.centreX
					originalCentreY = g.centreY
				ElseIf KeyHit(KEY_EQUALS) Or MouseZ() > previousScroll Then
					g.ZoomIn()
					originalCentreX = g.centreX
					originalCentreY = g.centreY
					origX = 0
	 		 		origY = 0
				ElseIf KeyHit(KEY_MINUS) Or MouseZ() < previousScroll Then
					g.ZoomOut()
					originalCentreX = g.centreX
					originalCentreY = g.centreY
					origX = 0
			  		origY = 0
				End If				
				
				' Select on map?
				If MouseHit(1) Then 
					If gd.buttons.CheckClick(MouseX(), MouseY()) = 0 Then
						SelectEntity(gd, gfx, ms)
					End If
				End If
				
				' Scroll?
				If MouseDown(2) Then
					ScrollAction(gfx)
				Else
					scrolling = 0
					originalCentreX = g.centreX
					originalCentreY = g.centreY
					origX = 0
			  		origY = 0
				End If
			End If
			previousScroll = MouseZ()
			
			' Set scroll position
			g.centreX = originalCentreX + (origX * g.mapSectionSize * (g.scale / g.strategicScale) / g.size)
			g.centreY = originalCentreY - (origY * g.mapSectionSize * (g.scale / g.strategicScale) / g.size)

			' Points			
			g.p1PointsLimit = (g.p1PointsLimit / 500) * 500
			g.p1PointsLimit = (g.p1PointsLimit / 500) * 500
			If g.p1PointsLimit < g.p1Points Then g.p1PointsLimit = g.p1Points

			' Render
			BuildButtons(gfx)
			If g.addPlanetMode = 0 And g.addVesselMode = 0 And g.moveItemMode = 0 And g.chooseAIStep = 0 And g.addAsteroidMode = 0 And g.addScriptStep = 0 And g.setVictoryConditionStep = 0 Then
				TGameRender.Render(gfx, gd, g, selectedVessel, HoverEntity(gd, gfx), HoverEntityObj(gd, gfx), selectedObject, 1, radar, ms) 
			Else
				TGameRender.Render(gfx, gd, g, selectedVessel, Null, Null, selectedObject, 1, radar, ms) 
			End If
			UIToolbar(gfx)
			If g.addPlanetMode = 1 Then
				AddPlanet(gfx, gd)
			ElseIf g.addAsteroidMode = 1 Then
				AddAsteroid(gfx, gd)
			ElseIf g.addVesselMode = 1 Then
				AddVessel(gfx, gd)
			ElseIf renameMode = 1 Then
				Rename(gfx)
			ElseIf g.chooseAIStep = 1 Then
				AIPersonality(gd, gfx)
			ElseIf g.addScriptStep = 1 Then
				AddScript(gd, gfx)
			ElseIf g.addScriptStep = 2 Then
				AddScriptTime(gd, gfx)			
			ElseIf g.setVictoryConditionStep = 1 Then
				SetVictory(gd, gfx)
			ElseIf g.setVictoryConditionStep = 2 Then
				SetVictoryLength(gfx)
			End If
			gd.buttons.Render(gfx)
			
			' Tot up points
			TGameEntity.CalcPoints(gd, g)
			
			' Animate
			time = MilliSecs() - ms
			g.frameTime = MilliSecs() - m
			m = MilliSecs()
			g.calcTime = (MilliSecs() - m)
			Local totalFrameTime:Double = Double(g.calcTime + g.frameTime) / 1000.0
			g.Zoom(totalFrameTime)
			ms = m
			
			' Quit?
			If KeyHit(KEY_Q) And g.addPlanetMode = 0 And g.addVesselMode = 0 And g.moveItemMode = 0 And g.chooseAIStep = 0 And g.addWaypointStep = 0 Then 
				If changes = 0 Then Return
				Local r:Int = TFullScreenButtonBar.CreateSave(gfx, gd.buttons)
				Select r
				Case 0
				Case 1
					SaveMission(gfx)
					?debug
		   				TProfiler.Leave("MissionBuilder::Start")
  					?
					Return
				Case 2
					?debug
   						TProfiler.Leave("MissionBuilder::Start")
			  		?
					Return
				End Select
			Else
				gfx.UIScanlines()
				Flip()
			End If
			PollSystem()			
			gd.sf.Cycle()
		Forever
		?debug
   			TProfiler.Leave("MissionBuilder::Start")
  		?
	End Method
	
	Method HoverEntity:TGameEntity(gd:TGameData, gfx:TGFX)
		?debug
   			TProfiler.Enter("MissionBuilder::HoverEntity")
  		?
		Local tX:Double, tY:Double
		GetPosition(gfx, tX, tY)

		Local dist:Double = 9999999
		Local v:TGameEntity = Null
		For Local player:Int = 0 To 1
			For Local ge:TGameEntity = EachIn g.entities[player]
				If Abs(tX - ge.x) < (gd.SnapSize * g.scale) And Abs(tY - ge.y) < (gd.SnapSize * g.scale) Then
					Local m:Double = Min(Abs(tX - ge.x), Abs(tY - ge.y))
					If m < dist Then
						v = ge
						dist = m
						gfx.pointer = 1
					End If
				End If
			Next
		Next 
		?debug
   			TProfiler.Leave("MissionBuilder::HoverEntity")
  		?
		Return v
	End Method

	Method HoverEntityObj:TGameScenery(gd:TGameData, gfx:TGFX)
		?debug
   			TProfiler.Enter("MissionBuilder::HoverEntityObj")
  		?
		Local tX:Double, tY:Double
		GetPosition(gfx, tX, tY)

		Local dist:Double = 9999999
		Local v:TGameScenery = Null
		For Local ge:TGameScenery = EachIn g.entitiesObjects
			If Abs(tX - ge.x) * 2 < (ge.size / 2.0) And Abs(tY - ge.y) * 2 < (ge.size / 2.0) Then
				Local m:Double = Min(Abs(tX - ge.x), Abs(tY - ge.y))
				If m < dist Then
					v = ge
					dist = m 
				End If
			End If
		Next 
		?debug
   			TProfiler.Leave("MissionBuilder::HoverEntityObj")
  		?
		Return v
	End Method
	
	Method ScrollAction(gfx:TGFX)
		If scrolling = 1 Then
			Local dX:Int = MouseX() - prevX
			Local dY:Int = MouseY() - prevY
			g.CanScroll(gfx, dX, dY, 1)
			origX :- dX
			origY :- dY
			gd.sf.panCycle(dX, dY)
		Else
			scrolling = 1
		End If
		prevX = MouseX()
		prevY = MouseY()
	End Method

	Method Rename(gfx:TGFX)
		Local name:String = renameUI.Render(gfx, gd, 1)
		If name = Null Then Return
		FlushKeys()
		If selectedVessel <> Null Then
			selectedVessel.name = name
		ElseIf selectedObject <> Null Then
			selectedObject.name = name
		End If
		renameMode = 0
		changes = 1
	End Method

	Method AIPersonality(gd:TGameData, gfx:TGFX)
		Local s2:Int = personality.Render(gfx, gd.buttons, gd.sf, 1)
		If s2 = -100 Then Return
		If s2 >= 0 Then 
			selectedVessel.ai.personality = s2
			selectedVessel.waypoints = CreateList()
			selectedVessel.ai.escortID = -1
			changes = 1
		End If
		g.chooseAIStep = 0
	End Method

	Method AddScript(gd:TGameData, gfx:TGFX)
		Local s2:Int = personality.Render(gfx, gd.buttons, gd.sf, 1)
		If s2 = -100 Then Return
		If s2 >= 0 Then 
			savedScript = s2
			renameUI = TUIInputBox.Create("Enter the jump time (in seconds):", "600", 360, "Jump Time", 30)
			g.addScriptStep = 2
			Return
		End If
		g.addScriptStep = 0
	End Method
	
	Method AddScriptTime(gd:TGameData, gfx:TGFX)
		Local name:String = renameUI.Render(gfx, gd, 1)
		If name = Null Then Return
		FlushKeys()
		ListAddLast(selectedVessel.script, TScriptItem.Create(savedScript, Double(name)))
		g.addScriptStep = 0
		changes = 1
	End Method

	Method SetVictory(gd:TGameData, gfx:TGFX)
		Local s2:Int = personality.Render(gfx, gd.buttons, gd.sf, 1)
		If s2 = -100 Then Return
		If s2 >= 0 Then 
			If s2 = TVictoryConditions.VictoryHoldout Then 
				savedMissionType = s2
				g.setVictoryConditionStep = 2 
				renameUI = TUIInputBox.Create("Enter the mission length (in seconds):", "600", 360, "Mission Length", 30)
				Return
			ElseIf s2 = TVictoryConditions.VictoryProtect Then 
				savedMissionType = s2
				g.setVictoryConditionStep = 2 
				renameUI = TUIInputBox.Create("Enter the mission length (in seconds):", "600", 360, "Mission Length", 30)
				Return
			Else
				g.victoryCondition = s2
				changes = 1
			End If
		End If
		g.setVictoryConditionStep = 0
	End Method

	Method SetVictoryLength(gfx:TGFX)
		Local name:String = renameUI.Render(gfx, gd, 1)
		If name = Null Then Return
		FlushKeys()
		savedMissionLength = Double(name)
		If savedMissionType = TVictoryConditions.VictoryProtect Then
			g.victoryCondition = savedMissionType
			g.victoryHoldOut = savedMissionLength
			g.victoryEntityList = CreateList()
			g.setVictoryConditionStep = 0
			changes = 1
		Else
			g.setVictoryConditionStep = 3
		End If
	End Method
	
	Method RotateLeft()
		If selectedVessel <> Null Then 
			selectedVessel.angle :- 5
			If selectedVessel.angle < 0 Then selectedVessel.angle :+ 360
			selectedVessel.targetAngle = selectedVessel.angle
			changes = 1
		ElseIf selectedObject <> Null Then
			selectedObject.angle :- 5
			If selectedObject.angle < 0 Then selectedObject.angle :+ 360
			changes = 1
		End If
	End Method
	
	Method RotateRight()
		If selectedVessel <> Null Then 
			selectedVessel.angle :+ 5
			If selectedVessel.angle > 360 Then selectedVessel.angle :- 360
			selectedVessel.targetAngle = selectedVessel.angle
			changes = 1
		ElseIf selectedObject <> Null Then
			selectedObject.angle :+ 5
			If selectedObject.angle > 360 Then selectedObject.angle :- 360
			changes = 1
		End If
	End Method

	Method RemoveItem()
		If selectedVessel <> Null Then
			ListRemove(g.entities[selectedVessel.owningPlayerNo], selectedVessel)
			selectedVessel = Null
			changes = 1
		End If
		If selectedObject <> Null Then
			ListRemove(g.entitiesObjects, selectedObject)
			selectedObject = Null
			changes = 1
		End If
		PaintTargets()
	End Method

	Method SelectEntity(gd:TGameData, gfx:TGFX, ms:Long)
		?debug
   			TProfiler.Enter("MissionBuilder::SelectEntity")
  		?
		Local tX:Double, tY:Double
		GetPosition(gfx, tX, tY)

		' Add planet
		If g.addPlanetMode = 2 Then
			Local e:TGameScenery = TGameScenery.Create(addPlanetName, TGameScenery.TypePlanet, g.entityID, addPlanetNo, addPlanetSize, tX, tY)
			ListAddLast(g.entitiesObjects, e)
			g.entityID :+ 1
			g.addPlanetMode = 0
			changes = 1
			selectedVessel = Null
			selectedObject = e
			FlushKeys
			?debug
   				TProfiler.Leave("MissionBuilder::SelectEntity")
  			?
			Return
		End If

		' Add asterid
		If g.addAsteroidMode = 2 Then
			Local e:TGameScenery = TGameScenery.Create("", TGameScenery.TypeAsteroid, g.entityID, addAsteroidNo, addAsteroidSize, tX, tY, Rand(0, 359))
			ListAddLast(g.entitiesObjects, e)
			g.entityID :+ 1
			g.addAsteroidMode = 0
			changes = 1
			selectedVessel = Null
			selectedObject = e
			FlushKeys
			?debug
   				TProfiler.Leave("MissionBuilder::SelectEntity")
  			?
			Return
		End If
		
		' Set waypoint
		If g.addWaypointStep = 1 Then
			ListAddLast(selectedvessel.waypoints, TXY.Create(tX, tY))
			g.addWaypointStep = 0
			changes = 1
			?debug
   				TProfiler.Leave("MissionBuilder::SelectEntity")
  			?
			Return
		End If
		
		' Set mission point
		If g.setVictoryConditionStep = 3 Then
			g.victoryX = tX
			g.victoryY = tY
			g.victoryCondition = savedMissionType
			g.victoryHoldOut = savedMissionLength
			g.setVictoryConditionStep = 0
			changes = 1
			FlushMouse()
			?debug
   				TProfiler.Leave("MissionBuilder::SelectEntity")
  			?
			Return
		End If
		
		' Move
		If g.moveItemMode = 1 Then
			If selectedVessel <> Null Then 
				selectedVessel.x = tX
				selectedVessel.y = tY
			ElseIf selectedObject <> Null Then 
				selectedObject.x = tX
				selectedObject.y = tY
			End If
			g.moveItemMode = 0
			changes = 1
			PaintTargets()
			?debug
   				TProfiler.Leave("MissionBuilder::SelectEntity")
  			?
			Return
		End If

		' Add vessel
		If g.addVesselMode = 2 Then
			Local vessel:TVessel = g.fleets[addVesselNo].GetX(addVesselID)
			Local e:TGameEntity = TGameEntity.Create(g, g.entityID, gd.pieces, addVesselNo, vessel, tX, tY, gd.weapons, ms)
			ListAddLast(g.entities[e.owningPlayerNo], e)
			g.entityID :+ 1
			g.addVesselMode = 0
			changes = 1
			selectedObject = Null
			selectedVessel = e
			FlushKeys
			PaintTargets()
			?debug
   				TProfiler.Leave("MissionBuilder::SelectEntity")
  			?
			Return
		End If

		' Selected?
		Local dist:Double = 999999
		Local selectedVesselSaved:TGameEntity = selectedVessel
		For Local ge:TGameScenery = EachIn g.entitiesObjects
			If Abs(tX - ge.x) * 2 < (ge.size / 2.0) And Abs(tY - ge.y) * 2 < (ge.size / 2.0) Then
				Local m:Double = (Min(Abs(tX - ge.x), Abs(tY - ge.y))) * 8
				If m < dist Then
					selectedVessel = Null
					selectedObject = ge
					dist = m 
				End If
			End If
		Next 
		For Local player:Int = 0 To 1
			For Local ge:TGameEntity = EachIn g.entities[player]
				If Abs(tX - ge.x) < (gd.SnapSize * g.scale) And Abs(tY - ge.y) < (gd.SnapSize * g.scale) Then
					Local m:Double = Min(Abs(tX - ge.x), Abs(tY - ge.y))
					If m < dist Then
						selectedVessel = ge
						selectedObject = Null
						dist = m
					End If
				End If
			Next
		Next 

		' Mission protect
		If g.addProtectVesselStep = 1 And selectedVessel <> Null Then
			If selectedVessel.owningPlayerNo = 0 Then
				ListAddLast(g.victoryEntityList, selectedVessel)
				changes = 1
				selectedVessel = selectedVesselSaved
				?debug
   					TProfiler.Leave("MissionBuilder::SelectEntity")
  				?
				g.addProtectVesselStep = 0
				Return
			Else
				selectedVessel = selectedVesselSaved
				?debug
   					TProfiler.Leave("MissionBuilder::SelectEntity")
  				?
				Return
			End If
		End If
		
		' Set escort
		If g.addEscortStep = 1 And selectedVessel <> Null Then
			If selectedVessel.owningPlayerNo = selectedVesselSaved.owningPlayerNo Then
				selectedVesselSaved.ai.escort = selectedVessel
				selectedVesselSaved.ai.escortID = selectedVessel.index
				g.addEscortStep = 0
				changes = 1
				selectedVessel = selectedVesselSaved
				?debug
   					TProfiler.Leave("MissionBuilder::SelectEntity")
  				?
				Return
			Else
				selectedVessel = selectedVesselSaved
				?debug
   					TProfiler.Leave("MissionBuilder::SelectEntity")
  				?
				Return
			End If
		End If
		
		?debug
   			TProfiler.Leave("MissionBuilder::SelectEntity")
  		?
	End Method
	
	Method GetPosition(gfx:TGFX, tX:Double Var, tY:Double Var)
		?debug
   			TProfiler.Enter("MissionBuilder::GetPosition")
  		?
		tX = (MouseX() - g.mapViewCentreX) * g.scale
		tY = (g.mapViewCentreY - MouseY()) * g.scale
		tX :+ g.centreX
		tY :+ g.centreY		
		?debug
   			TProfiler.Leave("MissionBuilder::GetPosition")
  		?
	End Method
	
	Method AddVessel(gfx:TGFX, gd:TGameData)
		Local f:Int = vesselSelector.Render(gfx, gd.buttons, gd.sf, 1)
		If f = - 100 Then
		ElseIf f = -1 Then 
			g.addVesselMode = 0
			Return
		Else
			g.addVesselMode = 2
			addVesselID = f
		End If
	End Method

	Method AddPlanet(gfx:TGFX, gd:TGameData)
		Local f:Int = selector.Render(gfx, 0.125, 3, 3, gd.buttons, gd.sf, 1)
		If f = - 100 Then
		ElseIf f = -1 Then 
			g.addPlanetMode = 0
			Return
		Else
			g.addPlanetMode = 2
			addPlanetName = selector.s
			Select selector.sizePlanet
			Case 0
				addPlanetSize = 25000.0
			Case 1
				addPlanetSize = 100000.0
			Case 2
				addPlanetSize = 250000.0
			End Select
			addPlanetNo = f
		End If
	End Method	

	Method AddAsteroid(gfx:TGFX, gd:TGameData)
		Local f:Int = asteroidSelector.Render(gfx, 0.25, 3, 3, gd.buttons, gd.sf, 1)
		If f = - 100 Then
		ElseIf f = -1 Then 
			g.addAsteroidMode = 0
			Return
		Else
			g.addAsteroidMode = 2
			Select asteroidSelector.sizeAsteroid
			Case 0
				addAsteroidSize = 500.0
			Case 1
				addAsteroidSize = 1000.0
			Case 2
				addAsteroidSize = 5000.0
			End Select
			addAsteroidNo = f
		End If
	End Method	
		
	Method Setup(gfx:TGFX)
		?debug
   			TProfiler.Enter("MissionBuilder::Setup")
  		?
		TGameRender.SetupMapView(gfx, gd, g, 1)
		g.fleets[0].RenderAllVessels(gd.pieces, gfx)
		g.fleets[1].RenderAllVessels(gd.pieces, gfx)
		?debug
   			TProfiler.Leave("MissionBuilder::Setup")
  		?
	End Method

	Method UIToolbar(gfx:TGFX)
		SetColor(0, 0, 64)
		SetAlpha(0.5)
		DrawRect(0, 0, gfx.width, TGameData.ToolbarHeight)
		SetColor(255, 255, 255)
		SetAlpha(1.0)
	End Method

	Method BuildButtons(gfx:TGFX)
		gd.buttons.ClearButtons()
		gd.buttons.AddButtonBordered("Reset", "View", 3, 10, 5, 100, "ResetMapView")
		gd.buttons.AddButtonBordered("Add", "Friendly", 1, 120, 5, 100, "AddVessel1")
		gd.buttons.AddButtonBordered("Add", "Foe", 1, 220, 5, 100, "AddVessel2")
		gd.buttons.AddButtonBordered("Add", "Planet", 1, 320, 5, 100, "AddPlanet")
		gd.buttons.AddButtonBordered("Add", "Asteroid", 1, 420, 5, 100, "AddAsteroid")
		gd.buttons.AddButtonBordered("Move", "Item", 2, 520, 5, 100, "MoveItem", selectedVessel = Null And selectedObject = Null)
		gd.buttons.AddButtonBordered("Remove", "Item", 2, 620, 5, 100, "RemoveItem", selectedVessel = Null And selectedObject = Null)
		gd.buttons.AddButtonBordered("Rename", "Item", 5, 720, 5, 100, "Rename", selectedVessel = Null And selectedObject = Null)
		gd.buttons.AddButtonBordered("Reload", "Mission", 5, 830, 5, 100, "LoadMission")
		gd.buttons.AddButtonBordered("Save", "Mission", 5, 930, 5, 100, "SaveMission")
		gd.buttons.AddButtonBordered("Play", "Mission", 4, 1030, 5, 100, "PlayMission")
		If g.ShowRadar = 1 Then
			gd.buttons.AddButtonBordered("Hide", "Radar", 6, 1140, 5, 100, "HideRadar")
		Else
			gd.buttons.AddButtonBordered("Show", "Radar", 6, 1140, 5, 100, "ShowRadar")
		End If
	End Method

	Method SaveMission(gfx:TGFX)
		Local f:String = filename
		If f = "" Then
			Local t:TUIInputBox = TUIInputBox.Create("Enter the mission name:", "", 360, "Mission Name", 20)
			filename = t.Render(gfx, Null, 0)
		End If
		If filename = "" Then
			filename = f
			Return
		End If
		
		TGameSave.SaveMission(filename, g)
		changes = 0
	End Method
	
	Method ReloadMission(gfx:TGFX)
		g = TGameSave.LoadMission(filename, gd)
		Setup(gfx)
		changes = 0
	End Method
		
	Method PaintTargets()
		?debug
   			TProfiler.Enter("MissionBuilder::PaintTargets")
  		?
		radar.Clear()
		radar.CalcRadar()
		radar.SetVisible(1)
		?debug
   			TProfiler.Leave("MissionBuilder::PaintTargets")
  		?
	End Method

End Type
