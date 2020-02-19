SuperStrict
Import "Block.bmx"
Import "Helper.bmx"
Import "Piece.bmx"
Import "WeaponClass.bmx"
Import "XY.bmx"

Type TVessel
	Const DefaultRadarRange:Double = 5000.0
	Field name:String
	Field variantOf:String = ""
	Const MaxShapeX:Int = 8
	Const MaxShapeY:Int = 8
	Field shapeV:TBlock[,] = New TBlock[maxShapeX, maxShapeY]
	Field loadout:Int[]
	Field ship:Int = 1
	Field missile:Int = 0
	Field fighter:Int = 0
	Field missiles:TList = CreateList()
	Field guns:TList = CreateList()
	Field modules:TList = CreateList()
	Field thrusters:TList = CreateList()
	Field launchers:TList = CreateList()
	Field occupied:TList = CreateList()
	Field renderedImage:TImage
	Field firstX:Int = -1, firstY:Int = -1, lastX:Int = -1, lastY:Int = -1, centreX:Double = -1, centreY:Double = -1
		
	Function Create:TVessel()
		Local o:TVessel = New TVessel
		o.name = "(NEW)"
		o.loadout = New Int[TWeaponClass.NumberOfClasses]
		For Local i:Int = 0 To TWeaponClass.NumberOfClasses - 1
			o.loadout[i] = 0
		Next

		o.BuildShape()
		Return o
	End Function
	
	Method RealDimension:Int(firstX:Int Var, firstY:Int Var, lastX:Int Var, lastY:Int Var, width:Int Var, height:Int Var)
		firstX:Int = -1
		firstY:Int = -1
		lastX:Int = -1
		lastY:Int = -1
		For Local y:Int = 0 To MaxShapeY - 1
			For Local x:Int = 0 To MaxShapeX - 1
				Local s:TBlock = shapeV[x, y]
				If s.piece > 0 Then
					If x < firstX Or firstX = -1 Then firstX = x
					If x > lastX Or lastX = -1 Then lastX = x
					If y < firstY Or firstY = -1 Then firstY = y
					If y > lastY Or lastY = -1 Then lastY = y
				End If
			Next
		Next
		width = lastX - firstX + 1
		height = lastY - firstY + 1
		Return Max(width, height)
	End Method
	
	Method Render(pieces:TPiece[])
		Local size:Int = TPiece.Size / 4 '16
		SetOrigin(size / 2, size / 2)
		SetAlpha(1.0)
		SetClsColor(0, 0, 0)
		SetMaskColor(0, 0, 0)
		SetColor(255, 255, 255)
		Cls
		
		'Work out dimensions
		For Local y:Int = 0 To MaxShapeY - 1
			For Local x:Int = 0 To MaxShapeX - 1
				Local s:TBlock = shapeV[x, y]
				If s.piece > 0 Then
					If x < firstX Or firstX = -1 Then firstX = x
					If x > lastX Or lastX = -1 Then lastX = x
					If y < firstY Or firstY = -1 Then firstY = y
					If y > lastY Or lastY = -1 Then lastY = y
				End If
			Next
		Next

		' Render hull
		For Local y:Int = firstY To lastY
			For Local x:Int = firstX To lastX
				Local b:TBlock = shapeV[x, y]
				Local piece:TPiece = pieces[b.piece]
				TPiece.RenderPiece(pieces, size, b.piece, (x - firstX) * size, (y - firstY) * size, b.rot, b.variant)
			Next
		Next
		renderedImage = CreateImage((lastX - firstX + 1) * size, (lastY - firstY + 1) * size, 1, DYNAMICIMAGE|MASKEDIMAGE|FILTEREDIMAGE)
		GrabImage(renderedImage, 0, 0)		
	End Method
	
	Method LiveRender(pieces:TPiece[], xPos:Double, yPos:Double, a:Double, scale:Double)
	
		'Work out dimensions
		If firstX = -1 Then
			For Local y:Int = 0 To MaxShapeY - 1
				For Local x:Int = 0 To MaxShapeX - 1
					Local s:TBlock = shapeV[x, y]
					If s.piece > 0 Then
						If x < firstX Or firstX = -1 Then firstX = x
						If x > lastX Or lastX = -1 Then lastX = x
						If y < firstY Or firstY = -1 Then firstY = y
						If y > lastY Or lastY = -1 Then lastY = y
					End If
				Next
			Next
		End If
		If centreX = -1 Then
			centreX = (lastX - firstX) / 2.0
			centreY = (lastY - firstY) / 2.0
		End If

		' Draw
		scale :/ 52
		Local size:Double = TPiece.Size * scale
		
		' Rotation
		Local mX_X:Double = size, mX_Y:Double = 0
		RotateAroundOrigin(mX_X, mX_Y, a)
		Local mX_Xc:Int = mX_X, mX_Yc:Int = mX_Y
		Local mY_X:Double = 0, mY_Y:Double = size
		RotateAroundOrigin(mY_X, mY_Y, a)
		Local mY_Xc:Int = mY_X, mY_Yc:Int = mY_Y

		' Render
		SetAlpha(1.0)
		SetColor(255, 255, 255)
		SetScale(scale, scale)
		For Local y:Int = firstY To lastY
			For Local x:Int = firstX To lastX
				Local b:TBlock = shapeV[x, y]
				Local piece:TPiece = pieces[b.piece]
				
				' Calculate position
'				Local pX:Double = ((Double(x) - firstX - centreX) * size)
'				Local pY:Double = ((Double(y) - firstY - centreY) * size)
				Local pX:Double = ((x - firstX - centreX) * mX_Xc) + ((y - firstY - centreY) * mY_Xc)
				Local pY:Double = ((x - firstX - centreX) * mX_Yc) + ((y - firstY - centreY) * mY_Yc)
'				Local pX:Double = (Double(x - firstX - centreX) * mX_X) + (Double(y - firstY - centreY) * mY_X)
'				Local pY:Double = (Double(x - firstX - centreX) * mX_Y) + (Double(y - firstY - centreY) * mY_Y)
'				RotateAroundOrigin(pX, pY, a)
				TPiece.RenderPieceNoScale(pieces, b.piece, pX + xPos, pY + yPos, b.rot, b.variant, a)
			Next
		Next
		SetScale(1.0, 1.0)
	End Method
	
	Method BuildGunsMissilesModules(pieces:TPiece[])
		occupied = CreateList()
		modules = CreateList()
		guns = CreateList()
		missiles = CreateList()
		thrusters = CreateList()
		launchers = CreateList()
		For Local y:Int = 0 To maxShapeY - 1 
			For Local x:Int = 0 To maxShapeX - 1 
				Local s:TBlock = shapeV[x, y]
				Local p:TPiece = pieces[s.piece]
				If s.piece > 0 Then ListAddLast(occupied, TXY.Create(x, y))
				If p.isModule Then ListAddLast(modules, TXY.Create(x, y))
				If p.isGun Then ListAddLast(guns, TXY.Create(x, y))
				If p.isMissile Then ListAddLast(missiles, TXY.Create(x, y))
				If p.propulsion.Length > 0 And p.propulsion[0] > 0 Then ListAddLast(thrusters, TXY.Create(x, y))
				If p.isLauncher Then ListAddLast(launchers, TXY.Create(x, y))
			Next
		Next
	End Method

	Method BuildShape()
		shapeV = New TBlock[maxShapeX, maxShapeY]
		For Local y:Int = 0 To maxShapeY - 1 
			For Local x:Int = 0 To maxShapeX - 1 
				shapeV[x, y] = New TBlock
				shapeV[x, y].preferredAmmo1V = -1
				shapeV[x, y].preferredAmmo2V = -1
				shapeV[x, y].preferredAmmo3V = -1
				shapeV[x, y].strafe = 0
			Next
		Next 
		Clear()
	End Method

	Method Clear()	
		For Local y:Int = 0 To maxShapeY - 1 
			For Local x:Int = 0 To maxShapeX - 1 
				shapeV[x, y].piece = 0
				shapeV[x, y].rot = 0
				shapeV[x, y].variant = 0
			Next
		Next 
	End Method

	Method CentreBlueprint()
		'Work out dimensions
		Local firstX:Int = -1
		Local firstY:Int = -1
		Local lastX:Int = -1
		Local lastY:Int = -1
		For Local y:Int = 0 To MaxShapeY - 1
			For Local x:Int = 0 To MaxShapeX - 1
				Local s:TBlock = shapeV[x, y]
				If s.piece > 0 Then
					If x < firstX Or firstX = -1 Then firstX = x
					If x > lastX Or lastX = -1 Then lastX = x
					If y < firstY Or firstY = -1 Then firstY = y
					If y > lastY Or lastY = -1 Then lastY = y
				End If
			Next
		Next
		If firstX = -1 And firstY = - 1 And lastX = -1 And lastY = -1 Then Return
		
		' Now copy it
		Local newMaxX:Int = lastX - firstX + 1
		Local newMaxY:Int = lastY - firstY + 1
		Local newArray:TBlock[,] = New TBlock[newMaxX, newMaxY]
		For Local y:Int = 0 To newMaxY - 1
			For Local x:Int = 0 To newMaxX - 1
				newArray[x, y] = shapeV[x + firstX, y + firstY]
			Next
		Next
		
		' Compress
		BuildShape()
		Local padX:Int = Floor((maxShapeX - newMaxX) / 2)
		Local padY:Int = Floor((maxShapeY - newMaxY) / 2)
		For Local y:Int = 0 To newMaxY - 1
			For Local x:Int = 0 To newMaxX - 1
				shapeV[x + padX, y + padY] = newArray[x, y]
			Next
		Next
	End Method

	Function LoadVessel:TVessel(file:TStream, pieces:TPiece[])
		Local v:TVessel = TVessel.Create()
		Local l:String[] = (String(ReadLine(file))).split(",")
		v.name = l[0]
		For Local y:Int = 0 To maxShapeY - 1
			Local yIn:String[] = String(ReadLine(file)).split(",")
			For Local x:Int = 0 To maxShapeX - 1
				Local yy:String[] = yIn[x].split("/")
				Local s:TBlock = v.shapeV[x, y]
				s.piece = Int(yy[0])
				s.rot = Int(yy[1])
				s.variant = Int(yy[2])
				If yy.Length > 3 Then
					v.shapeV[x, y].autoFire = Double(yy[3])
					v.shapeV[x, y].preferredAmmo1V = Int(yy[4])
					v.shapeV[x, y].preferredAmmo2V = Int(yy[5])
					v.shapeV[x, y].preferredAmmo3V = Int(yy[6])
				End If
			Next 
		Next
		v.CentreBlueprint()
		For Local i:Int = 0 To TWeaponClass.NumberOfClasses - 1
			v.loadout[i] = Int(ReadLine(file))
		Next
		v.BuildGunsMissilesModules(pieces)
		Return v
	End Function
	
	Method SaveVessel(file:TStream)
		CentreBlueprint()
		WriteLine file, name
		For Local y:Int = 0 To maxShapeY - 1
			For Local x:Int = 0 To maxShapeX - 1
				Local s:TBlock = shapeV[x, y]
				Local st:String = s.piece + "/" + s.rot + "/" + s.variant + "/" + s.autoFire + "/"
				st :+ s.preferredAmmo1V + "/" + s.preferredAmmo2V + "/" + s.preferredAmmo3V + ","
				WriteString(file, st)
			Next
			WriteLine(file, "")
		Next
		For Local i:Int = 0 To TWeaponClass.NumberOfClasses - 1
			WriteLine(file, loadout[i])
		Next
	End Method
	
	' Condition states
	Function BuildAutofireArray:Double[,]()
		Local a:Double[,] = New Double[TVessel.MaxShapeX, TVessel.MaxShapeY]
		For Local y:Int = 0 To TVessel.MaxShapeY - 1
			For Local x:Int = 0 To TVessel.MaxShapeX - 1
				a[x, y] = 1.0
			Next
		Next
		Return a
	End Function

	Function BuildConditionArray:Double[,]()
		Local a:Double[,] = New Double[TVessel.MaxShapeX, TVessel.MaxShapeY]
		For Local y:Int = 0 To TVessel.MaxShapeY - 1
			For Local x:Int = 0 To TVessel.MaxShapeX - 1
				a[x, y] = 1.0
			Next
		Next
		Return a
	End Function
	
	Function BuildOnOffArray:Int[,]()
		Local a:Int[,] = New Int[TVessel.MaxShapeX, TVessel.MaxShapeY]
		For Local y:Int = 0 To TVessel.MaxShapeY - 1
			For Local x:Int = 0 To TVessel.MaxShapeX - 1
				a[x, y] = 1
			Next
		Next
		Return a
	End Function	
	
	' Stat stuff
	Method CalcECM:Int(pieces:TPiece[], condition:Double[,], onOff:Int[,])
		Local ecm:Int = 0
		For Local xy:TXY = EachIn occupied
			Local s:Int = shapeV[xy.x, xy.y].piece
			Local v:Int = shapeV[xy.x, xy.y].variant
			ecm :+ Double(pieces[s].GetECM(v)) * condition[xy.x, xy.y] * onOff[xy.x, xy.y]
		Next
		Return ecm
	End Method
	
	Method CalcMass:Int(pieces:TPiece[])
		Local mass:Int = 0
		For Local xy:TXY = EachIn occupied
			Local s:Int = shapeV[xy.x, xy.y].piece
			Local v:Int = shapeV[xy.x, xy.y].variant
			mass :+ pieces[s].GetMass(v)
		Next
		Return mass
	End Method

	Method CalcPropulsion:Int(pieces:TPiece[], onOff:Int[,])
		Local propulsion:Int = 0
		For Local xy:TXY = EachIn occupied
			Local s:Int = shapeV[xy.x, xy.y].piece
			Local v:Int = shapeV[xy.x, xy.y].variant
			propulsion :+ Double(pieces[s].GetPropulsion(v)) * onOff[xy.x, xy.y]
		Next
		Return propulsion
	End Method
	
	Method CalcPower:Int(pieces:TPiece[], onOff:Int[,])
		Local power:Int = 0
		For Local xy:TXY = EachIn occupied
			Local s:Int = shapeV[xy.x, xy.y].piece
			Local v:Int = shapeV[xy.x, xy.y].variant
			power :+ Double(pieces[s].GetPower(v)) * onOff[xy.x, xy.y]
		Next
		Return power
	End Method

	Method CalcPowerOutput:Int(pieces:TPiece[], condition:Double[,], onOff:Int[,])
		Local power:Int = 0
		For Local xy:TXY = EachIn modules
			Local s:Int = shapeV[xy.x, xy.y].piece
			Local v:Int = shapeV[xy.x, xy.y].variant
			power :+ Double(pieces[s].GetPowerOut(v)) * condition[xy.x, xy.y] * onOff[xy.x, xy.y]
		Next
		Return power
	End Method

	Method CalcShield:Int(pieces:TPiece[], condition:Double[,], onOff:Int[,])
		Local shield:Int = 100
		For Local xy:TXY = EachIn modules
			Local p:TBlock = shapeV[xy.x, xy.y]
			Local r:Int = Double(pieces[p.piece].GetBooster(p.variant)) * condition[xy.x, xy.y] * onOff[xy.x, xy.y] 
			If r > 0 Then shield :+ r
		Next
		Return ((((CalcMass(pieces) * shield) / 100) / 5) / 25) * 25
	End Method

	Method CalcCostBase:Int(pieces:TPiece[])
		Local pts:Int = 0
		For Local xy:TXY = EachIn occupied
			pts :+ pieces[shapeV[xy.x, xy.y].piece].GetCost(0)
		Next
		Return pts
	End Method
	
	Method CalcCost:Int(pieces:TPiece[])
		Local pts:Int = 0
		For Local xy:TXY = EachIn occupied
			Local v:Int = shapeV[xy.x, xy.y].variant
			pts :+ pieces[shapeV[xy.x, xy.y].piece].GetCost(v)
		Next
		Return pts
	End Method
	
	Method CalcCostTotal:Int(pieces:TPiece[], weapons:TWeaponClass[], loadout:Int[])
		If fighter = 1 Then Return 0
		Local pts:Int = 0
		For Local i:Int = 0 To TWeaponClass.NumberOfClasses - 1
			pts :+ (loadout[i] * weapons[i].cost)
		Next
		Return CalcCost(pieces) + pts
	End Method

	' Calculated
	Method CalcSpeed:Float(propulsion:Int, mass:Int)
		Local massSq:Float = Float(mass) / 250.0
		Local speed:Float = (Float(propulsion) / massSq) * 1.5
'		Print "Speed: " + speed	
		If speed > 500 Then speed = 500
		If speed < 0 Then speed = 0
		Return speed
	End Method
	
	Method CalcDPS:Float(propulsion:Int, mass:Int)
		Local massSq:Float = Float(mass) / 250.0
		Local dps:Float = Float(propulsion) / massSq / 5.0
'		Print "DPS: " + dps	
		If dps <= 0 Then dps = 5.0
		If dps > 100 Then dps = 100
		Return dps
	End Method

	Method CalcArmour:Int(mass:Int)
		Return mass / 100 * 10
	End Method
	
	Method CalcRegeneration:Double(pieces:TPiece[], condition:Double[,], onOff:Int[,])
		Local regeneration:Int = 100
		For Local xy:TXY = EachIn modules
			Local p:TBlock = shapeV[xy.x, xy.y]
			Local r:Int = Double(pieces[p.piece].GetRegeneration(p.variant)) * condition[xy.x, xy.y] * onOff[xy.x, xy.y] 
			If r > 0 Then regeneration :+ r
		Next
		Return Double(regeneration) / 5000.0
	End Method

	Method CalcRepairRate:Double(pieces:TPiece[], condition:Double[,], onOff:Int[,])
		Local repair:Int = 100
		For Local xy:TXY = EachIn modules
			Local p:TBlock = shapeV[xy.x, xy.y]
			Local r:Int = Double(pieces[p.piece].GetRepairRate(p.variant)) * condition[xy.x, xy.y] * onOff[xy.x, xy.y] 
			If r > 0 Then repair :+ r
		Next
		Return Double(repair) / 20000.0
	End Method

	Method CalcRadarRange:Float(pieces:TPiece[], condition:Double[,], onOff:Int[,])
		Local range:Float = 0.0
		
		' A tactical scanner
		For Local xy:TXY = EachIn modules
			Local p:TBlock = shapeV[xy.x, xy.y]
			If p.variant = 4 Then range :+ Double(25000) * onOff[xy.x, xy.y] '* condition[xy.x, xy.y] 
			If p.variant = 5 Then range :+ Double(100000) * onOff[xy.x, xy.y] '* condition[xy.x, xy.y] 
		Next
		If range = 0 Then range = DefaultRadarRange
		Return range
	End Method
	
End Type
