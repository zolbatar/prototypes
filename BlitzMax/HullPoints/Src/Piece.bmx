SuperStrict
Import BaH.Cairo
Import "GFX.bmx"
Include "StandardPieces.bmx"

Type TPiece
	Const Size:Int = 256
	Field image:TImage[]
	Field mass:Int[], propulsion:Int[], power:Int[], powerOut:Int[], cost:Int[], repair:Int[]
	Field booster:Int[], regeneration:Int[], ECM:Int[], firingReduce:Int[]
	Field descriptions:String[], longDescriptions:String[], maxVariant:Int = 1 
	Field isModule:Int = 0, isMissile:Int = 0, isGun:Int = 0, component:Int = 0, isLauncher:Int = 0

	Method Draw(x:Int, y:Int, variant:Int)
		DrawImage(image[variant], x, y)
	End Method

	Function DrawPiece(pieces:TPiece[], piece:Int, x:Int, y:Int, rot:Int, variant:Int, a:Double)
		Select rot
		Case 0
			SetRotation 0 + a
		Case 1
			SetRotation 90 + a
		Case 2
			SetRotation 180 + a
		Case 3
			SetRotation 270 + a
		End Select
		pieces[piece].Draw(x, y, variant)
		SetRotation 0
	End Function

	Method IsComponent:Int()
		Return component
	End Method
	
	Method GetDescription:String(variant:Int = 0)
		Return descriptions[variant]
	End Method
	
	Method GetLongDescription:String(variant:Int = 0)
		Return longDescriptions[variant]
	End Method

	Method GetMass:Int(variant:Int = 0)
		Return mass[variant]
	End Method
	
	Method GetCost:Int(variant:Int = 0)
		If cost.Length > 0 Then Return cost[variant] Else Return 0
	End Method

	Method GetPower:Int(variant:Int = 0)
		If power.length > 0 Then Return power[variant] Else Return 0
	End Method

	Method GetRegeneration:Int(variant:Int = 0)
		If regeneration.length > 0 Then Return regeneration[variant] Else Return 0
	End Method

	Method GetECM:Int(variant:Int = 0)
		If ecm.length > 0 Then Return ecm[variant] Else Return 0
	End Method

	Method GetBooster:Int(variant:Int = 0)
		If booster.length > 0 Then Return booster[variant] Else Return 0
	End Method
	
	Method GetRepairRate:Int(variant:Int = 0)
		If repair.length > 0 Then Return repair[variant] Else Return 0
	End Method

	Method GetPowerOut:Int(variant:Int = 0)
		If powerOut.Length > 0 Then Return powerOut[variant] Else Return 0
	End Method

	Method GetPropulsion:Int(variant:Int = 0)
		If propulsion.Length > 0 Then Return propulsion[variant] Else Return 0
	End Method
	
	Function RenderPiece(pieces:TPiece[], zoom:Int, s:Int, x:Int, y:Int, rot:Int, variant:Int)
		If s >= 1 Then
			Local z:Double = Double(zoom) / Double(TPiece.Size)
			SetScale(z, z)
			TPiece.DrawPiece(pieces, s, x, y, rot, variant, 0.0)
			SetScale(1.0, 1.0)
		End If
	End Function

	Function RenderPieceNoScale(pieces:TPiece[], piece:Int, x:Int, y:Int, rot:Int, variant:Int, a:Double)
		TPiece.DrawPiece(pieces, piece, x, y, rot, variant, a)
	End Function

End Type

