SuperStrict
Import "Colour.bmx"
Import "Helper.bmx"
Import "GameEntity.bmx"
Import "GameState.bmx"
Import "Profiler.bmx"

Type TRadar
	Const radarSize:Float = 32.0
	Field g:TGameState, radarSteps:Int, radar1:Int[,], radar2:Int[,], blockSize:Double, width:Int, height:Int
	Field sizeX:Int[], sizeY:Int[], pattern:Int[,,], m:Int
	Field img1:TImage, img2:TImage, img12:TImage
	
	Function Create:TRadar(g:TGameState, colours:TColour[])
		Local o:TRadar = New TRadar
		o.g = g
		o.radarSteps = 4' * Int(g.mapSectionSize / 2500)
		o.width = g.ratioX * o.radarSteps
		o.height = g.ratioY * o.radarSteps
		o.radar1 = New Int[o.width, o.height]
		o.radar2 = New Int[o.width, o.height]
		o.blockSize = g.mapSectionSize / o.radarSteps
		o.PreCalcPatterns()
		
		' Pre-render radar blocks
		o.img1 = CreateImage(radarSize, radarSize, DYNAMICIMAGE|MASKEDIMAGE|FILTEREDIMAGE)
		o.img2 = CreateImage(radarSize, radarSize, DYNAMICIMAGE|MASKEDIMAGE|FILTEREDIMAGE)
		o.img12 = CreateImage(radarSize, radarSize, DYNAMICIMAGE|MASKEDIMAGE|FILTEREDIMAGE)
		SetClsColor(0, 0, 0)
		Cls
		SetPlayerColour(0, colours)
		SetOrigin(0, 0)
		DrawRect(0, 0, radarSize, radarSize)
		GrabImage(o.img1, 0, 0)
		Cls
		SetPlayerColour(1, colours)
		SetOrigin(0, 0)
		DrawRect(0, 0, radarSize, radarSize)
		GrabImage(o.img2, 0, 0)
		Cls
		SetPlayerColour(0, colours)
		DrawPoly([0.0, 0.0, 0.0, radarSize, radarSize, radarSize])
		SetPlayerColour(1, colours)
		DrawPoly([0.0, 0.0, radarSize, 0.0, radarSize, radarSize])
		GrabImage(o.img12, 0, 0)
		Cls

		Return o
	End Function
	
	'1290097 = 117281.547
	Method Clear()
		?debug
   			TProfiler.Enter("Radar::Clear")
  		?
		MemClear(radar1, SizeOf(radar1))
		MemClear(radar2, SizeOf(radar2))
		?debug
   			TProfiler.Leave("Radar::Clear")
  		?
	End Method
	
	Method Render(g:TGameState, missionBuilder:Int)
		?debug
   			TProfiler.Enter("Radar::Render")
  		?
		Local x1:Double, y1:Double, x2:Double, y2:Double
		Local xC:Double, yC:Double
		Local oX:Double = -g.worldSizeX / 2
		Local oY:Double = -g.worldSizeY / 2
		Local bS:Double = blockSize / g.scale
		SetAlpha(0.35)
		SetScale(bS / radarSize, bS / radarSize)
		SetColor(255, 255, 255)
		For Local y:Int = 0 To height - 1
			For Local x:Int = 0 To width - 1
				g.TranslateXY(oX + (x * blockSize) + (blockSize / 2), oY + (y * blockSize) + (blockSize / 2), xC, yC)
				If radar1[x, y] > 0 And radar2[x, y] > 0 And (g.optionShowEnemyInfo = 1 Or missionBuilder = 1) Then
					DrawImage(img12, xC, yC)
				ElseIf radar1[x, y] > 0 Then
					DrawImage(img1, xC, yC)
				ElseIf radar2[x, y] > 0 And (g.optionShowEnemyInfo = 1 Or missionBuilder = 1) Then
					DrawImage(img2, xC, yC)
				End If
			Next
		Next
		SetAlpha(1.0)
		?debug
   			TProfiler.Leave("Radar::Render")
  		?
	End Method
	
	Method PreCalcPatterns()
		m = (200000 / 2500) * radarSteps
		sizeX = New Int[3]
		sizeY = New Int[3]
		pattern = New Int[3, m, m]
		PreCalc(0, 5000.0)
		PreCalc(1, 25000.0)
		PreCalc(2, 100000.0)
	End Method
	
	Method PreCalc(i:Int, radar:Double)
		Local mb:Int = Int((radar * 2) / blockSize)
		For Local y:Int = 0 To mb - 1
			Local bY:Int = (y - (mb / 2))
			Local pY:Double = (Double(bY) + 0.5) * blockSize
			Local cY:Int = bY + (m / 2)
			For Local x:Int = 0 To mb - 1
				Local bX:Int = (x - (mb / 2))
				Local pX:Double = (Double(bX) + 0.5) * blockSize
					
				' Is this covered?
				If DistanceIsLess(0, 0, pX, pY, radar) Then
					Local cX:Int = bX + (m / 2)
					If cX >= 0 And cX < m And cY >= 0 And cY < m Then
						pattern[i, x, y] = 1
					End If
				End If
			Next
		Next
	End Method

	Method CalcRadar()
		?debug
   			TProfiler.Enter("Radar::CalcRadar")
  		?
		For Local player:Int = 0 To 1
			For Local ge:TGameEntity = EachIn g.entities[player]
				Local i:Int = 0
				Select ge.radar
				Case 5000.0
					i = 0
				Case 25000.0
					i = 1
				Case 100000.0
					i = 2
				Default
					Print "Unsupported radar range: " + ge.radar
					End
				End Select
				Local mb:Int = Int((ge.radar * 2) / blockSize)
				Local xC:Int = Int(ge.x / blockSize) - (mb / 2) + (width / 2)
				Local yC:Int = Int(ge.y / blockSize) - (mb / 2) + (height / 2)
				For Local y:Int = 0 To mb - 1
					Local yP:Int = (yC + y)
					For Local x:Int = 0 To mb - 1
						Local xP:Int = (xC + x)
						If xP >= 0 And xP < width And yP >= 0 And yP < height And pattern[i, x, y] = 1 Then
							Select ge.owningPlayerNo
							Case 0
								radar1[xP, yP] :+ 1
							Case 1
								radar2[xP, yP] :+ 1
							End Select
						End If
					Next
				Next
			Next
		Next
		?debug
   			TProfiler.Leave("Radar::CalcRadar")
  		?
	End Method
	
	Method SetVisible(missionBuilder:Int)
		?debug
   			TProfiler.Enter("Radar::SetVisible")
  		?

		' Clear painted status
		For Local player:Int = 0 To 1
			For Local ge:TGameEntity = EachIn g.entities[player]
				ge.targetPainted = 0
				If missionBuilder = 1 Then 
					ge.visible = 1
					Continue
				End If
				If ge.owningPlayerNo = 0 Then ge.visible = 1 Else ge.visible = 0
				Local bX:Int = (ge.x - (blockSize / 2)) / blockSize
				Local bY:Int = (ge.y - (blockSize / 2)) / blockSize
				If bX + (width / 2) < 0 Or bX + (width / 2) >= width Or bY + (height / 2) < 0 Or bY + (height / 2) >= height Then Continue
				Select ge.owningPlayerNo
				Case 0
					If radar2[bX + (width / 2), bY + (height / 2)] > 0 Then 
						If ge.targetable = 1 Then ge.targetPainted = 1
					End If
				Case 1
					If radar1[bX + (width / 2), bY + (height / 2)] > 0 Then 
						If ge.targetable = 1 Then ge.targetPainted = 1
						ge.visible = 1
					End If
				End Select
			Next
			For Local ge:TGameEntity = EachIn g.entitiesProjectiles[player]
				ge.targetPainted = 0
				If missionBuilder = 1 Then 
					ge.visible = 1
					Return
				End If
				If ge.owningPlayerNo = 0 Then ge.visible = 1 Else ge.visible = 0
				Local bX:Int = (ge.x - (blockSize / 2)) / blockSize
				Local bY:Int = (ge.y - (blockSize / 2)) / blockSize
				If bX + (width / 2) < 0 Or bX + (width / 2) >= width Or bY + (height / 2) < 0 Or bY + (height / 2) >= height Then Continue
				Select ge.owningPlayerNo
				Case 0
					If radar2[bX + (width / 2), bY + (height / 2)] > 0 Then 
						If ge.targetable = 1 Then ge.targetPainted = 1
					End If
				Case 1
					If radar1[bX + (width / 2), bY + (height / 2)] > 0 Then 
						If ge.targetable = 1 Then ge.targetPainted = 1
						ge.visible = 1
					End If
				End Select		
			Next
		Next
		
		?debug
   			TProfiler.Leave("Radar::SetVisible")
  		?
	End Method

End Type
 