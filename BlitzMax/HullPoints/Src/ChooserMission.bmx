SuperStrict
Import "GameData.bmx"
Import "GFX.bmx"
Import "MissionBuilder.bmx"
Import "UIInputBox.bmx"
Import "UIListButtonText.bmx"
Import "UISelector.bmx"

Type TChooserMission
	
	Function FleetList:TList(gd:TGameData)
		Local s:TList = CreateList()
		For Local f:TFleet = EachIn gd.fleets
			ListAddLast(s, f.name)
		Next
		Return s
	End Function

	Function MissionList:TList()
		Local l:TList = ListFiles("Missions/", "mis", CreateList())
		Local s:TList = CreateList()
		For Local f:String = EachIn l
			ListAddLast(s, StripAll(f))
		Next
		Return s
	End Function

	Function Start(gfx:TGFX, gd:TGameData)
		Repeat
			Local ui:TUISelector = TUISelector.Create(MissionList(), 350, "Choose Mission", "Mission", 1, 1)
			Local f:Int = ui.Render(gfx, gd.buttons, gd.sf, 0)
			If f = -1 Then 
				Return
			ElseIf f = -2 Then
				Local t2:TUIInputBox = TUIInputBox.Create("Enter the mission name:", "", 400, "Create New Mission", 30)
				Local name:String = t2.Render(gfx, gd, 0)
				If name = "" Then Return
				Local s:TList = FleetList(gd)
				ui = TUISelector.Create(s, 350, "Choose Fleet (Player 1)", "Fleet", 0, 0)
				Local p1:Int = ui.Render(gfx, gd.buttons, gd.sf, 0)
				If p1 = -1 Then Return
				s = FleetList(gd)
				ui = TUISelector.Create(s, 350, "Choose Fleet (Player 2)", "Fleet", 0, 0)
				Local p2:Int = ui.Render(gfx, gd.buttons, gd.sf, 0)
				If p2 = -1 Then Return

				' Size
				Local t:String[] = ["60km x 40km", "150km x 100km", "300km x 200km"]
				Local size:TUIListButtonText = TUIListButtonText.Create(["Small Map Size", "Medium Map Size", "Large Map Size"], t, 3, 300, "Choose Map Size")
				Local s2:Int = size.Render(gfx, gd.buttons, gd.sf, 0)
				If s2 = -1 Then Return
				Local mb:TMissionBuilder = New TMissionBuilder
				mb.gd = gd
				mb.g = TGameState.Create()
				Select s2
				Case 0
					mb.g.worldSizeX = 60000.0
					mb.g.worldSizeY = 40000.0
					mb.g.mapSectionSize = 2500
				Case 1 
					mb.g.worldSizeX = 150000.0
					mb.g.worldSizeY = 100000.0
					mb.g.mapSectionSize = 5000
				Case 2
					mb.g.worldSizeX = 150000.0
					mb.g.worldSizeY = 200000.0
					mb.g.mapSectionSize = 10000
				End Select
				mb.g.fleets[0] = TFleet(gd.fleets.ValueAtIndex(p1))
				mb.g.fleets[1] = TFleet(gd.fleets.ValueAtIndex(p2))
				mb.Setup(gfx)
				mb.filename = name
				mb.SaveMission(gfx)
				mb.Start(gfx, gd)
				Return
			ElseIf f >= 0
				Local mb:TMissionBuilder = New TMissionBuilder
				mb.gd = gd
				Local file:String = String(MissionList().ValueAtIndex(f))
				mb.filename = StripAll(file)
				mb.g = TGameSave.LoadMission(file, gd)
				If mb.g = Null Then 
				Else
					mb.Setup(gfx)
					mb.Start(gfx, gd)
					Return
				End If
			Else
				Local i:Int = -(f + 3)
				DeleteFile("Missions/" + String(MissionList().ValueAtIndex(i)) + ".mis")
			End If
		Forever
	End Function
	
End Type

