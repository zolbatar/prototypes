SuperStrict
Import "Vessel.bmx"
Import "WeaponClass.bmx"

Type TVesselMissile Extends TVessel
	Function Create:TVessel()
		Local vm:TVesselMissile = New TVesselMissile
		vm.ship = 0
		vm.missile = 1
		vm.name = "Missile"
		Return vm
	End Function
End Type

