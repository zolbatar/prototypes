SuperStrict
Import "Helper.bmx"
Import "Profiler.bmx"
Import "WeaponClass.bmx"

Type TBlock
	Field piece:Int, variant:Int = 0, rot:Int, autoFire:Double, preferredAmmo1V:Int, preferredAmmo2V:Int, preferredAmmo3V:Int, strafe:Int
	Field fired:Long, numberRemaining:Int, weapon:TWeaponClass, reloadNeeded:Int = 0
	Field AngleCache:Int[] = [0, 90, 180, 270]

	Method RotateL()
		rot :- 1
		If rot = -1 Then rot = 3
	End Method

	Method RotateR()
		rot :+ 1
		If rot = 4 Then rot = 0
	End Method

	Method TubeAngle:Double(angle:Double)
'		?debug
'  			TProfiler.Enter("Block::TubeAngle")
'  		?
		Local tubeAngle:Double = AdjustAngle(angle +  AngleCache[rot])
'		?debug
'  			TProfiler.Leave("Block::TubeAngle")
'  		?
		Return tubeAngle
	End Method
End Type


