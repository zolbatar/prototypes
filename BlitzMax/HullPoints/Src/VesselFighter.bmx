SuperStrict
Import "Vessel.bmx"
Import "WeaponClass.bmx"

Type TVesselFighter Extends TVessel
	Function Create:TVessel()
		Local vm:TVesselFighter = New TVesselFighter
		vm.ship = 1
		vm.fighter = 1
		vm.name = "Fighter"
		Return vm
	End Function
End Type



