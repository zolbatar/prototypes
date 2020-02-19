SuperStrict
Import "Fleet.bmx"
Import "GameData.bmx"
Import "GFX.bmx"
Import "ShipEditor.bmx"
Import "UIInputBox.bmx"
Import "UISelector.bmx"

Type TChooserFleet

	Function FleetList:TList(gd:TGameData)
		Local s:TList = CreateList()
		For Local f:TFleet = EachIn gd.fleets
			ListAddLast(s, f.name)
		Next
		Return s
	End Function
	
	Function Start(gfx:TGFX, gd:TGameData)
		Repeat
			Local ui:TUISelector = TUISelector.Create(FleetList(gd), 350, "Choose Fleet", "Fleet", 1, 1)
			Local f:Int = ui.Render(gfx, gd.buttons, gd.sf, 0)
			If f = -1 Then 
				Return
			ElseIf f = -2 Then
				Local t2:TUIInputBox = TUIInputBox.Create("Enter the fleet name:", "", 400, "Create New Fleet", 30)
				Local name:String = t2.Render(gfx, gd, 0)
				If name = "" Then Return
				Local fleet:TFleet = TFleet.Create(name)
				fleet.SaveFleet()
				ListAddLast(gd.fleets, fleet)
			ElseIf f >= 0
				Local t:TFleet = TFleet(gd.fleets.ValueAtIndex(f))
				Local v:TVessel
				If t.vessels.Count() = 0 Then
					v = TVessel.Create()
					ListAddFirst(t.vessels, v)
				Else
					v = TVessel(t.vessels.First())
				End If
				TShipEditor.Create(gfx, gd, t, v)
				Return
			Else
				' Delete
				Local i:Int = -(f + 3)
				Local t:TFleet = TFleet(gd.fleets.ValueAtIndex(i))
				t.DeleteFleet()
				ListRemove(gd.fleets, t)
			End If
		Forever
	End Function
	
End Type
