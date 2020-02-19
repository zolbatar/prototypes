SuperStrict
Import "Vessel.bmx"
Import "WeaponClass.bmx"

Type TDrone Extends TVessel
	Function Create:TVessel()
		Local vm:TDrone = New TDrone
		vm.name = "Drone"
		vm.ship = 1
		vm.fighter = 1
		Return vm
	End Function
End Type



