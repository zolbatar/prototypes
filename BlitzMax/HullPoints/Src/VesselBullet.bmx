SuperStrict
Import "Vessel.bmx"
Import "WeaponClass.bmx"

Type TVesselBullet Extends TVessel
	Function Create:TVessel()
		Local vm:TVesselBullet = New TVesselBullet
		vm.ship = 0
		vm.missile = 0
		vm.name = "Bullet"
		Return vm
	End Function
End Type


