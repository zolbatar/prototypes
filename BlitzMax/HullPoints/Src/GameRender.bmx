SuperStrict
Import "CatmullRomSplines.bmx"
Import "GameData.bmx"
Import "GameEntity.bmx"
Import "GameInfoOverlay.bmx"
Import "GameScenery.bmx"
Import "GameState.bmx"
Import "Profiler.bmx"
Import "Radar.bmx"
Import "GFX.bmx"
Import "XYEntity.bmx"
Include "Minimap.bmx"

Type TGameRender

	Function Render(gfx:TGFX, gd:TGameData, g:TGameState, selectedVessel:TGameEntity, hoveringVessel:TGameEntity, hoveringObject:TGameScenery, selectedObject:TGameScenery, missionBuilder:Int, radar:TRadar, ms:Long)
		?debug
   			TProfiler.Enter("GameRender::Render")
  		?
		Local s:Double = g.strategicScale / g.scale
		Local z:Double = ((s / 128) - (1.0 / 128.0)) + 1.0
		If missionBuilder = 1 Then 
			gd.sf.Render(z) 
		Else 
			If g.showStars Then 
				gd.sf.Render(z) 
			Else 
				SetClsColor(0, 0, 32)
				Cls
			End If
		End If
		If missionBuilder = 1 Or g.cinematicMode = 0 Then MapView(gfx, g, s)
		
		' Translate		
		TranslateEntities(g)
		
		' Render
		SetOrigin(g.mapViewCentreX, g.mapViewCentreY)
		RenderObjects(gd, g, gfx, g.entitiesObjects, hoveringObject, selectedObject, s, missionBuilder)
		If g.showRadar = 1 And (g.cinematicMode = 0 Or missionBuilder = 1) And g.scale >= 20.0 Then VesselRadar(gfx, g, missionBuilder, gd.fleetColours, radar)
		RenderDeadEntities(gfx, gd, g, g.entitiesDead, 1, Null, Null, missionBuilder, s, ms)
		RenderJumpPoints(gfx, gd, g, ms)
		RenderEntities(gfx, gd, g, g.entities[1], 0, selectedVessel, hoveringVessel, missionBuilder, s, ms)
		RenderEntities(gfx, gd, g, g.entities[0], 0, selectedVessel, hoveringVessel, missionBuilder, s, ms)
		RenderDeadProjectiles(gd, g, gfx, g.entitiesProjectilesDead, 0.2, s, g.worldSizeX / 60000, ms)
		RenderEntities(gfx, gd, g, g.entitiesProjectiles[1], 1, Null, Null, missionBuilder, s, ms)
		RenderEntities(gfx, gd, g, g.entitiesProjectiles[0], 1, Null, Null, missionBuilder, s, ms)
		If g.victoryCondition = TVictoryConditions.VictoryHoldout And g.cinematicMode = 0 Then 
			Local tX:Double, tY:Double
			g.TranslateXY(g.victoryX, g.victoryY, tX, tY)

			' Blue
			Local sz:Double = 10000 / g.scale
			SetAlpha(0.25)
			SetColor(0, 0, 128)
			DrawOval(tX - (sz / 2), tY - (sz / 2), sz, sz)

			' Target
			SetColor(255, 255, 255)
			SetRotation(gd.sf.r * 100.0)
			SetScale(10000 / g.scale / 512, 10000 / g.scale / 512)
			DrawImage(gd.spinner2, tX, tY)
			SetScale(1.0, 1.0)
			SetRotation(0)
			SetAlpha(1.0)
		End If
		SetViewport(0, 0, gfx.width, gfx.height)
		SetOrigin(0, 0)

		' Sidebar
		If selectedVessel <> Null Then
			If missionBuilder = 1 Then
				SetColor(0, 0, 0)
				SetAlpha(0.25)
				DrawRect(0, gd.ToolbarHeight, gd.OverlayWidth, gfx.height - gd.ToolbarHeight)
				SetViewport(0, gd.ToolbarHeight, gd.OverlayWidth - 5, gfx.height - gd.ToolbarHeight)
			Else
				SetColor(0, 0, 0)
				SetAlpha(0.25)
				DrawRect(0, 0, gd.OverlayWidth, gfx.height)
				SetViewport(0, 0, gd.OverlayWidth - 5, gfx.height)
			End If
		End If
		SetColor(255, 255, 255)
		SetAlpha(1.0)
		
		' Data
		Local top:Int = 0
		If missionBuilder = 1 Then top :+ gd.ToolbarHeight
		TGameInfoOverlay.UIOverlay(gfx, gd, g, selectedVessel, missionBuilder, top)
		SetViewport(0, 0, gfx.width, gfx.height)

		' Minimap		
		If missionBuilder = 0 Then
			TMiniMap.MiniMap(gfx, gd, g)
			TMiniMap.MiniMapData(gfx, gd, g)
		End If
		
		'Stats
		If g.showStats = 1 And missionBuilder = 0 Then
			SetColor(255, 255, 255)
			gfx.SetFontSize(TGFX.FontMediumSmall)
			Local h:Int = gfx.GetCachedFontHeight("Text")
			DrawText("Entities: = " + String(g.entities[0].Count() + g.entities[1].Count() + g.entitiesProjectiles[0].Count() + g.entitiesProjectiles[1].Count()), 10, gfx.height - 80 - h)
			DrawText("Render Time: = " + String(g.frameTime) + " ms", 10, gfx.height - 80 - h - h)
			DrawText("Calc Time: = " + String(g.calcTime) + " ms", 10, gfx.height - 80 - h - h - h)
		End If
		
		' Mission stats
		If missionBuilder = 1 And g.setVictoryConditionStep = 0 And g.addEscortStep = 0 And g.addWaypointStep = 0 And g.addVesselMode = 0 And g.addAsteroidMode = 0 And g.addPlanetMode = 0 And g.addProtectVesselStep = 0 Then
			gfx.SetFontSize(TGFX.FontLarge)
			Local h:Int = gfx.GetCachedFontHeight("Text")

			' Background
			SetColor(0, 0, 0)
			SetAlpha(0.25)
			DrawRect(gd.OverlayWidth, gfx.height - 15 - h - h - h, gfx.width - gd.OverlayWidth, 15 + h + h + h)

			' Elements			
			SetAlpha(1.0)
			SetColor(220, 220, 220)
			Local w:Int = gfx.GetCachedFontWidth("Player 1:")
			SetPlayerColour(0, gd.fleetColours)
			DrawText("Player 1:", 10, gfx.height - 10 - h - h - h)
			SetPlayerColour(1, gd.fleetColours)
			DrawText("Player 2:", 10, gfx.height - 10 - h - h)
			SetColor(0, 255, 0)
			Local s:String = g.p1points + " points (allowed " + g.p1pointslimit + " points)"
			DrawText(s, 20 + w, gfx.height - 10 - h - h - h)
			Local sw:Int = gfx.GetCachedFontWidth(s)
			DrawText(g.p2points + " points", 20 + w, gfx.height - 10 - h - h)
			gd.buttons.AddButtonMS("-500", 2, 20 + sw + w + 5, gfx.height - 15 - h - h - h, 50, "PointDown", g.p1PointsLimit <= g.p1Points)
			gd.buttons.AddButtonMS("Match", 4, 20 + sw + w + 50, gfx.height - 15 - h - h - h, 50, "PointMatch", g.p1PointsLimit = g.p1Points)
			gd.buttons.AddButtonMS("+500", 1, 20 + sw + w + 95, gfx.height - 15 - h - h - h, 50, "PointUp")
			SetColor(200, 200, 200)
			s = "Victory Condition: "
			sw = gfx.GetCachedFontWidth(s)
			DrawText(s, 10, gfx.height - 10 - h)
			gfx.SetFontSize(TGFX.FontLarge)
			s = TVictoryConditions.ReturnVictoryName(g.victoryCondition)
			If g.victoryCondition = TVictoryConditions.VictoryHoldout Then
				s :+ " For " + g.victoryHoldOut + " seconds"
			ElseIf g.victoryCondition = TVictoryConditions.VictoryProtect Then 
				s :+ " For " + g.victoryHoldOut + " seconds."
			End If
			SetColor(0, 255, 0)
			DrawText(s, 10 + sw, gfx.height - 10 - h)
			gd.buttons.AddButtonMS("Set Victory Condition", 5, 10 + gfx.GetCachedFontWidth(s) + 5 + sw, gfx.height - 15 - h, 150, "SetVictoryCondition")
			If g.victoryCondition = TVictoryConditions.VictoryHoldout Then 
				gd.buttons.AddButtonMS("Set Hold Position", 1, 10 + gfx.GetCachedFontWidth(s) + 5 + sw + 150, gfx.height - 15 - h, 150, "SetHoldPosition")
			ElseIf g.victoryCondition = TVictoryConditions.VictoryProtect Then 
				gd.buttons.AddButtonMS("Add Vessel", 1, 10 + gfx.GetCachedFontWidth(s) + 5 + sw + 150, gfx.height - 15 - h, 150, "AddProtectVessel")
				gd.buttons.AddButtonMS("Clear Vessels", 2, 10 + gfx.GetCachedFontWidth(s) + 5 + sw + 300, gfx.height - 15 - h, 150, "ClearProtectVessels")
			End If
		Else
			Local prop1:Double = Double(g.p1points) / Double(g.p1pointsInitial)
			Local prop1r:Double = Double(g.p1points + g.p1pointsReserve) / Double(g.p1pointsInitial)
			Local prop2:Double = Double(g.p2points) / Double(g.p2pointsInitial)
			Local prop2r:Double = Double(g.p2points + g.p2pointsReserve) / Double(g.p2pointsInitial)
			SetPlayerColour(0, gd.fleetColours)
			SetAlpha(0.4)
			DrawRect(5, gfx.height - 60, 100.0, 15)
			SetAlpha(0.75)
			DrawRect(5, gfx.height - 60, prop1r * 100.0, 15)
			SetAlpha(1.0)
			DrawRect(5, gfx.height - 60, prop1 * 100.0, 15)
			SetPlayerColour(1, gd.fleetColours)
			SetAlpha(0.4)
			DrawRect(5, gfx.height - 40, 100.0, 15)
			SetAlpha(0.75)
			DrawRect(5, gfx.height - 40, prop2r * 100.0, 15)
			SetAlpha(1.0)
			DrawRect(5, gfx.height - 40, prop2 * 100.0, 15)
			Local t:Long
			If g.victoryCondition = TVictoryConditions.VictoryAnnihilation Then
				t = ms / 1000
			Else
				t = g.victoryHoldOut - (ms / 1000)
			End If
			If t < 0 Then t = 0
			Local mn:Long = t / 60
			Local se:Long = t Mod 60
			Local tst:String
			If mn > 0 Then
				tst = mn + " minutes, " + se + " seconds"
			Else
				tst = se + " seconds"
			End If
			gfx.SetFontSize(TGFX.FontLarge)
			Select g.victoryCondition
			Case TVictoryConditions.VictoryAnnihilation
				Local st:String = "Mission Time: "
				SetColor(200, 200, 200)
				DrawText(st, 5, gfx.height - gfx.GetCachedFontHeight(st))
				SetColor(0, 255, 0)
				DrawText(tst, 5 + gfx.GetCachedFontWidth(st), gfx.height - gfx.GetCachedFontHeight(st))
			Case TVictoryConditions.VictoryHoldout
				Local st:String = "Mission Time Remaining: "
				SetColor(200, 200, 200)
				DrawText(st, 5, gfx.height - gfx.GetCachedFontHeight(st))
				SetColor(0, 255, 0)
				DrawText(tst, 5 + gfx.GetCachedFontWidth(st), gfx.height - gfx.GetCachedFontHeight(st))
			Case TVictoryConditions.VictoryProtect
				Local st:String = "Mission Time Remaining: "
				SetColor(200, 200, 200)
				DrawText(st, 5, gfx.height - gfx.GetCachedFontHeight(st))
				SetColor(0, 255, 0)
				Local tst2:String = ", " + g.remaining + " of " + g.victoryEntityList.Count() + " vessel(s) remaining"
				DrawText(tst + tst2, 5 + gfx.GetCachedFontWidth(st), gfx.height - gfx.GetCachedFontHeight(st))
			End Select
		End If

		' Messages & prompts
		If g.showMessages = 1 Then RenderMessages(gfx, gd, g)
		Prompts(gfx, gd, g, selectedVessel)
		?debug
   			TProfiler.Leave("GameRender::Render")
  		?
	End Function
	
	Function RenderJumpPoints(gfx:TGFX, gd:TGameData, g:TGameState, ms:Long)
		?debug
   			TProfiler.Enter("GameRender::RenderJumpPoints")
  		?
		For Local t:TXYEntity = EachIn g.jumpPoints
			Local time:Double = ms - t.t
			If time > 6000 Then
				ListRemove(g.jumpPoints, t)
				Continue
			End If
			Local s2:Double = t.s / g.scale / (g.worldSizeX / 60000)
			If time < 1000 Then
				SetAlpha((time / 1000) * 0.75)
			ElseIf time > 5000 Then
				SetAlpha(((6000 - time) / 1000) * 0.75)
			Else
				SetAlpha(0.75)
			End If 
			Local tX:Double, tY:Double
			g.TranslateXY(t.x, t.y, tX, tY)
			SetColor(255, 255, 255)
			SetScale(s2 / 128, s2 / 128)
			Local frame:Int = ((ms - t.t) / 30) & 15
			DrawImage(gd.warp, tX, tY, frame)
			SetScale(1.0, 1.0)
		Next
		?debug
   			TProfiler.Leave("GameRender::RenderJumpPoints")
  		?
	End Function
	
	Function RenderMessages(gfx:TGFX, gd:TGameData, g:TGameState)
		?debug
   			TProfiler.Enter("GameRender::RenderMessages")
  		?
		Local x:Int = g.messageCount
		If x > 10 Then x = 10
		gfx.SetFontSize(TGFX.FontMediumSmall)
		Local h:Int = gfx.GetCachedFontHeight("Message")
		Local i:Int = 0
		Local t:Int = 10
		SetAlpha(0.75)
		For Local s:TMessage = EachIn g.messages
			SetColor(255, 255, 255)
			DrawText(s.time, gd.OverlayWidth + 10, t + (i * h))
			SetPlayerColour(s.playerNo, gd.fleetColours)
			DrawText(s.s, gd.OverlayWidth + 60, t + (i * h))
			i :+ 1
			If i = x Then 
				?debug
   					TProfiler.Leave("GameRender::RenderMessages")
		  		?
				Return
			End If
		Next
		SetAlpha(1.0)
		?debug
   			TProfiler.Leave("GameRender::RenderMessages")
  		?
	End Function

	Function Prompts(gfx:TGFX, gd:TGameData, g:TGameState, selectedVessel:TGameEntity)
		?debug
   			TProfiler.Enter("GameRender::Prompts")
  		?
		Local v:Float = gfx.height - gd.ToolbarHeight
		SetColor(32, 32, 32)
		If g.addPlanetMode = 2 Then
			DrawRect(0, v, gfx.width, gd.ToolbarHeight + 10)
			SetColor(240, 240, 0)
			gfx.CenteredText(TGFX.FontXLarge, "Click to place planet, or ESC to cancel", gfx.height - 45)
		ElseIf g.addAsteroidMode = 2 Then
			DrawRect(0, v, gfx.width, gd.ToolbarHeight + 10)
			SetColor(240, 240, 0)
			gfx.CenteredText(TGFX.FontXLarge, "Click to place asteroid, or ESC to cancel", gfx.height - 45)
		ElseIf g.addVesselMode = 2 Then
			DrawRect(0, v, gfx.width, gd.ToolbarHeight + 10)
			SetColor(240, 240, 0)
			gfx.CenteredText(TGFX.FontXLarge, "Click to place vessel, or ESC to cancel", gfx.height - 45)
		ElseIf g.moveItemMode = 1 Then
			DrawRect(0, v, gfx.width, gd.ToolbarHeight + 10)
			SetColor(240, 240, 0)
			gfx.CenteredText(TGFX.FontXLarge, "Click to set move point, or ESC to cancel", gfx.height - 45)
		ElseIf g.addWaypointStep = 1 Then
			DrawRect(0, v, gfx.width, gd.ToolbarHeight + 10)
			SetColor(240, 240, 0)
			gfx.CenteredText(TGFX.FontXLarge, "Click to set waypoint, or ESC to cancel", gfx.height - 45)
		ElseIf g.addEscortStep = 1 Then
			DrawRect(0, v, gfx.width, gd.ToolbarHeight + 10)
			SetColor(240, 240, 0)
			gfx.CenteredText(TGFX.FontXLarge, "Click target to set escorted vessel, or ESC to cancel", gfx.height - 45)
		ElseIf g.setVictoryConditionStep = 3 Then
			DrawRect(0, v, gfx.width, gd.ToolbarHeight + 10)
			SetColor(240, 240, 0)
			gfx.CenteredText(TGFX.FontXLarge, "Click to set mission target, or ESC to cancel", gfx.height - 45)
		ElseIf g.addProtectVesselStep = 1 Then
			DrawRect(0, v, gfx.width, gd.ToolbarHeight + 10)
			SetColor(240, 240, 0)
			gfx.CenteredText(TGFX.FontXLarge, "Click vessel that needs protecting for mission victory, or ESC to cancel", gfx.height - 45)
		ElseIf g.pursueOrderStep = 1 And g.pursueIsEscort = 0 Then
			DrawRect(0, v, gfx.width, gd.ToolbarHeight + 10)
			SetColor(240, 240, 0)
			Local w:Int = (gfx.width - (6.5 * 100)) / 2
			gd.buttons.AddButtonBordered("Pursue", "25000m", 0, w, v + 5, 100, "Pursue25000m")
			gd.buttons.AddButtonBordered("Pursue", "10000m", 3, w + 100, v + 5, 100, "Pursue10000m")
			gd.buttons.AddButtonBordered("Pursue", "5000m", 4, w + 200, v + 5, 100, "Pursue5000m")
			gd.buttons.AddButtonBordered("Pursue", "2500m", 5, w + 300, v + 5, 100, "Pursue2500m")
			gd.buttons.AddButtonL("Remove Order", "When Arrived", 2, w + 500, v + 5, 150, "RemoveOrderWhenArrived", g.removeOrderWhenArrived = 0)
		ElseIf g.pursueOrderStep = 1 And g.pursueIsEscort = 1 Then
			DrawRect(0, v, gfx.width, gd.ToolbarHeight + 10)
			SetColor(240, 240, 0)
			Local w:Int = (gfx.width - (4 * 100)) / 2
			gd.buttons.AddButtonBordered("Escort", "25000m", 0, w, v + 5, 100, "Pursue25000m")
			gd.buttons.AddButtonBordered("Escort", "10000m", 3, w + 100, v + 5, 100, "Pursue10000m")
			gd.buttons.AddButtonBordered("Escort", "5000m", 4, w + 200, v + 5, 100, "Pursue5000m")
			gd.buttons.AddButtonBordered("Escort", "2500m", 5, w + 300, v + 5, 100, "Pursue2500m")
		ElseIf g.pursueOrderStep = 2 Then
			DrawRect(0, v, gfx.width, gd.ToolbarHeight + 10)
			SetColor(240, 240, 0)
			gfx.CenteredText(TGFX.FontXLarge, "Click target to set pursued vessel, or ESC to cancel", gfx.height - 45)
		ElseIf g.fireTargetStep = 2 Then
			DrawRect(0, v, gfx.width, gd.ToolbarHeight + 10)
			SetColor(240, 240, 0)
			gfx.CenteredText(TGFX.FontXLarge, "Click to select target, or ESC to cancel", gfx.height - 45)
		ElseIf g.moveOrderStep = 1 Then
			DrawRect(0, v, gfx.width, gd.ToolbarHeight + 10)
			SetColor(240, 240, 0)
			gfx.CenteredText(TGFX.FontXLarge, "Click to set move point, or ESC to cancel", gfx.height - 45)
		ElseIf g.headingOrderStep = 1 Then
			DrawRect(0, v, gfx.width, gd.ToolbarHeight + 10)
			SetColor(240, 240, 0)
			gfx.CenteredText(TGFX.FontXLarge, "Click to set heading, or ESC to cancel", gfx.height - 45)
		ElseIf g.fireTargetStep = 1 And selectedVessel <> Null Then
			DrawRect(0, v, gfx.width, gd.ToolbarHeight + 10)
			Local nb:Int = 0
			If selectedVessel.gunsCount > 0 Then nb :+ 1
			If selectedVessel.missilesCount > 0 Then nb :+ 1
			If selectedVessel.gunsCount > 0 And selectedVessel.missilesCount > 0 Then nb :+ 1
			Local w:Int = (gfx.width - ((nb + 6) * 100)) / 2
			If selectedVessel.gunsCount > 0 Then 
				gd.buttons.AddButtonBordered("Fire", "Guns", 1, w, v + 5, 100, "GunsOnly")
				w :+ 100
			End If
			If selectedVessel.missilesCount > 0 Then 
				gd.buttons.AddButtonBordered("Fire", "Missiles", 2, w, v + 5, 100, "MissileOnly")
				w :+ 100
			End If
			If selectedVessel.gunsCount > 0 And selectedVessel.missilesCount > 0 Then 
				gd.buttons.AddButtonBordered("All", "Weapons", 3, w, v + 5, 100, "AllWeapons")
				w :+ 100
			End If
			If g.autoBow = 1 Then 
				gd.buttons.AddButtonMS("Auto Bow", 5, w + 100, v + 2, 100, "AutoBowOff")
			Else
				gd.buttons.AddButtonMS("Auto Bow", 5, w + 100, v + 2, 100, "AutoBowOn", 1)
			End If
			If g.autoPort = 1 Then
				gd.buttons.AddButtonMS("Auto Port", 5, w + 200, v + 15, 100, "AutoPortOff")
			Else
				gd.buttons.AddButtonMS("Auto Port", 5, w + 200, v + 15, 100, "AutoPortOn", 1)
			End If
			If g.autoStarboard = 1 Then
				gd.buttons.AddButtonMS("Auto Starboard", 5, w, v + 15, 100, "AutoStarboardOff")
			Else
				gd.buttons.AddButtonMS("Auto Starboard", 5, w, v + 15, 100, "AutoStarboardOn", 1)
			End If
			If g.autoStern = 1 Then
				gd.buttons.AddButtonMS("Auto Stern", 5, w + 100, v + 28, 100, "AutoSternOff")
			Else
				gd.buttons.AddButtonMS("Auto Stern", 5, w + 100, v + 28, 100, "AutoSternOn", 1)
			End If
			w :+ (3 * 100)
			If g.rateFull = 1 Then
				gd.buttons.AddButtonMS("Full Rate", 6, w, v + 2, 100, "FullRateOff")
			Else
				gd.buttons.AddButtonMS("Full Rate", 6, w, v + 2, 100, "FullRateOn", 1)
			End If
			If g.rateHalf = 1 Then
				gd.buttons.AddButtonMS("Half Rate", 6, w + 100, v + 2, 100, "HalfRateOff")
			Else
				gd.buttons.AddButtonMS("Half Rate", 6, w + 100, v + 2, 100, "HalfRateOn", 1)
			End If
			If g.rateQuarter = 1 Then
				gd.buttons.AddButtonMS("Quarter Rate", 6, w, v + 28, 100, "QuarterRateOff")
			Else
				gd.buttons.AddButtonMS("Quarter Rate", 6, w, v + 28, 100, "QuarterRateOn", 1)
			End If
			If g.rateHarassing = 1 Then
				gd.buttons.AddButtonMS("Harassing", 6, w + 100, v + 28, 100, "HarassingOff")
			Else
				gd.buttons.AddButtonMS("Harassing", 6, w + 100, v + 28, 100, "HarassingOn", 1)
			End If
			If g.rateWeapon = 1 Then
				gd.buttons.AddButtonL("Auto", "Rate", 6, w + 200, v + 2, 100, "WeaponRateOff")
			Else
				gd.buttons.AddButtonL("Auto", "Rate", 6, w + 200, v + 2, 100, "WeaponRateOn", 1)
			End If
		End If
		?debug
   			TProfiler.Leave("GameRender::Prompts")
  		?
	End Function

	Function RenderDeadEntities(gfx:TGFX, gd:TGameData, g:TGameState, entities:TList, simple:Int, selectedVessel:TGameEntity, hoveringVessel:TGameEntity, missionBuilder:Int, s:Double, ms:Long)
		?debug
   			TProfiler.Enter("GameRender::RenderDeadEntities")
  		?
		For Local ge:TGameEntity = EachIn entities
		
			' If visible, render
			If Abs(ge.tX) < gfx.width Or Abs(ge.tY) < gfx.height Then 
				If g.scale < 20.0 Or (missionBuilder = 0 And g.cinematicMode = 1) Then
					RenderDeadEntityArcade(gd, g, ge, selectedVessel, hoveringVessel, 0.1, s / 17, g.worldSizeX / 60000, missionBuilder, gfx, ms)	
				End If
			End If
			
		Next
		?debug
   			TProfiler.Leave("GameRender::RenderDeadEntities")
  		?
	End Function
	
	Function RenderEntities(gfx:TGFX, gd:TGameData, g:TGameState, entities:TList, simple:Int, selectedVessel:TGameEntity, hoveringVessel:TGameEntity, missionBuilder:Int, s:Double, ms:Long)
		?debug
   			TProfiler.Enter("GameRender::RenderEntities")
  		?
		For Local ge:TGameEntity = EachIn entities
			Local adjust:Double = (g.worldSizeX / 60000)

			' Visible?
			If ge.visible = 0 And g.optionShowEnemyInfo = 0 Then Continue
			
			' Show orders?
			If (ge.vessel.fighter = 0 Or g.showFightersIconView = 1) And (simple = 0 And g.showOrders = 1) Or (simple = 0 And selectedVessel = ge) Or (ge.vessel.ship = 0 And g.showMissileTargets = 1) Then ShowOrders(gfx, ge, gd, g, s)

			' Show waypoints/escort?
			If missionBuilder = 1 And selectedVessel = ge And ge.waypoints.Count() > 0 Then ShowWaypoints(gfx, ge, gd, g, s)
			If missionBuilder = 1 And selectedVessel = ge And selectedVessel.ai.escortID > -1 Then ShowEscort(gfx, ge, gd, g, s)

			' If visible, render
			If Abs(ge.tX) < gfx.width Or Abs(ge.tY) < gfx.height Then 
				If g.scale < 20.0 Or (missionBuilder = 0 And g.cinematicMode = 1) Then
					RenderEntityArcade(gd, g, ge, selectedVessel, hoveringVessel, 0.1, s / 17, adjust, missionBuilder, gfx, ms)	
				Else
					RenderEntityIcon(gd, g, ge, selectedVessel, hoveringVessel, 0.1, s / 17, adjust, missionBuilder, gfx, ms)	
				End If
			End If
			
			' Trails?
			If g.ShowTrails And (ge.vessel.ship = 1 Or (ge.vessel.ship = 0 And ge.vessel.missile = 1)) Then ShowTrails(gd, g, ge, s)
			
			' EMP?
			If ge.haloActive > 0 Then
				Local s2:Double = TWeaponClass.EMPRadius / g.scale / adjust
				Local time:Double = ms - ge.haloActive
				If time < 250 Then
					SetAlpha((time / 250) * 0.75)
				ElseIf time > 1250 Then
					SetAlpha(((1500 - time) / 250) * 0.75)
				Else
					SetAlpha(0.75)
				End If 
				SetColor(255, 255, 255)
				SetScale(s2 / 256, s2 / 256)
				Local frame:Int = ((ms - ge.haloActive) / 30) & 7
				DrawImage(gd.halo, ge.tX, ge.tY, frame)
				SetScale(1.0, 1.0)
			End If
			
			' Electric?
			If ge.electricActive > 0 Then
				Local s2:Double = ge.collisionSize / g.scale / adjust
				Local time:Double = ms - ge.electricActive
				If time < 250 Then
					SetAlpha((time / 250) * 0.75)
				ElseIf time > 1250 Then
					SetAlpha(((1500 - time) / 250) * 0.75)
				Else
					SetAlpha(0.75)
				End If 
				SetColor(255, 255, 255)
				SetScale(s2 / 256, s2 / 256)
				Local frame:Int = ((ms - ge.electricActive) / 30) & 15
				DrawImage(gd.electric, ge.tX, ge.tY, frame)
				SetScale(1.0, 1.0)
			End If
			
			' Mission protect?
			If g.victoryCondition = TVictoryConditions.VictoryProtect And g.cinematicMode = 0 And ListContains(g.victoryEntityList, ge)
				Local v:Double = (Max(ge.vessel.renderedImage.width, ge.vessel.renderedImage.height) / g.strategicScale / 4.0) * adjust
				SetScale(Max(0.1, (s / 17) / adjust) * v / 1.5, Max(0.1, (s / 17) / adjust) * v / 1.5)
				SetColor(255, 255, 255)
				SetRotation(gd.sf.r * 100.0)
				DrawImage(gd.spinner2, ge.tX, ge.tY)
				SetScale(1.0, 1.0)
			End If
		Next
		?debug
   			TProfiler.Leave("GameRender::RenderEntities")
  		?
	End Function
	
	Function RenderEntityIcon(gd:TGameData, g:TGameState, ge:TGameEntity, selectedVessel:TGameEntity, hoveringVessel:TGameEntity, minS:Double, s:Double, adjust:Double, missionBuilder:Int, gfx:TGFX, ms:Long)
		?debug
   			TProfiler.Enter("GameRender::RenderEntityIcon")
  		?
		SetColor(255, 255, 255)
		SetAlpha(1.0)
		SetLineWidth(1.0)
		If ge.vessel.ship = 0 Then
			SetRotation(ge.angle + 90 + g.rotate)
			If g.bulletsInColour Then SetColor(ge.w.cR, ge.w.cG, ge.w.cB) Else SetColor(255, 255, 255)
			If ge.w.t = TWeaponClass.BulletType Then
				If ge.w.id = TWeaponClass.fighterID Then
					SetScale(Max(MinS * 2.0, s) / 16.0 / adjust, Max(MinS * 2.0, s) / 16.0 / adjust)
					DrawImage(ge.w.projectileImg, ge.tX, ge.tY)
				Else
					SetScale(Max(MinS * 2.0, s) / 2.0 / adjust, Max(MinS * 2.0, s) / 2.0 / adjust)
					DrawImage(gd.missile, ge.tX, ge.tY)
				End If
			ElseIf ge.w.t = TWeaponClass.missileType Then
				SetScale(Max(MinS * 2.0, s) / 2.0 / adjust, Max(MinS * 2.0, s) / 2.0 / adjust)
				DrawImage(gd.missile, ge.tX, ge.tY)
			Else
				SetColor(255, 255, 255)
				SetScale(Max(MinS * 2.0, s) / 8.0 / adjust, Max(MinS * 2.0, s) / 8.0 / adjust)
				SetRotation(AdjustAngle(ge.angle + g.rotate + (gd.sf.r * 5000)))
				DrawImage(gd.shrapnel, ge.tX, ge.tY)
			End If
			SetRotation(0)
			SetScale(1.0, 1.0)
			If missionBuilder = 0 And g.cinematicMode = 0 Then
				SetColor(ge.w.cR, ge.w.cG, ge.w.cB)
				Select ge.w.t
				Case TWeaponClass.bulletType
					BoundingBox(ge, Max(minS, s / adjust) * 10, 1.0)
				Case TWeaponClass.missileType
					BoundingBox(ge, Max(minS, s / adjust) * 25, 1.0)
				End Select
				SetColor(255, 255, 255)
			End If
			SetColor(255, 255, 255)
		Else
			Local v:Double
			If ge.vessel.fighter = 0 Then
				v = (Max(ge.vessel.renderedImage.width, ge.vessel.renderedImage.height) / g.strategicScale / 4.0) * adjust
			Else
				v = (Max(g.fleets[ge.owningPlayerNo].drone.width, g.fleets[ge.owningPlayerNo].drone.height) / g.strategicScale / 4.0 / 10.0) * adjust
			End If

			' Autoarcs?
			If ge.vessel.fighter = 0 And ((missionBuilder = 0 And (ge.owningPlayerNo = 0 Or g.optionShowEnemyInfo = 1) And g.cinematicMode = 0) Or missionBuilder = 1) Then RenderAutoArcs(g, ge, s, minS, adjust)

			' Set alpha on selected
			If selectedVessel = ge Then SetAlpha(1.0) ElseIf hoveringVessel = ge Then SetAlpha(0.9) Else SetAlpha(0.8)

			SetRotation(ge.angle + 90 + g.rotate)
			SetColor(255, 255, 255)
			SetScale(Max(minS, s / adjust) * v, Max(minS, s / adjust) * v)
			If ge.owningPlayerNo = 0 Then DrawImage(gd.player1Icon, ge.tX, ge.tY) Else DrawImage(gd.player2Icon, ge.tX, ge.tY)
			SetScale(1.0, 1.0)
			SetRotation(0)
			
			' Textbox
			If ge.vessel.fighter = 0 Or g.showFightersIconView = 1 Then
				Local tW:Int, tH:Int
				If ge.vessel.fighter = 0 Then 
					gfx.SetSpecificFontSize(80.0 * Max(s / Adjust, minS))
					tW = gfx.GetCachedFontWidth(ge.name)
					tH = gfx.GetCachedFontHeight(ge.name)
				Else
					gfx.SetSpecificFontSize(60.0 * Max(s / Adjust, minS))
					tW = gfx.GetCachedFontWidth(ge.name)
					tH = gfx.GetCachedFontHeight(ge.name)
				End If
				SetPlayerColour(ge.owningPlayerNo, gd.fleetColours)
				SetAlpha(0.35)
				DrawRect(ge.tX - (tW / 2) - 3, ge.tY - (tH / 2) - 3, tW + 6, tH + 6)
				SetAlpha(1.0)
				
				' Label
				SetColor(255, 255, 0)
				DrawText(ge.name, Int(ge.tX - (tW / 2)), Int(ge.tY - (tH / 2)))
			End If
			
			' Bounding box
			If ge = selectedVessel Then
				SetColor(255, 255, 255)
				BoundingBox(ge, Max(minS, s / adjust) * v * 70, 1.0)
			End If
		End If
		?debug
   			TProfiler.Leave("GameRender::RenderEntityIcon")
  		?
	End Function
	
	Function RenderDeadEntityArcade(gd:TGameData, g:TGameState, ge:TGameEntity, selectedVessel:TGameEntity, hoveringVessel:TGameEntity, minS:Double, s:Double, adjust:Double, missionBuilder:Int, gfx:TGFX, ms:Long)
		?debug
   			TProfiler.Enter("GameRender::RenderDeadEntityArcade")
  		?
		If ge.vessel.ship = 1 Then
			SetRotation(ge.angle + 90 + g.rotate)
			Local l:Int = 50 - ((ms - ge.died) / 40.0)
			If l < 0 Then l = 0
			SetColor(l + 120, l + 120, l + 120)
			SetAlpha(1.0)
			If ge.vessel.fighter = 0 Then
				SetScale(s / adjust / 2.5, s / adjust / 2.5)
				DrawImage(ge.vessel.renderedImage, ge.tX, ge.tY)
			Else
				SetScale(s / adjust / 25.0, s / adjust / 25.0)
				DrawImage(g.fleets[ge.owningPlayerNo].drone, ge.tX, ge.tY)
			End If
		End If
		?debug
   			TProfiler.Leave("GameRender::RenderDeadEntityArcade")
  		?
	End Function
	
	Function RenderEntityArcade(gd:TGameData, g:TGameState, ge:TGameEntity, selectedVessel:TGameEntity, hoveringVessel:TGameEntity, minS:Double, s:Double, adjust:Double, missionBuilder:Int, gfx:TGFX, ms:Long)
		?debug
   			TProfiler.Enter("GameRender::RenderEntityArcade")
  		?
		SetColor(255, 255, 255)
		SetAlpha(1.0)
		SetLineWidth(1.0)
		If ge.vessel.ship = 0 Then
			SetRotation(ge.angle + 90 + g.rotate)
			If g.bulletsInColour Then SetColor(ge.w.cR, ge.w.cG, ge.w.cB) Else SetColor(255, 255, 255)
			If ge.w.t = TWeaponClass.BulletType Then
				If ge.w.id = TWeaponClass.fighterID Then
					SetScale(Max(MinS * 2.0, s) / 16.0 / adjust, Max(MinS * 2.0, s) / 16.0 / adjust)
					DrawImage(ge.w.projectileImg, ge.tX, ge.tY)
				Else
					SetScale(Max(MinS * 2.0, s) / 2.0 / adjust, Max(MinS * 2.0, s) / 2.0 / adjust)
					DrawImage(gd.missile, ge.tX, ge.tY)
				End If
			ElseIf ge.w.t = TWeaponClass.missileType Then
				SetScale(Max(MinS * 2.0, s) / 2.0 / adjust, Max(MinS * 2.0, s) / 2.0 / adjust)
				DrawImage(gd.missile, ge.tX, ge.tY)
			Else
				SetColor(255, 255, 255)				
				SetScale(Max(MinS * 2.0, s) / 8.0 / adjust, Max(MinS * 2.0, s) / 8.0 / adjust)
				SetRotation(AdjustAngle(ge.angle + g.rotate + (gd.sf.r * 5000)))
				DrawImage(gd.shrapnel, ge.tX, ge.tY)
			End If
			SetRotation(0)
			SetScale(1.0, 1.0)
			If missionBuilder = 0 And g.cinematicMode = 0 Then
				SetColor(ge.w.cR, ge.w.cG, ge.w.cB)
				Select ge.w.t
				Case TWeaponClass.bulletType
					BoundingBox(ge, Max(minS, s / adjust) * 10, 1.0)
				Case TWeaponClass.missileType
					BoundingBox(ge, Max(minS, s / adjust) * 25, 1.0)
				End Select
				SetColor(255, 255, 255)
			End If
		Else
			Local v:Double
			If ge.vessel.fighter = 0 Then
				v = (Max(ge.vessel.renderedImage.width, ge.vessel.renderedImage.height) / g.strategicScale / 4.0) * adjust
			Else
				v = (Max(g.fleets[ge.owningPlayerNo].drone.width, g.fleets[ge.owningPlayerNo].drone.height) / g.strategicScale / 4.0 / 10.0) * adjust
			End If

			' Auto arcs
			If ge.vessel.fighter = 0 And ((missionBuilder = 0 And (ge.owningPlayerNo = 0 Or g.optionShowEnemyInfo = 1) And g.cinematicMode = 0) Or missionBuilder = 1) Then RenderAutoArcs(g, ge, s, minS, adjust)

			' Selected alpha
			If selectedVessel = ge Then SetAlpha(0.5) ElseIf hoveringVessel = ge Then SetAlpha(0.4) Else SetAlpha(0.3)
			
			' Targeteter
			SetRotation(ge.angle + 90 + g.rotate)
			If (selectedVessel = ge And ge.owningPlayerNo = 0) Or missionBuilder = 1 Or (g.cinematicMode = 0 And (g.optionShowEnemyInfo = 1 Or ge.owningPlayerNo = 0)) Then 
				SetColor(255, 255, 255)
				SetScale((s * v) / adjust / 3.5, (s * v) / adjust / 3.5)
				DrawImage(gd.targeter, ge.tX, ge.tY)
			End If
			
			' Selected alpha
			If selectedVessel = ge Then SetAlpha(0.8) ElseIf hoveringVessel = ge Then SetAlpha(0.7) Else SetAlpha(0.6)
			
			' Vessel
'			SetPlayerColour(ge.owningPlayerNo, gd.fleetColours)
			SetAlpha(1.0)
			SetColor(255, 255, 255)
			If ge.vessel.fighter = 0 Then
				SetScale(s / adjust / 2.5, s / adjust / 2.5)
'				ge.vessel.LiveRender(gd.pieces, ge.tX, ge.tY, ge.angle + 90 + g.rotate, s / adjust)
				DrawImage(ge.vessel.renderedImage, ge.tX, ge.tY)
				SetRotation(ge.angle + 90 + g.rotate)
			Else
				SetScale(s / adjust / 25, s / adjust / 25)
				DrawImage(g.fleets[ge.owningPlayerNo].drone, ge.tX, ge.tY)
			End If
			
			' Show stats?
			If (ge.vessel.fighter = 0 Or g.showFightersIconView = 1) And ((selectedVessel = ge And ge.owningPlayerNo = 0) Or (g.cinematicMode = 0 And (g.optionShowEnemyInfo = 1 Or ge.owningPlayerNo = 0))) And missionBuilder = 0 Then 
				If selectedVessel = ge Then SetAlpha(1.0) ElseIf hoveringVessel = ge Then SetAlpha(0.8) Else SetAlpha(0.6)
				ShowStats(gd, ge, s, v, adjust)
			End If
			
			' Flames from weapons
			Local tX:Double, tY:Double, x1:Double, y1:Double
			SetColor(255, 255, 255)
			SetScale(s / adjust / 2.5, s / adjust / 2.5)
			If missionBuilder = 0 And g.cinematicMode = 1 And ge.vessel.fighter = 0 Then
				For Local x:TXY = EachIn ge.vessel.missiles
					Local lt:TBlock = ge.shape[x.x, x.y]
					If (ms - lt.fired) < 500 And lt.fired < ms Then
						SetRotation(90 + g.rotate + lt.TubeAngle(ge.angle))
						Select lt.rot
						Case 0
							x1 = ((x.x - ge.centreX) * TGameEntity.SectionSizeX)
							y1 = ((x.y - ge.centreY - 0.8) * TGameEntity.SectionSizeY)
						Case 1
							x1 = ((x.x - ge.centreX + 0.8) * TGameEntity.SectionSizeX)
							y1 = ((x.y - ge.centreY) * TGameEntity.SectionSizeY)
						Case 2
							x1 = ((x.x - ge.centreX) * TGameEntity.SectionSizeX)
							y1 = ((x.y - ge.centreY + 0.8) * TGameEntity.SectionSizeY)
						Case 3
							x1 = ((x.x - ge.centreX - 0.8) * TGameEntity.SectionSizeX)
							y1 = ((x.y - ge.centreY) * TGameEntity.SectionSizeY)
						End Select
						RotateAroundOrigin(x1, y1, ge.angle + 90 + g.rotate)
						g.TranslateXY(ge.x + x1, ge.y - y1, tX, tY)
						DrawImage(gd.missileFlame, tX, tY)
					End If
				Next
				For Local x:TXY = EachIn ge.vessel.guns
					Local lt:TBlock = ge.shape[x.x, x.y]
					If (ms - lt.fired) < 100 And lt.fired < ms Then
						SetRotation(90 + g.rotate + lt.TubeAngle(ge.angle))
						Select lt.rot
						Case 0
							x1 = ((x.x - ge.centreX) * TGameEntity.SectionSizeX)
							y1 = ((x.y - ge.centreY - 1) * TGameEntity.SectionSizeY)
						Case 1
							x1 = ((x.x - ge.centreX + 1) * TGameEntity.SectionSizeX)
							y1 = ((x.y - ge.centreY) * TGameEntity.SectionSizeY)
						Case 2
							x1 = ((x.x - ge.centreX) * TGameEntity.SectionSizeX)
							y1 = ((x.y - ge.centreY + 1) * TGameEntity.SectionSizeY)
						Case 3
							x1 = ((x.x - ge.centreX - 1) * TGameEntity.SectionSizeX)
							y1 = ((x.y - ge.centreY) * TGameEntity.SectionSizeY)
						End Select
						RotateAroundOrigin(x1, y1, ge.angle + 90 + g.rotate)
						g.TranslateXY(ge.x + x1, ge.y - y1, tX, tY)
						DrawImage(gd.railgunFlame, tX, tY)
					End If
				Next
			End If
			
			' Exhaust
			If ge.currentSpeed > 2.5 And ge.vessel.fighter =0 Then
				SetRotation(ge.angle + 90 + g.rotate)
				For Local y:Int = ge.firstY To ge.lastY
					For Local x:Int = ge.firstX To ge.lastX
						Local b:TBlock = ge.shape[x, y]
						Local piece:TPiece = gd.pieces[b.piece]
						If piece.propulsion <> Null And ge.onOff[x, y] > 0 Then
							Local frame:Int = ((ms - ge.born) / 30) & 31
							
							' Burner 1
							Local x1:Double = ((x - ge.centreX - 0.225) * TGameEntity.SectionSizeX)
							Local y1:Double = ((y - ge.centreY + 0.5) * TGameEntity.SectionSizeY)
							RotateAroundOrigin(x1, y1, ge.angle + 90 + g.rotate)
							g.TranslateXY(ge.x + x1, ge.y - y1, tX, tY)
							If ge.owningPlayerNo = 0 Then DrawImage(gd.exhaust1, tX, tY, frame) Else DrawImage(gd.exhaust2, tX, tY, frame)

							' Burner 2
							x1 = ((x - ge.centreX + 0.225) * TGameEntity.SectionSizeX)
							y1 = ((y - ge.centreY + 0.5) * TGameEntity.SectionSizeY)
							RotateAroundOrigin(x1, y1, ge.angle + 90 + g.rotate)
							g.TranslateXY(ge.x + x1, ge.y - y1, tX, tY)
							If ge.owningPlayerNo = 0 Then DrawImage(gd.exhaust1, tX, tY, frame) Else DrawImage(gd.exhaust2, tX, tY, frame)
						End If
					Next
				Next
			End If
			SetScale(1.0, 1.0)
			
			' Stats
			SetRotation(0)
			If (ge.vessel.fighter = 0 Or g.showFightersIconView = 1) And ((selectedVessel = ge And ge.owningPlayerNo = 0) Or (g.cinematicMode = 0 And (g.optionShowEnemyInfo = 1 Or ge.owningPlayerNo = 0))) And missionBuilder = 0 And g.scale < 20.0 Then
				If ge.vessel.fighter = 0 Then
					gfx.SetSpecificFontSize(20.0 * Max(s / Adjust, minS * 4.0))
				Else
					gfx.SetSpecificFontSize(15.0 * Max(s / Adjust, minS * 4.0))
				End If

				' Shield and armour
				Local percentShield:Double = Double(ge.shieldRemaining) / Double(ge.shield)
				If percentShield > 1.0 Then percentShield = 1.0
				If percentShield < 0.0 Then percentShield = 0.0  
				Local percentArmour:Double = Double(ge.armourRemaining) / Double(ge.armour)
				If percentArmour > 1.0 Then percentArmour = 1.0
				If percentArmour < 0.0 Then percentArmour = 0.0  
				
				' Loadout
				Local mW:Double = 0
				Local mWT:Double = 0
				Local tH:Int = gfx.GetCachedFontHeight(ge.name)
				Local tth:Int = th
				If ge.vessel.fighter = 0 Then
					Local lc:Int = 0
					If ge.vessel.fighter = 0 Then
						For Local i:Int = 0 To TWeaponClass.NumberOfClasses - 1
							If ge.initialLoadout[i] > 0 Then 
								Local w:Int = gfx.GetCachedFontWidth(gd.weapons[i].name + ": 00")
								If w > mW Then mW = w
								lc :+ 1
							End If
						Next
					End If
					mWT = mW
					tth = (3 + lc) * th
				End If
				If gfx.GetCachedFontWidth(ge.name) > mwT Then mwT = gfx.GetCachedFontWidth(ge.name)
				If ge.vessel.fighter = 1 Then tth :+ th
				
				' Textbox
				SetPlayerColour(ge.owningPlayerNo, gd.fleetColours)
				SetAlpha(0.35)
				DrawRect(ge.tX - (mWT / 2) - 3, ge.tY - (tth / 2) - 3, mWT + 6, tth + 6)
				SetAlpha(1.0)
			
				' Label
				Local top:Int = ge.tY - (tth / 2)
				SetColor(255, 255, 0)
				DrawText(ge.name, Int(ge.tX - (gfx.GetCachedFontWidth(ge.name) / 2)), Int(top))
				
				' Shield
				If ge.vessel.fighter = 0 Then
					Local s:String = "Shield: "
					Local s2:String = Int(percentShield * 100) + "%"
					Local w1:Double = gfx.GetCachedFontWidth(s)
					Local w2:Double = gfx.GetCachedFontWidth(s + s2)
					SetColor(220, 220, 220)
					DrawText(s, Int(ge.tX - (w2 / 2)), Int(top + (th * 1)))
					SetColor(255, 255, 0)
					DrawText(s2, Int(ge.tX - (w2 / 2) + w1), Int(top + (th * 1)))

					' Hull
					s = "Hull: "
					s2 = Int(percentArmour * 100) + "%"
					w1 = gfx.GetCachedFontWidth(s)
					w2 = gfx.GetCachedFontWidth(s + s2)
					SetColor(220, 220, 220)
					DrawText(s, Int(ge.tX - (w2 / 2)), Int(top + (th * 2)))
					SetColor(255, 255, 0)
					DrawText(s2, Int(ge.tX - (w2 / 2) + w1), Int(top + (th * 2)))
				
					' Loadout
					If ge.vessel.fighter = 0 Then
						Local j:Int = 0
						Local twN:Int = gfx.GetCachedFontWidth("00")
						For Local i:Int = 0 To TWeaponClass.NumberOfClasses - 1
							If ge.initialLoadout[i] > 0 Then
								s = gd.weapons[i].name + ":   "
								s2 = ge.loadout[i]
								w1 = gfx.GetCachedFontWidth(s)
								SetColor(220, 220, 220)
								DrawText(s, Int(ge.tX + (mW / 2) - twN - w1), Int(top + (th * (3 + j))))
								SetColor(154, 144, 255)
								DrawText(s2, Int(ge.tX + (mW / 2) - twN), Int(top + (th * (3 + j))))
								j :+ 1
							End If
						Next
					End If
				Else
					Local s:String = "Ammo: "
					Local s2:String = ge.fighterL.numberRemaining + " shots"
					Local w1:Double = gfx.GetCachedFontWidth(s)
					Local w2:Double = gfx.GetCachedFontWidth(s + s2)
					SetColor(220, 220, 220)
					DrawText(s, Int(ge.tX - (w2 / 2)), Int(top + (th * 1)))
					SetColor(255, 255, 0)
					DrawText(s2, Int(ge.tX - (w2 / 2) + w1), Int(top + (th * 1)))
				End If
			End If
	
			' Bounding box
			If ge = selectedVessel And g.cinematicMode = 0 Then
				SetRotation(0)
				SetColor(255, 255, 255)
				BoundingBox(ge, Max(minS, s / adjust) * v * 70, 1.0)
			End If
		End If
		?debug
   			TProfiler.Leave("GameRender::RenderEntityArcade")
  		?
	End Function

	Function ShowStats(gd:TGameData, ge:TGameEntity, s:Double, v:Double, adjust:Double)
		?debug
   			TProfiler.Enter("GameRender::ShowStats")
  		?
		Local percentShield:Double = Double(ge.shieldRemaining) / Double(ge.shield)
		If percentShield > 1.0 Then percentShield = 1.0
		If percentShield < 0.0 Then percentShield = 0.0  
		Local percentArmour:Double = Double(ge.armourRemaining) / Double(ge.armour)
		If percentArmour > 1.0 Then percentArmour = 1.0
		If percentArmour < 0.0 Then percentArmour = 0.0  
		
		If ge.vessel.fighter = 0 Then
			'Shield
			SetColor(128, 128, 128)
			Local sb:Double = (s * v) / adjust / 4.0
			For Local a:Double = 0 To 1.0 Step 0.2
				If percentShield >= a Then
					SetAlpha((percentShield - a) * 5)
					SetScale(sb * (1.5 + (a * 0.5)), sb * (1.5 + (a * 0.5)))
					DrawImage(gd.shield, ge.tX, ge.tY)
				End If
			Next			

			' Hull
			For Local a:Double = 0 To 1.0 Step 0.2
				If percentArmour >= a Then
					SetAlpha((percentArmour - a) * 5)
					SetScale(sb * (1.0 + (a * 0.5)), sb * (1.0 + (a * 0.5)))
					DrawImage(gd.hull, ge.tX, ge.tY)
				End If
			Next
		Else
	
			'Shield
			SetColor(128, 128, 128)
			Local sb:Double = (s * v) / adjust / 4.0
			For Local a:Double = 0 To 1.0 Step 0.5
				If percentShield >= a Then
					SetAlpha((percentShield - a) * 5)
					SetScale(sb * (1.5 + (a * 0.5)), sb * (1.5 + (a * 0.5)))
					DrawImage(gd.shield, ge.tX, ge.tY)
				End If
			Next			

			' Hull
			For Local a:Double = 0 To 1.0 Step 0.5
				If percentArmour >= a Then
					SetAlpha((percentArmour - a) * 5)
					SetScale(sb * (1.0 + (a * 0.5)), sb * (1.0 + (a * 0.5)))
					DrawImage(gd.hull, ge.tX, ge.tY)
				End If
			Next
		End If
		SetAlpha(1.0)
		SetScale(1.0, 1.0)
		?debug
   			TProfiler.Leave("GameRender::ShowStats")
  		?
	End Function
		
	Function ShowTrails(gd:TGameData, g:TGameState, ge:TGameEntity, s:Double)
		?debug
   			TProfiler.Enter("GameRender::ShowTrails")
  		?
		If ge.vessel.ship = 1 And ge.vessel.fighter = 0 Then 
			?debug
   				TProfiler.Leave("GameRender::ShowTrails")
  			?
			Return
		End If
		SetColor(ge.w.cR, ge.w.cG, ge.w.cB)
		Local a:Double = 1.0
		Local f:Int = 0, pX:Double, pY:Double
		If ge.vessel.ship = 1 Then SetLineWidth(2.0) Else SetLineWidth(1.0)
		For Local x:TPoint = EachIn ge.trail
			Local tX:Double, tY:Double
			g.TranslateXY(x.x, x.y, tX, tY)
			If f > 0 Then
'				If ge.vessel.ship = 1 Then SetLineWidth(3.0) Else SetLineWidth(2.0)
'				SetAlpha(a / 2)
'				DrawLine(pX, pY, tX, tY, False)
				If ge.vessel.ship = 1 Then SetLineWidth(2.0) Else SetLineWidth(1.0)
				SetAlpha(a)
				DrawLine(pX, pY, tX, tY, False)
				If ge.vessel.ship = 1 Then a :- 0.15 Else a :- 0.05
				If a <= 0 Then Exit
			End If
			f :+ 1
			pX = tX
			pY = tY
		Next
		?debug
   			TProfiler.Leave("GameRender::ShowTrails")
  		?
	End Function
	
	Function RenderAutoArcs(g:TGameState, ge:TGameEntity, s:Double, minSize:Double, adjust:Double)
		?debug
   			TProfiler.Enter("GameRender::RenderAutoArcs")
  		?
		SetRotation(0.0)
		SetScale(1.0, 1.0)
		SetAlpha(0.35)
		Local x1:Double, y1:Double, x2:Double, y2:Double
		Local sizeArc:Double = Max(s, minSize) * 256.0 / adjust
		If ge.autoN > 0 Then
			PolarToCartesian(sizeArc, ge.angle + g.rotate - 40, x1, y1)
			PolarToCartesian(sizeArc, ge.angle + g.rotate + 40, x2, y2)
			AutoArcColour(ge.autoN)
			DrawPoly([Float(ge.tX), Float(ge.tY), Float(ge.tX + x1), Float(ge.tY + y1), Float(ge.tX + x2), Float(ge.tY + y2)])
		End If
		If ge.autoE > 0 Then
			PolarToCartesian(sizeArc, ge.angle + g.rotate + 50, x1, y1)
			PolarToCartesian(sizeArc, ge.angle + g.rotate + 130, x2, y2)
			AutoArcColour(ge.autoE)
			DrawPoly([Float(ge.tX), Float(ge.tY), Float(ge.tX + x1), Float(ge.tY + y1), Float(ge.tX + x2), Float(ge.tY + y2)])
		End If
		If ge.autoS > 0 Then
			PolarToCartesian(sizeArc, ge.angle + g.rotate + 140, x1, y1)
			PolarToCartesian(sizeArc, ge.angle + g.rotate + 220, x2, y2)
			AutoArcColour(ge.autoS)
			DrawPoly([Float(ge.tX), Float(ge.tY), Float(ge.tX + x1), Float(ge.tY + y1), Float(ge.tX + x2), Float(ge.tY + y2)])
		End If
		If ge.autoW > 0 Then
			PolarToCartesian(sizeArc, ge.angle + g.rotate + 230, x1, y1)
			PolarToCartesian(sizeArc, ge.angle + g.rotate + 310, x2, y2)
			AutoArcColour(ge.autoW)
			DrawPoly([Float(ge.tX), Float(ge.tY), Float(ge.tX + x1), Float(ge.tY + y1), Float(ge.tX + x2), Float(ge.tY + y2)])
		End If
		SetAlpha(1.0)
		SetColor(255, 255, 255)
		SetScale(s, s)
		?debug
   			TProfiler.Leave("GameRender::RenderAutoArcs")
  		?
	End Function
		
	Function AutoArcColour(auto:Int)
		Select auto
		Case 1
			SetColor(0, 0, 255)
		Case 2
			SetColor(255, 0, 0)
		Case 3
			SetColor(255, 0, 255)
		End Select
	End Function
	
	Function ShowEscort(gfx:TGFX, ge:TGameEntity, gd:TGameData, g:TGameState, s:Double)
		?debug
   			TProfiler.Enter("GameRender::ShowEscort")
  		?
		SetAlpha(0.75)
		If ge.owningPlayerNo = 0 Then SetLineWidth(4.0) Else SetLineWidth(2.0)
		SetColor(255, 255, 255)
		DrawLine(ge.tX, ge.tY, ge.ai.escort.tX, ge.ai.escort.tY)				
		RenderTarget(gfx, gd, g, ge.tX, ge.tY, ge.ai.escort.tX, ge.ai.escort.tY, 1, s)
		?debug
   			TProfiler.Leave("GameRender::ShowEscort")
  		?
	End Function
	
	Function ShowWaypoints(gfx:TGFX, ge:TGameEntity, gd:TGameData, g:TGameState, s:Double)
		?debug
   			TProfiler.Enter("GameRender::ShowWaypoints")
  		?
		Local lastX:Double = Null, lastY:Double = Null, startX:Double, startY:Double
		If ge.ai.ignoreStartingWaypoint = 0 Then 
			lastX = ge.tX
			lastY = ge.tY
			startX = ge.tX
			startY = ge.tY
		End If
		Local tX:Double, tY:Double
		SetAlpha(0.75)
		SetScale(1.0, 1.0)
		If ge.owningPlayerNo = 0 Then SetLineWidth(4.0) Else SetLineWidth(2.0)
		Local i:Int = 1
		For Local xy:TXY = EachIn ge.waypoints
			g.TranslateXY(xy.x, xy.y, tX, tY)
			SetColor(255, 255, 255)
			If lastX = Null Then
				lastX = tX
				lastY = tY
				startX = tX
				startY = tY
			Else
				DrawLine(lastX, lastY, tX, tY)
			End If
			RenderTarget(gfx, gd, g, lastX, lastY, tX, tY, i, s, 0, 0)
			lastX = tX
			lastY = tY
			i :+ 1
		Next
		SetColor(255, 255, 255)
		DrawLine(lastX, lastY, startX, startY)
		?debug
   			TProfiler.Leave("GameRender::ShowWaypoints")
  		?
	End Function
	
	Function ShowOrders(gfx:TGFX, ge:TGameEntity, gd:TGameData, g:TGameState, s:Double)
		?debug
   			TProfiler.Enter("GameRender::ShowOrders")
  		?
		Local lastX:Double = ge.tX, lastY:Double = ge.tY
		Local tX:Double, tY:Double
		Local i:Int = 1
		SetAlpha(0.75)
		SetScale(1.0, 1.0)
		If ge.owningPlayerNo = 0 Then SetLineWidth(2.0) Else SetLineWidth(1.0)
		If (ge.owningPlayerNo = 0 And ge.computerControlled = 0) Or (ge.owningPlayerNo = 0 And g.allowAIEnemySelection = 1) Or (ge.owningPlayerNo <> 0 And g.optionShowEnemyInfo = 1) Then 
			For Local o:TOrder = EachIn ge.orders
				Select o.t
				Case OrderHeading
					g.TranslateXY(o.x, o.y, tX, tY)
					SetColor(255, 0, 255)
					DrawLine(lastX, lastY, tX, tY)
					RenderTarget(gfx, gd, g, lastX, lastY, tX, tY, -1, s)
					i :+ 1
				Case OrderMove
					g.TranslateXY(o.x, o.y, tX, tY)
					SetColor(255, 255, 0)
					DrawLine(lastX, lastY, tX, tY)
					RenderTarget(gfx, gd, g, lastX, lastY, tX, tY, i, s)
					lastX = tX
					lastY = tY
					i :+ 1
				Case OrderPursue
					Local found:Int = 0
					If o.target.died = 0 Then
						found = 1
						If o.heading <> 0 Then
							Local aX:Double, aY:Double
							g.TranslateXY(o.x, o.y, aX, aY)
							SetColor(255, 144, 30)
							DrawLine(lastX, lastY, aX, aY)
							RenderTarget(gfx, gd, g, 0, 0, aX, aY, -1, s)
							g.TranslateXY(o.target.x, o.target.y, tX, tY)
						Else
							g.TranslateXY(o.target.x, o.target.y, tX, tY)
						End If
						If o.target.vessel.ship = 1 Then SetColor(30, 144, 255) Else SetColor(255, 228, 181)
						DrawLine(lastX, lastY, tX, tY)
						RenderTarget(gfx, gd, g, lastX, lastY, tX, tY, i, s)
						lastX = tX
						lastY = tY
						i :+ 1
					End If
				Case OrderFire
					If o.target = Null Then
						g.TranslateXY(o.x, o.y, tX, tY)
						SetColor(230, 80, 80)
						DrawLine(lastX, lastY, tX, tY)
						RenderTarget(gfx, gd, g, lastX, lastY, tX, tY, i, s)
						lastX = tX
						lastY = tY
						i :+ 1
					ElseIf o.target.died = 0 Then
						g.TranslateXY(o.target.x, o.target.y, tX, tY)
						SetColor(230, 80, 80)
						DrawLine(lastX, lastY, tX, tY)
						RenderTarget(gfx, gd, g, lastX, lastY, tX, tY, i, s)
						lastX = tX
						lastY = tY
						i :+ 1
					End If
				Case OrderAccelerate
					Exit			
				End Select
			Next
		End If
		?debug
   			TProfiler.Leave("GameRender::ShowOrders")
  		?
	End Function
	
	Function RenderTarget(gfx:TGFX, gd:TGameData, g:TGameState, pX:Double, pY:Double, x:Double, y:Double, i:Int, s:Double, t:Int = 0, ignoreStart:Int = 1)
		?debug
   			TProfiler.Enter("GameRender::RenderTarget")
  		?
		If pX = x And pY = y And ignoreStart = 1 Then Return
		SetColor(255, 255, 255)
		SetAlpha(1.0)
		SetRotation(gd.sf.r * 500.0)
		SetScale(s / 64.0, s / 64.0)
		If t = 0 Then DrawImage(gd.spinner, x, y) Else DrawImage(gd.spinner2, x, y)
		SetScale(1.0, 1.0)
		SetRotation(0)
		If i <> -1 Then 
			Local size:Double = TGFX.FontMediumSmallSize * s
			If size > 100 Then size = 100.0
			gfx.SetSpecificFontSize(size)
			Local w:Int = gfx.GetCachedFontWidth(String(i))
			Local h:Int = gfx.GetCachedFontHeight(String(i))
			DrawText(String(i), x - (w /2), y - h - 8)
		End If
		?debug
   			TProfiler.Leave("GameRender::RenderTarget")
  		?
	End Function

	Function RenderObjects(gd:TGameData, g:TGameState, gfx:TGFX, entities:TList, hoveringObject:TGameScenery, selectedObject:TGameScenery, s:Double, missionBuilder:Int)
		?debug
   			TProfiler.Enter("GameRender::RenderObjects")
  		?
		For Local ge:TGameScenery = EachIn entities
			Local size:Double = TGFX.FontMediumSize * s
			If size > 100 Then size = 100.0
			gfx.SetSpecificFontSize(size)

			' Selection alpha
			If missionbuilder = 1 Then
				If selectedObject = ge Then SetAlpha(1.0) ElseIf hoveringObject = ge Then SetAlpha(0.9) Else SetAlpha(0.8)
			Else 
				If g.cinematicMode = 1 Then SetAlpha(1.0) Else SetAlpha(0.5)
			End If

			' Render planet
			Select ge.t
			Case TGameScenery.TypePlanet
				SetColor(104, 104, 104)
				SetScale((ge.size / g.scale) / 1024, (ge.size / g.scale) / 1024)
				If missionBuilder = 0 Then SetRotation(ge.angle + g.rotate + (gd.sf.r)) Else SetRotation(ge.angle + g.rotate)
				DrawImage(gd.planets[ge.objectType], ge.tX, ge.tY)
			Case TGameScenery.TypeAsteroid
				SetColor(60, 60, 60)
				SetScale((ge.size / g.scale) / 512, (ge.size / g.scale) / 512)
				If missionBuilder = 0 Then SetRotation(ge.angle + g.rotate + (gd.sf.r * ge.rotVel)) Else SetRotation(ge.angle + g.rotate)
				DrawImage(gd.asteroids[ge.objectType], ge.tX, ge.tY)
			End Select
			
			' Bounding box
			SetColor(255, 255, 255)
			SetRotation(0)
			SetAlpha(1.0)
			SetScale(1.0, 1.0)
			If ge = selectedObject Then
				Local v:Double = ((ge.size / g.scale) / 2.0) * 0.85
				BoundingBoxObject(ge, v, 1.0)
			End If
			
			' Label
			Local w:Int = gfx.GetCachedFontWidth(ge.name)
			Local h:Int = gfx.GetCachedFontHeight(ge.name)
			SetColor(255, 255, 255)
			DrawText(ge.name, Int(ge.tX - (w / 2)), Int(ge.tY - ((ge.size / g.scale) / 2.0) - h))
		Next
		?debug
   			TProfiler.Leave("GameRender::RenderObjects")
  		?
	End Function
	
	Function RenderDeadProjectiles(gd:TGameData, g:TGameState, gfx:TGFX, entities:TList, minS:Double, s:Double, adjust:Double, ms:Long)
		?debug
   			TProfiler.Enter("GameRender::RenderDeadProjectiles")
  		?
		SetRotation(0)
		For Local ge:TGameEntity = EachIn entities
			Local s2:Double = ge.w.blastRadius / g.scale / adjust
			Local a:Double = ge.w.damage / 50.0
			If a < 0.5 Then a = 0.5
			If a > 1.0 Then a = 1.0
			SetAlpha(a)
			SetColor(255, 255, 255)
			SetScale(s2 / 32, s2 / 32)
			Local frame:Int = (ms - ge.died) / 25
			If frame < gd.explosionSizes[ge.w.explosionType] Then 
				DrawImage(gd.explosions[ge.w.explosionType], ge.tX, ge.tY, frame)
			End If
			SetScale(1.0, 1.0)
			SetAlpha(1.0)
		Next	
		?debug
   			TProfiler.Leave("GameRender::RenderDeadProjectiles")
  		?
	End Function

	Function BoundingBox(ge:TGameEntity, vSize:Double, width:Double)
		?debug
   			TProfiler.Enter("GameRender::BoundingBox")
  		?
		Local spacer:Double = vSize / 4
		SetLineWidth(width)
		DrawLine(ge.tX - vSize - spacer, ge.tY - vSize - spacer, ge.tX - vSize + spacer, ge.tY - vSize - spacer)
		DrawLine(ge.tX - vSize - spacer, ge.tY - vSize - spacer, ge.tX - vSize - spacer, ge.tY - vSize + spacer)
		DrawLine(ge.tX - vSize - spacer, ge.tY + vSize + spacer, ge.tX - vSize + spacer, ge.tY + vSize + spacer)
		DrawLine(ge.tX - vSize - spacer, ge.tY + vSize + spacer, ge.tX - vSize - spacer, ge.tY + vSize - spacer)
		DrawLine(ge.tX + vSize + spacer, ge.tY - vSize - spacer, ge.tX + vSize - spacer, ge.tY - vSize - spacer)
		DrawLine(ge.tX + vSize + spacer, ge.tY - vSize - spacer, ge.tX + vSize + spacer, ge.tY - vSize + spacer)
		DrawLine(ge.tX + vSize + spacer, ge.tY + vSize + spacer, ge.tX + vSize - spacer, ge.tY + vSize + spacer)
		DrawLine(ge.tX + vSize + spacer, ge.tY + vSize + spacer, ge.tX + vSize + spacer, ge.tY + vSize - spacer)
		SetLineWidth(1.0)
		?debug
   			TProfiler.Leave("GameRender::BoundingBox")
  		?
	End Function
	
	Function BoundingBoxObject(ge:TGameScenery, vSize:Double, width:Double)
		?debug
   			TProfiler.Enter("GameRender::BoundingBoxObject")
  		?
		Local spacer:Double = vSize / 4
		SetLineWidth(width)
		DrawLine(ge.tX - vSize - spacer, ge.tY - vSize - spacer, ge.tX - vSize + spacer, ge.tY - vSize - spacer)
		DrawLine(ge.tX - vSize - spacer, ge.tY - vSize - spacer, ge.tX - vSize - spacer, ge.tY - vSize + spacer)
		DrawLine(ge.tX - vSize - spacer, ge.tY + vSize + spacer, ge.tX - vSize + spacer, ge.tY + vSize + spacer)
		DrawLine(ge.tX - vSize - spacer, ge.tY + vSize + spacer, ge.tX - vSize - spacer, ge.tY + vSize - spacer)
		DrawLine(ge.tX + vSize + spacer, ge.tY - vSize - spacer, ge.tX + vSize - spacer, ge.tY - vSize - spacer)
		DrawLine(ge.tX + vSize + spacer, ge.tY - vSize - spacer, ge.tX + vSize + spacer, ge.tY - vSize + spacer)
		DrawLine(ge.tX + vSize + spacer, ge.tY + vSize + spacer, ge.tX + vSize - spacer, ge.tY + vSize + spacer)
		DrawLine(ge.tX + vSize + spacer, ge.tY + vSize + spacer, ge.tX + vSize + spacer, ge.tY + vSize - spacer)
		SetLineWidth(1.0)
		?debug
   			TProfiler.Leave("GameRender::BoundingBoxObject")
  		?
	End Function

	Function TranslateEntities(g:TGameState)
		?debug
   			TProfiler.Enter("GameRender::TranslateEntities")
  		?
		For Local player:Int = 0 To 1
			For Local ge:TGameEntity = EachIn g.entities[player]
				g.TranslateXY(ge.x, ge.y, ge.tX, ge.tY)
			Next
			For Local ge:TGameEntity = EachIn g.entitiesProjectiles[player]
				g.TranslateXY(ge.x, ge.y, ge.tX, ge.tY)
			Next
		Next
		For Local ge:TGameEntity = EachIn g.entitiesDead
			g.TranslateXY(ge.x, ge.y, ge.tX, ge.tY)
		Next
		For Local ge:TGameEntity = EachIn g.entitiesProjectilesDead
			g.TranslateXY(ge.x, ge.y, ge.tX, ge.tY)
		Next
		For Local ge:TGameScenery = EachIn g.entitiesObjects
			g.TranslateXY(ge.x, ge.y, ge.tX, ge.tY)
		Next
		?debug
   			TProfiler.Leave("GameRender::TranslateEntities")
  		?
	End Function
	
	Function VesselRadar(gfx:TGFX, g:TGameState, missionBuilder:Int, colours:TColour[], radar:TRadar)
		?debug
   			TProfiler.Enter("GameRender::VesselRadar")
  		?
		radar.Render(g, missionBuilder)
		?debug
   			TProfiler.Leave("GameRender::VesselRadar")
  		?
	End Function

	Function SetupMapView(gfx:TGFX, gd:TGameData, g:TGameState, missionBuilder:Int)
		?debug
   			TProfiler.Enter("GameRender::SetupMapView")
  		?
		' Size
		g.ratioX = g.worldSizeX / g.mapSectionSize
		g.ratioY = g.worldSizeY / g.mapSectionSize
		g.sizeX = (gfx.width - 50.0) / g.ratioX
		If missionBuilder = 1 Then
			g.sizeY = (gfx.height - 50.0 - gd.ToolbarHeight) / g.ratioY
		Else
			g.sizeY = (gfx.height - 50.0) / g.ratioY
		End If
		g.size = Min(g.sizeX, g.sizeY)
		g.mapViewCentreX = (gfx.width / 2)
		If missionBuilder = 1 Then
			g.mapViewCentreY = (gfx.height / 2) + (gd.ToolbarHeight / 2)
		Else
			g.mapViewCentreY = (gfx.height / 2)
		End If
		SetOrigin(g.mapViewCentreX, g.mapViewCentreY)
		
		' Set strategic scale
		g.strategicScale = g.mapSectionSize / g.size
		g.ConfigureZoom()
		?debug
   			TProfiler.Leave("GameRender::SetupMapView")
  		?
	End Function
	
	Function MapView(gfx:TGFX, g:TGameState, s:Double)
		?debug
   			TProfiler.Enter("GameRender::MapView")
  		?
		SetOrigin(g.mapViewCentreX, g.mapViewCentreY)
		SetBlend(ALPHABLEND)
		SetColor(0, 255, 0)
		SetLineWidth(1.0)
		SetAlpha(0.15)

		' Grid
		Local tX:Double, tY:Double
		Local x1:Double, x2:Double, y1:Double, y2:Double, cX:Double, cY:Double
		g.TranslateXY((-g.worldSizeX / 2), 0, x1, tY)
		g.TranslateXY((g.worldSizeX / 2), 0, x2, tY)
		g.TranslateXY(0, (-g.worldSizeY / 2), tX, y1)
		g.TranslateXY(0, (g.worldSizeY / 2), tX, y2)
		g.TranslateXY(0, 0, cX, cY)
		gfx.SetFontSize(TGFX.FontSmall)
		Local interval:Int = 8
		If g.scale < (g.strategicScale / 8.0) Then 
			interval = 1
		ElseIf g.scale < (g.strategicScale / 4.0) Then 
			interval = 2
		ElseIf g.scale < (g.strategicScale / 2.0) Then 
			interval = 4
		End If
'		Print g.scale < (g.strategicScale / 8.0)
		For Local i:Int = 0 To g.ratioX * 4
			Local x:Double = (i - (g.ratioX  * 2)) * g.mapSectionSize / 4.0
			g.TranslateXY(x, 0, tX, tY)
			If i Mod 4 = 0 Then 
				SetLineWidth(2.0)
				DrawLine(tX, y1, tX, y2)			
			ElseIf g.scale < (g.strategicScale / 4.0) Then 
				SetLineWidth(1.0)
				DrawLine(tX, y1, tX, y2)			
			End If
			If i Mod interval = 0 Then
				SetAlpha(0.5)
				SetColor(255, 255, 255)
				Local l:String = String(Long((Double(i) / 4.0 - (g.ratioX / 2.0)) * g.mapSectionSize)) + "m"
				Local w:Int = gfx.GetCachedFontWidth(l)
				Local h:Int = gfx.GetCachedFontHeight(l)
				DrawText(l, Int(tX - w / 2), Int(cY))
				SetColor(0, 255, 0)
				SetAlpha(0.15)
			End If
		Next
		For Local i:Int = 0 To g.ratioY * 4
			Local y:Double = (i - (g.ratioY * 2)) * g.mapSectionSize / 4.0
			g.TranslateXY(0, y, tX, tY)
			If i Mod 4 = 0 Then 
				SetLineWidth(2.0)
				DrawLine(x1, tY, x2, tY)
			ElseIf g.scale < (g.strategicScale / 4.0) Then 
				SetLineWidth(1.0)
				DrawLine(x1, tY, x2, tY)
			End If
			If i Mod interval = 0 And (i <> g.ratioY * 2) Then
				SetAlpha(0.5)
				SetColor(255, 255, 255)
				Local l:String = String(Long((Double(i) / 4.0 - (g.ratioY / 2.0)) * g.mapSectionSize)) + "m"
				Local w:Int = gfx.GetCachedFontWidth(l)
				Local h:Int = gfx.GetCachedFontHeight(l)
				DrawText(l, Int(cX), Int(tY - (h / 2)))
				SetColor(0, 255, 0)
				SetAlpha(0.15)
			End If
		Next 
		SetLineWidth(2.0)
		DrawLine(x1, y1, x2, y1)
		DrawLine(x1, y2, x2, y2)
		DrawLine(x1, y1, x1, y2)
		DrawLine(x2, y1, x2, y2)
		DrawLine(x1, cY, x2, cY) 
		DrawLine(cX, y1, cX, y2) 
		SetLineWidth(1.0)
			
		SetOrigin(0, 0)
		SetAlpha(1.0)
		?debug
   			TProfiler.Leave("GameRender::MapView")
  		?
	End Function
	
End Type
