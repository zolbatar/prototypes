Const Flags:Int = FILTEREDIMAGE|MIPMAPPEDIMAGE
Const NoPieces:Int = 14
Function CreatePieceArray:TPiece[]()
	Local path:String = "Res/Pieces/Union 1/"
	Local pieces:TPiece[noPieces]
	pieces[0] = TPiece1.Create(path)
	pieces[1] = TPiece2.Create(path)
	pieces[2] = TPiece3.Create(path)
	pieces[3] = TPiece4.Create(path)
	pieces[4] = TPiece5.Create(path)
	pieces[5] = TPiece6.Create(path)
	pieces[6] = TPiece7.Create(path)
	pieces[7] = TPiece8.Create(path)
	pieces[8] = TPiece9.Create(path)
	pieces[9] = TPiece10.Create(path)
	pieces[10] = TPiece11.Create(path)
	pieces[11] = TPiece12.Create(path)
	pieces[12] = TPiece13.Create(path)
	pieces[13] = TPiece14.Create(path)
	Return pieces
End Function

Type TPiece1 Extends TPiece
	Function Create:TPiece(path:String)
		Local p:TPiece1 = New TPiece1
		p.mass = [0]
		p.cost = [0]
		p.descriptions = ["Empty"]
		p.Render(path)
		Return p
	End Function
	
	Method Render(path:String)
		image = New TImage[1]
		Local format:Int = PF_BGRA8888
		?littleendian
		format = PF_BGRA8888
		?bigendian
		format = PF_ARGB8888
		?
		Local p:TPixmap = CreatePixmap(size, size, format)
		ClearPixels(p, 0)
		image[0] = LoadImage(p)
	End Method
End Type

Type TPiece2 Extends TPiece
	Function Create:TPiece(path:String)
		Local p:TPiece2 = New TPiece2
		p.mass = [10, 25, 50, 250, 25, 75, 250, 50, 250]
		p.power = [0, 0, 50, 100, 100, 500, 100, 250, 750]
		p.powerOut = [0, 1000, 0, 0, 0, 0, 0, 0, 0]
		p.cost = [5, 50, 100, 250, 50, 250, 50, 250, 500]
		p.booster = [0, 0, 100, 0, 0, 0, 0, 0, 0]
		p.regeneration = [0, 0, 0, 50, 0, 0, 0, 0, 0]
		p.repair = [0, 0, 0, 0, 0, 0, 150, 0, 0]
		p.ECM = [0, 0, 0, 0, 0, 0, 0, 75, 0]
		p.isModule = 1
		p.maxVariant = 9
		p.descriptions = New String[p.maxVariant]
		p.descriptions[0] = "Module"
		p.descriptions[1] = "1000MW Power Core"
		p.descriptions[2] = "Shield Hardener"
		p.descriptions[3] = "Shield Booster"
		p.descriptions[4] = "Tactical Scanner"
		p.descriptions[5] = "Long Range Scanner"
		p.descriptions[6] = "Hull & Module Repair"
		p.descriptions[7] = "ECM Module"
		p.descriptions[8] = "EMP Bomb"
		p.longDescriptions = New String[p.maxVariant]
		p.longDescriptions[0] = "An empty module, simply mass."
		p.longDescriptions[1] = "Standard universal power core."
		p.longDescriptions[2] = "Doubles standard shield capacity."
		p.longDescriptions[3] = "A 50% increase in shield regeneration rate."
		p.longDescriptions[4] = "Gives 25km of targeting coverage."
		p.longDescriptions[5] = "Gives 100km of targeting coverage, standard battle group issue."
		p.longDescriptions[6] = "Hull and module repair system. Only way to repair hull."
		p.longDescriptions[7] = "Reduces the chance of a missile lock."
		p.longDescriptions[8] = "Causes systems damage to nearby ships when activated."
		p.Render(path)
		Return p
	End Function
	
	Method Render(path:String)
		image = New TImage[maxVariant]
		For Local i:Int = 0 To maxVariant - 1
			If i = 1 Then
				image[i] = LoadImage(path + "Power.png",flags)
			ElseIf i = 3 Then
				image[i] = LoadImage(path + "ShieldBooster.png",flags)
			ElseIf i = 4 Then
				image[i] = LoadImage(path + "ShortRangeScanner.png",flags)
			ElseIf i = 5 Then
				image[i] = LoadImage(path + "LongRangeScanner.png",flags)
			ElseIf i = 7 Then
				image[i] = LoadImage(path + "ECM.png",flags)
			ElseIf i = 8 Then
				image[i] = LoadImage(path + "EMP.png",flags)
			Else
				image[i] = LoadImage(path + "Module.png",flags)
			End If
		Next
	End Method
	
End Type

Type TPiece3 Extends TPiece
	Function Create:TPiece(path:String)
		Local p:TPiece3 = New TPiece3
		p.mass = [100]
		p.cost = [100]
		p.power = [100]
		p.isLauncher = 1
		p.descriptions = ["Launch Bay"]
		p.Render(path)
		Return p
	End Function
	
	Method Render(path:String)
		image = New TImage[1]
		image[0] = LoadImage(path + "Launcher.png",flags)
	End Method
End Type

Type TPiece4 Extends TPiece
	Function Create:TPiece(path:String)
		Local p:TPiece4 = New TPiece4
		p.mass = [100]
		p.propulsion = [250]
		p.power = [150]
		p.cost = [50]
		p.component = 1
		p.descriptions = ["Thruster"]
		p.Render(path)
		Return p
	End Function
	
	Method Render(path:String)
		image = New TImage[1]
		image[0] = LoadImage(path + "Thruster.png",flags)
	End Method
End Type

Type TPiece5 Extends TPiece
	Function Create:TPiece(path:String)
		Local p:TPiece5 = New TPiece5
		p.mass = [100]
		p.power = [150]
		p.cost = [50]
		p.component = 1
		p.isMissile = 1
		p.descriptions = ["Missile Tube"]
		p.Render(path)
		Return p
	End Function
	
	Method Render(path:String)
		image = New TImage[1]
		image[0] = LoadImage(path + "Missile.png",flags)
	End Method
	
End Type

Type TPiece6 Extends TPiece
	Function Create:TPiece(path:String)
		Local p:TPiece6 = New TPiece6
		p.mass = [150]
		p.power = [150]
		p.cost = [50]
		p.component = 1
		p.isGun = 1
		p.descriptions = ["Railgun"]
		p.Render(path)
		Return p
	End Function
	
	Method Render(path:String)
		image = New TImage[1]
		image[0] = LoadImage(path + "Gun.png",flags)
	End Method

End Type

Type TPiece7 Extends TPiece
	Function Create:TPiece(path:String)
		Local p:TPiece7 = New TPiece7
		p.mass = [20]
		p.cost = [10]
		p.Render(path)
		p.descriptions = ["Hull"]
		Return p
	End Function
	
	Method Render(path:String)
		image = New TImage[1]
		image[0] = LoadImage(path + "Section1.png",flags)
	End Method
End Type

Type TPiece8 Extends TPiece
	Function Create:TPiece(path:String)
		Local p:TPiece8 = New TPiece8
		p.mass = [40]
		p.cost = [20]
		p.descriptions = ["Hull"]
		p.Render(path)
		Return p
	End Function
	
	Method Render(path:String)
		image = New TImage[1]
		image[0] = LoadImage(path + "Section2.png",flags)
	End Method
End Type

Type TPiece9 Extends TPiece
	Function Create:TPiece(path:String)
		Local p:TPiece9 = New TPiece9
		p.mass = [80]
		p.cost = [40]
		p.descriptions = ["Hull"]
		p.Render(path)
		Return p
	End Function
	
	Method Render(path:String)
		image = New TImage[1]
		image[0] = LoadImage(path + "Section3.png",flags)
	End Method
End Type

Type TPiece10 Extends TPiece
	Function Create:TPiece(path:String)
		Local p:TPiece10 = New TPiece10
		p.mass = [60]
		p.cost = [30]
		p.descriptions = ["Hull"]
		p.Render(path)
		Return p
	End Function
	
	Method Render(path:String)
		image = New TImage[1]
		image[0] = LoadImage(path + "Section5.png",flags)
	End Method
End Type

Type TPiece11 Extends TPiece
	Function Create:TPiece(path:String)
		Local p:TPiece11 = New TPiece11
		p.mass = [50]
		p.cost = [25]
		p.descriptions = ["Hull"]
		p.Render(path)
		Return p
	End Function
	
	Method Render(path:String)
		image = New TImage[1]
		image[0] = LoadImage(path + "Section6.png",flags)
	End Method
End Type

Type TPiece12 Extends TPiece
	Function Create:TPiece(path:String)
		Local p:TPiece12 = New TPiece12
		p.mass = [50]
		p.cost = [25]
		p.descriptions = ["Hull"]
		p.Render(path)
		Return p
	End Function
	
	Method Render(path:String)
		image = New TImage[1]
		image[0] = LoadImage(path + "Section7.png",flags)
	End Method
End Type

Type TPiece13 Extends TPiece
	Function Create:TPiece(path:String)
		Local p:TPiece13 = New TPiece13
		p.mass = [60]
		p.cost = [30]
		p.descriptions = ["Hull"]
		p.Render(path)
		Return p
	End Function
	
	Method Render(path:String)
		image = New TImage[1]
		image[0] = LoadImage(path + "Section4.png",flags)
	End Method
End Type

Type TPiece14 Extends TPiece
	Function Create:TPiece(path:String)
		Local p:TPiece14 = New TPiece14
		p.mass = [100]
		p.cost = [50]
		p.descriptions = ["Hull"]
		p.Render(path)
		Return p
	End Function
	
	Method Render(path:String)
		image = New TImage[1]
		image[0] = LoadImage(path + "Junction.png",flags)
	End Method
End Type


