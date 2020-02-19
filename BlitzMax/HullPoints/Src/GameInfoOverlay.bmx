SuperStrict
Import "GameEntity.bmx"
Import "GameState.bmx"
Import "GFX.bmx"
Import "Profiler.bmx"
Import "ScriptItem.bmx"
Import "Vessel.bmx"

Type TGameInfoOverlay

	Function UIOverlay(gfx:TGFX, gd:TGameData, g:TGameState, selectedVessel:TGameEntity, missionBuilder:Int, top:Int)
		If selectedVessel = Null Then Return
		?debug
  			TProfiler.Enter("GameInfoOverlay::UIOverlay")
 		?
		Local vessel:TVessel = selectedVessel.vessel

		' Info
		SetAlpha(1.0)
		SetOrigin(5, top + 5)
		Local orderY:Int = 0
		If vessel.ship = 1 Then
			SetColor(255, 255, 0)
			gfx.SetFontSize(TGFX.FontMedium)
			DrawText("Vessel Info:", 0, 0)
			gfx.SetFontSize(TGFX.FontMediumSmall)
			SetColor(200, 200, 200)
			If selectedVessel.name = vessel.name Then
				DrawText("Name: ", 0, 20)
			Else
				DrawText("Name/Type: ", 0, 20)
			End If
			DrawText("Position: ", 0, 35)
			DrawText("Heading: ", 0, 50)
			DrawText("Speed: ", 0, 65)
			DrawText("Mass: ", 0, 80)
			DrawText("Max. Speed: ", 0, 95)
			DrawText("Rotation: ", 0, 110)
			DrawText("Hull: ", 0, 125)
			DrawText("Shield: ", 0, 140)
			DrawText("Power: ", 0, 155)
			SetColor(0, 255, 0)
			If selectedVessel.name = vessel.name Then
				DrawText(selectedVessel.name, 70, 20)
			Else
				DrawText(selectedVessel.name + "/" + vessel.name, 70, 20)
			End If
			DrawText(RoundDoubleThousand(selectedVessel.x, 1) + ", " + RoundDoubleThousand(selectedVessel.y, 1), 70, 35)
			DrawText(Int(AdjustAngle(selectedVessel.angle + 90)) + "/" + Int(AdjustAngle(selectedVessel.targetAngle + 90)) + " deg", 70, 50)
			DrawText(Int(selectedVessel.currentSpeed) +  "/" + Int(selectedVessel.targetSpeed) + " m/s", 70, 65)
			DrawText(selectedVessel.mass + " tons", 70, 80)
			DrawText(Int(selectedVessel.speed) + " m/s", 70, 95)
			DrawText(RoundDouble(selectedVessel.dps, 1) + " dps", 70, 110)
			DrawText(Int(selectedVessel.armourRemaining) + "/" + Int(selectedVessel.armour), 70, 125)
			DrawText(Int(selectedVessel.shieldRemaining) + "/" + Int(selectedVessel.shield), 70, 140)
			If selectedVessel.pwrOut > selectedVessel.pwrIn Then SetColor(255, 0, 0) Else SetColor(0, 255, 0)
			DrawText(selectedVessel.pwrOut + "/" + selectedVessel.pwrIn + "MW", 70, 155)
			Local t2:Int = 0
			If missionBuilder = 1 Then 
				SetColor(255, 255, 0)
				gfx.SetFontSize(TGFX.FontMedium)
				DrawText("Personality:", 0, 180)
				gfx.SetFontSize(TGFX.FontMediumSmall)
				SetColor(200, 200, 200)
				DrawText("Controller: ", 0, 200)
				If selectedVessel.computerControlled = 0 Then 
					SetColor(0, 255, 0)
					DrawText("Player", 70, 200)
					gd.buttons.AddButtonMS("Set AI Controlled", 1, 0, top + 215, 150, "ComputerControlledOn")
					t2 = 240
				Else
					SetColor(0, 255, 0)
					DrawText("AI", 70, 200)
					gd.buttons.AddButtonMS("Set Player Controlled", 2, 0, top + 215, 150, "ComputerControlledOff")
					SetColor(200, 200, 200)
					DrawText("Class: ", 0, 240)
					SetColor(0, 255, 0)
					DrawText(TAI.ReturnAIProfileName(selectedVessel.ai.personality), 70, 240)
					gd.buttons.AddButtonMS("Set AI Personality Class", 6, 0, top + 255, 150, "SetAIPersonality")
					If selectedVessel.ai.personality = TAI.ProfilePatrol Then
						SetColor(200, 200, 200)
						DrawText("Waypoints: ", 0, 280)
						SetColor(0, 255, 0)
						If selectedVessel.ai.ignoreStartingWaypoint = 1 Then
							gd.buttons.AddButtonMS("Include Start Point", 2, 0, top + 295, 150, "IncludeStartingWaypoint")
						Else
							gd.buttons.AddButtonMS("Ignore Start Point", 1, 0, top + 295, 150, "IgnoreStartingWaypoint")
						End If
						If selectedVessel.waypoints.Count() = 0 Then
							DrawText("None", 70, 280)
							gd.buttons.AddButtonMS("Add Waypoint", 1, 0, top + 320, 150, "AddWaypoint")
						Else
							DrawText(selectedVessel.waypoints.Count() + " waypoints", 70, 280)
							gd.buttons.AddButtonMS("Clear Waypoints", 2, 0, top + 320, 150, "ClearWaypoints")
							gd.buttons.AddButtonMS("Add Waypoint", 1, 0, top + 345, 150, "AddWaypoint")
						End If
						t2 = 370
					ElseIf selectedVessel.ai.personality = TAI.ProfileEscort Then
						If selectedVessel.ai.escortID = -1 Then
							gd.buttons.AddButtonMS("Set Escorted Vessel", 1, 0, top + 280, 150, "SetEscort")
						Else
							gd.buttons.AddButtonMS("Clear Escorted Vessel", 2, 0, top + 280, 150, "ClearEscort")
						End If
						t2 = 305
					Else
						t2 = 280
					End If
				End If
				t2 :+ 10
				SetColor(255, 255, 0)
				gfx.SetFontSize(TGFX.FontMedium)
				DrawText("Script:", 0, t2)
				gfx.SetFontSize(TGFX.FontMediumSmall)
				t2 :+ 20
				gd.buttons.AddButtonMS("Add Scripted Action", 1, 0, top + t2, 150, "AddScriptedAction")
				If selectedVessel.script.Count() > 0 Then
					t2 :+ 25
					gd.buttons.AddButtonMS("Clear Last Action", 2, 0, top + t2, 150, "ClearLastScriptAction")
					t2 :+ 25
					gd.buttons.AddButtonMS("Clear Script", 2, 0, top + t2, 150, "ClearScript")
				End If
				t2 :+ 25
				For Local sc:TScriptItem = EachIn selectedVessel.script
					Select sc.t
					Case TScriptItem.ScriptJumpIn
						SetColor(200, 200, 200)
						DrawText("Jump In: ", 0, t2)
						SetColor(0, 255, 0)
						DrawText(sc.time + " seconds", 70, t2)
					Case TScriptItem.ScriptJumpOut
						SetColor(200, 200, 200)
						DrawText("Jump Out: ", 0, t2)
						SetColor(0, 255, 0)
						DrawText(sc.time + " seconds", 70, t2)
					End Select
					t2 :+ 15
				Next
			Else
				SetColor(255, 255, 0)
				gfx.SetFontSize(TGFX.FontMedium)
				DrawText("Add Order:", 0, 180)
				gfx.SetFontSize(TGFX.FontMediumSmall)
				SetColor(200, 200, 200)
				gd.buttons.AddButtonMS("Add Fire Order", 0, 0, top + 200, 150, "FireOrder")
				gd.buttons.AddButtonMS("Add Heading Order", 1, 0, top + 225, 150, "HeadingOrder")
				gd.buttons.AddButtonMS("Add Move Order", 2, 0, top + 250, 150, "MoveOrder")
				gd.buttons.AddButtonMS("Add Escort Order", 3, 0, top + 275, 150, "EscortOrder")
				gd.buttons.AddButtonMS("Add Pursue Order", 4, 0, top + 300, 150, "ApproachOrder")
				orderY = 335
			End If
		Else
			SetColor(255, 255, 0)
			gfx.SetFontSize(TGFX.FontMedium)
			DrawText("Object Info:", 0, 0)
			gfx.SetFontSize(TGFX.FontMediumSmall)
			SetColor(200, 200, 200)
			DrawText("Type: ", 0, 15)
			DrawText("Position: ", 0, 30)
			DrawText("Heading: ", 0, 45)
			DrawText("Speed: ", 0, 60)
			DrawText("Max. Speed: ", 0, 75)
			DrawText("Rotation: ", 0, 90)
			SetColor(0, 255, 0)
			DrawText(vessel.name, 70, 15)
			DrawText(RoundDoubleThousand(selectedVessel.x, 1) + ", " + RoundDoubleThousand(selectedVessel.y, 1), 70, 30)
			DrawText(Int(AdjustAngle(selectedVessel.angle + 90)) + "/" + Int(AdjustAngle(selectedVessel.targetAngle + 90)) + " deg", 70, 45)
			DrawText(Int(selectedVessel.currentSpeed) +  "/" + Int(selectedVessel.targetSpeed) + " most/s", 70, 60)
			DrawText(Int(selectedVessel.speed) + " m/s", 70, 75)
			DrawText(RoundDouble(selectedVessel.dps, 1) + " dps", 70, 90)
			orderY = 105
		End If
		SetOrigin(0, 0)
		
		' Orders
		If missionBuilder = 1 Then 
			?debug
  				TProfiler.Leave("GameInfoOverlay::UIOverlay")
 			?
			Return
		End If
		SetOrigin(5, 0)
		Local i:Float = 0.0
		Local n:Int = 0
		SetColor(255, 255, 0)
		gfx.SetFontSize(TGFX.FontMedium)
		DrawText("Current Orders:", 0, orderY)
		gfx.SetFontSize(TGFX.FontMediumSmall)
		SetColor(200, 200, 200)
		orderY :+ 15
		If selectedVessel.orders.Count() > 0 Then
			If selectedVessel.ordersHeld = 1 Then
				If selectedVessel.currentSpeed = 0 Then 
					gd.buttons.AddButtonS("Unhold Orders", 0, 0, top + orderY - 5, 150, "UnholdOrders")
					orderY :+ 15
				End If
			Else
				gd.buttons.AddButtonS("Hold Orders", 0, 0, top + orderY - 5, 150, "HoldOrders")
				orderY :+ 15
			End If
		End If
		For Local o:TOrder = EachIn SelectedVessel.orders
			gfx.SetFontSize(TGFX.FontMediumSmall)
			DrawText(n + 1, 0, orderY + i)
			gd.buttons.AddButtonS("Cancel", 0, gd.OverlayWidth - 50, top + orderY - 3 + i, 50, "CancelOrder:" + String(n))
			Select o.t
			Case OrderHeading
				SetColor(255, 0, 255)
				DrawText("Heading", 15, orderY + i)
				SetColor(255, 255, 255)
				DrawText(RoundDouble(o.heading, 1) + " degrees", 15, orderY + i + 15)
			Case OrderPursue
				SetColor(30, 144, 255)
				If o.heading = 0 Then DrawText("Approach", 15, orderY + i) Else DrawText("Escort", 15, orderY + i)
				SetColor(255, 255, 255)
				Local found:Int = 0
				If o.target.died = 0 Then
					found = 1
					Local d:Double = DistanceBetweenPoints(selectedVessel.x, selectedVessel.y, o.target.x, o.target.y)
					Local time:Double = (d / selectedVessel.currentSpeed)
					Local t:String = ""
					If time < (60 * 60) Then t = " - " + String(Long(time)) + " seconds" Else t = ""
					DrawText("Distance: " + Int(d) + "/" + Int(o.distance) + "m", 15, orderY + i + 15)
					i :+ 15
					DrawText("Time: " + t, 15, orderY + i + 15)
				End If
				If found = 0 Then DrawText("No Target", 15, orderY + i + 15)
			Case OrderMove
				SetColor(255, 255, 0)
				DrawText("Move", 15, orderY + i)
				SetColor(255, 255, 255)
				Local d:Double = DistanceBetweenPoints(selectedVessel.x, selectedVessel.y, o.x, o.y)
				Local time:Double = (d / selectedVessel.currentSpeed)
				Local t:String = ""
				If time < (60 * 60) Then t = " - " + String(Long(time)) + " seconds" Else t = ""
				DrawText(RoundDoubleThousand(o.x, 1) + ", " + RoundDoubleThousand(o.y, 1), 15, orderY + i + 15)
				DrawText("Distance: " + Long(d) + " m", 15, orderY + i + 30)
				DrawText("Time: " + t, 15, orderY + i + 45)
				i :+ 30
			Case OrderFire
				SetColor(0, 96, 255)
				DrawText("Fire on Target", 15, orderY + i)
				SetColor(255, 255, 255)
				Local found:Int = 0
				If o.target = Null Then
					DrawText(RoundDoubleThousand(o.x, 1) + ", " + RoundDoubleThousand(o.y, 1), 15, orderY + 15 + i)
				Else
					If o.target.died = 0 Then
						found = 1
						Local name:String = o.target.vessel.name 
						Local level:String = o.GetLevel()
						Local rate:String = o.GetRate()
						Local direction:String = o.GetDirection()
						If direction.Length > 0 Then direction = ", " + direction
						DrawText(level + direction, 15, orderY + i + 15)
						i :+ 15
						DrawText(rate, 15, orderY + i + 15)
						i :+ 15
						Local d:Double = DistanceBetweenPoints(selectedVessel.x, selectedVessel.y, o.target.x, o.target.y)
						DrawText("Range: " + Int(d) + " m", 15, orderY + i + 15)
					End If
					If found = 0 Then DrawText("No Target", 15, orderY + i + 15)
				End If
			End Select
			i :+ 30
			n :+ 1
		Next
		SetOrigin(0, 0)
		?debug
  			TProfiler.Leave("GameInfoOverlay::UIOverlay")
 		?
	End Function
	
End Type