Type TMiniMap

	Function MiniMap(gfx:TGFX, gd:TGameData, g:TGameState)
		Local minimapHeight:Int = gd.MiniMapWidth * (g.worldSizeY / g.worldSizeX)
		SetAlpha(0.75)
		SetColor(255, 255, 255)
		DrawRect(gfx.width - 6 - gd.MiniMapWidth, gfx.height - minimapHeight - 6, gd.MiniMapWidth + 2, minimapHeight + 2)
		SetAlpha(1.0)
		SetColor(0, 0, 32)
		DrawRect(gfx.width - 5 - gd.MiniMapWidth, gfx.height - minimapHeight - 5, gd.MiniMapWidth, minimapHeight)
	End Function 
	
	Function MiniMapData(gfx:TGFX, gd:TGameData, g:TGameState)
		Local minimapHeight:Int = gd.MiniMapWidth * (g.worldSizeY / g.worldSizeX)
		Local minimapScale:Double = g.worldSizeX / (gd.OverlayWidth - 10)
		SetViewport(gfx.width - 5 - gd.MiniMapWidth, gfx.height - minimapHeight - 5, gd.MiniMapWidth, minimapHeight)
		SetAlpha(1.0)
		SetColor(255, 255, 255)
		For Local ge:TGameScenery = EachIn g.entitiesObjects
			Local x:Double = (ge.x / g.worldSizeX) * gd.MiniMapWidth
			Local y:Double = (ge.y / g.worldSizeY) * minimapHeight
			SetScale((ge.size / minimapScale) / 1024, (ge.size / minimapScale) / 1024)
			Select ge.t
			Case TGameScenery.TypePlanet
				SetAlpha(0.4)
				DrawImage(gd.planets[ge.objectType], gfx.width - gd.MiniMapWidth - 5 + x + (gd.MiniMapWidth / 2), gfx.height - (minimapHeight / 2) - 5 - y)
				SetAlpha(1.0)
			End Select
			SetScale(1.0, 1.0)
		Next
		For Local player:Int = 0 To 1
			For Local ge:TGameEntity = EachIn g.entities[player]
				If ge.visible = 1 Then
					Local x:Double = (ge.x / g.worldSizeX) * gd.MiniMapWidth
					Local y:Double = (ge.y / g.worldSizeY) * minimapHeight
					SetPlayerColour(ge.owningPlayerNo, gd.fleetColours)
					DrawRect(gfx.width - gd.MiniMapWidth - 5 + x + (gd.MiniMapWidth / 2) - 2, gfx.height - (minimapHeight / 2) - 5 - y - 2, 4, 4) 
				End If
			Next
		Next
		SetViewport(0, 0, gfx.width, gfx.height)
	End Function

End Type
