SuperStrict
Import "GFX.bmx"
Import "Vessel.bmx"

Type TFleet
	Field name:String
	Field filename:String
	Field vessels:TList
	Field drone:TImage
	
	Function Create:TFleet(name:String)
		Local o:TFleet = New TFleet
		o.name = name
		o.vessels = CreateList()
		Return o
	End Function
	
	Method GetX:TVessel(i:Int)
		Return TVessel(vessels.ValueAtIndex(i))
	End Method

	Method RenderAllVessels(pieces:TPiece[], gfx:TGFX)
		drone = LoadImage("Res/Pieces/" + name + " 1/Drone.png", FILTEREDIMAGE|MIPMAPPEDIMAGE)
		SetViewport(0, 0, gfx.width, gfx.height)
		For Local v:TVessel = EachIn vessels
			v.Render(pieces)
		Next
	End Method

	Method LoadFleetBody:Int(file:TStream, pieces:TPiece[])
		Try
			Local s:String[] = String(ReadLine(file)).Split(",")
			name = s[0]
			vessels = CreateList()
			Local vc:Int = Int(s[1])
			For Local i:Int = 0 To vc - 1
				ListAddLast(vessels, TVessel.LoadVessel(file, pieces))
			Next
			Return 0
		Catch error:String
			Return -1
		End Try
	End Method

	Function LoadFleet:TFleet(file:TStream, filename:String, pieces:TPiece[])
		Local o:TFleet = New TFleet
		o.filename = filename
		Local r:Int = o.LoadFleetBody(file, pieces)
		If r = -1 Then
			Print "Corrupted fleet file " + filename
			Return Null
		End If
		Return o
	End Function
	
	Method ReloadFleet:Int(pieces:TPiece[])
		Print "Reloading fleet: " + filename
		Local file:TStream = ReadFile(filename)
		If Not file Then Return -1
		LoadFleetBody(file, pieces)
		CloseStream file
		Return 0
	End Method
	
	Method SaveFleet()	
		Local file:TStream = WriteFile("Fleet/" + name  + ".flt")
		If Not file RuntimeError "Failed to save Fleet/" + name  + ".flt"
		WriteLine file, name  + "," + String(vessels.Count()) 
		For Local v:TVessel = EachIn vessels
			v.SaveVessel(file)
		Next
		CloseStream file
	End Method
	
	Method DeleteFleet()
		DeleteFile("Fleet/" + name  + ".flt")
	End Method

	Function FindFleet:TFleet(lst:TList, s:String)
		For Local fleet:TFleet = EachIn lst
			If fleet.name = s Then Return fleet
		Next
		Return Null
	End Function

	Method FindVessel:TVessel(s:String)
		For Local v:TVessel = EachIn vessels
			If v.name = s Then Return v
		Next
		Return Null
	End Method

End Type

