SuperStrict
Import "Helper.bmx"
Import "Vessel.bmx"
Import "WeaponClass.bmx"

Type TVesselShrapnel Extends TVessel
	Function Create:TVessel()
		Local vm:TVesselShrapnel = New TVesselShrapnel
		vm.ship = 0
		vm.missile = 0
		vm.name = "Shrapnel"
		Return vm
	End Function
End Type



