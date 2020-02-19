SuperStrict
Import BaH.cairo

Type TWeaponClass
	Const BaselineCost:Int = 10.0
	Const NumberOfClasses:Int = 10, missileType:Int = 0, bulletType:Int = 1, shrapnelType:Int = 2, size:Double = 32.0
	Const fragmentID:Int = 10, explosionID:Int = 11, explosionSmallID:Int = 12, fighterID:Int = 13
	Const DefaultMissile:Int = 5, DefaultBullet:Int = 0, ImgSize:Double = 32.0, LastBullet:Int = 4, LastMissile:Int = 9
	Const MissileAngle:Double = 60.0, RailgunAngle:Double = 10.0, DefaultMissileDPS:Double = 50.0
	Const EMPRadius:Double = 7500.0, EMPDamage:Double = 500.0, EMPRecharge:Long = 30000
	Field targetable:Int = 1, manuallyFired:Int = 0, radarSeeking:Int = 0, defensive:Int = 0, starPattern:Int = 0, explosionType:Int = 0
	Field id:Int, t:Int, name:String, description:String, currentSpeed:Double, targetSpeed:Double, dps:Double
	Field number:Int, coolDown:Long, cost:Int = 0, maxRange:Double = 50000.0, blastRadius:Double = 5.0, hitRadius:Double = 50.0, sound:Int = 0
	Field img:TImage, projectileImg:TImage
	Field cR:Int, cG:Int, cB:Int
	Field damage:Double, damageHullMultiplier:Double = 1.0, damageShieldMultiplier:Double = 1.0, damageSystemMultiplier:Double = 1.0
	
	Function Create:TWeaponClass[]()
		Local weapons:TWeaponClass[] = New TWeaponClass[TWeaponClass.numberOfClasses + 4]
		weapons[0] = TWeaponClass.Create_Bullet1(0)
		weapons[1] = TWeaponClass.Create_Bullet2(1)
		weapons[2] = TWeaponClass.Create_Bullet3(2)
		weapons[3] = TWeaponClass.Create_Bullet4(3)
		weapons[4] = TWeaponClass.Create_Bullet5(4)
		weapons[5] = TWeaponClass.Create_Missile1(5)
		weapons[6] = TWeaponClass.Create_Missile2(6)
		weapons[7] = TWeaponClass.Create_Missile3(7)
		weapons[8] = TWeaponClass.Create_Missile4(8)
		weapons[9] = TWeaponClass.Create_Missile5(9)
		weapons[10] = TWeaponClass.Create_Fragment(fragmentID)
		weapons[11] = TWeaponClass.Create_Explosion(explosionID)
		weapons[12] = TWeaponClass.Create_ExplosionSmall(explosionSmallID)
		weapons[13] = TWeaponClass.Create_Fighter(fighterID)
		Return weapons
	End Function
	
	Function Create_Fragment:TWeaponClass(id:Int)
		Local w:TWeaponClass = New TWeaponClass
		w.id = id
		w.t = shrapnelType
		w.name = "Fragment"
		w.description = "Shrapnel fragment."
		w.currentSpeed = 1000.0
		w.targetSpeed = 1000.0
		w.dps = 0
		w.damage = 2.5
		w.cost = 0
		w.blastRadius = 50.0
		w.hitRadius = 0.0
		w.maxRange = 250
		w.explosionType = 0
		w.Render(128.0 / 256.0, 128.0 / 256, 128.0 / 256.0)
		Return w
	End Function

	Function Create_Fighter:TWeaponClass(id:Int)
		Local w:TWeaponClass = New TWeaponClass
		w.id = id
		w.t = bulletType
		w.name = "Fighter"
		w.description = "Fighter weapon."
		w.currentSpeed = 1000.0
		w.targetSpeed = 1000.0
		w.dps = DefaultMissileDPS
		w.damage = 2.0
		w.cost = 0
		w.number = 25
		w.coolDown = 1000
		w.blastRadius = 25.0
		w.hitRadius = 0.0
		w.maxRange = 2500
		w.explosionType = 0
		w.Render(0.0 / 256.0, 256.0 / 256, 0.0 / 256.0)
		Return w
	End Function

	Function Create_Explosion:TWeaponClass(id:Int)
		Local w:TWeaponClass = New TWeaponClass
		w.id = id
		w.damage = 50.0
		w.blastRadius = 250.0
		w.hitRadius = 0.0
		w.explosionType = 4
		w.Render(186.0 / 256.0, 85.0 / 256, 211.0 / 256.0)
		Return w
	End Function

	Function Create_ExplosionSmall:TWeaponClass(id:Int)
		Local w:TWeaponClass = New TWeaponClass
		w.id = id
		w.damage = 50.0
		w.blastRadius = 50.0
		w.hitRadius = 0.0
		w.explosionType = 4
		w.Render(186.0 / 256.0, 85.0 / 256, 211.0 / 256.0)
		Return w
	End Function

	Function Create_Bullet1:TWeaponClass(id:Int)
		Local w:TWeaponClass = New TWeaponClass
		w.id = id
		w.t = bulletType
		w.name = "HE"
		w.description = "High explosive, small concentrated blast radius."
		w.currentSpeed = 2000.0
		w.targetSpeed = 2000.0
		w.dps = 0
		w.damage = 25
		w.number = 50
		w.coolDown = 2500
		w.cost = BaselineCost * 5
		w.blastRadius = 100.0
		w.hitRadius = 0.0
		w.maxRange = 5000
		w.explosionType = 1
		w.sound = 0
		w.Render(144.0 / 256.0, 238.0 / 256, 144.0 / 256.0)
		Return w
	End Function

	Function Create_Bullet2:TWeaponClass(id:Int)
		Local w:TWeaponClass = New TWeaponClass
		w.id = id
		w.t = bulletType
		w.name = "Thermotip"
		w.description = "Tipped with a thermonuclear device, powerful with an EMP effect."
		w.currentSpeed = 1500.0
		w.targetSpeed = 1500.0
		w.dps = 0
		w.damage = 75
		w.number = 10
		w.coolDown = 5000
		w.cost = BaselineCost * 10
		w.blastRadius = 250.0
		w.hitRadius = 0.0
		w.maxRange = 5000
		w.explosionType = 3
		w.damageSystemMultiplier = 2.0
		w.sound = 1
		w.Render(255 / 256.0, 215.0 / 256, 0.0 / 256.0)
		Return w
	End Function

	Function Create_Bullet3:TWeaponClass(id:Int)
		Local w:TWeaponClass = New TWeaponClass
		w.id = id
		w.t = bulletType
		w.name = "Shrapnel"
		w.description = "Explodes on impact into multiple fragments."
		w.currentSpeed = 3500.0
		w.targetSpeed = 1500.0
		w.dps = 0
		w.damage = 10
		w.number = 50
		w.coolDown = 1000
		w.cost = BaselineCost * 2
		w.blastRadius = 50.0
		w.hitRadius = 25.0
		w.starPattern = 1
		w.maxRange = 2500
		w.explosionType = 0
		w.sound = 3
		w.Render(186.0 / 256.0, 85.0 / 256, 211.0 / 256.0)
		Return w
	End Function
	
	Function Create_Bullet4:TWeaponClass(id:Int)
		Local w:TWeaponClass = New TWeaponClass
		w.id = id
		w.t = bulletType
		w.name = "AP"
		w.description = "Solid core round, 3x as effective against hulls, bypasses shields entirely."
		w.currentSpeed = 2000.0
		w.targetSpeed = 2000.0
		w.dps = 0
		w.damage = 50
		w.number = 25
		w.coolDown = 2500
		w.cost = BaselineCost * 5
		w.blastRadius = 100.0
		w.hitRadius = 0.0
		w.defensive = 0
		w.maxRange = 5000
		w.damageHullMultiplier = 3.0
		w.explosionType = 1
		w.sound = 4
		w.Render(255.0 / 256.0, 255.0 / 256, 60.0 / 256.0)
		Return w
	End Function

	Function Create_Bullet5:TWeaponClass(id:Int)
		Local w:TWeaponClass = New TWeaponClass
		w.id = id
		w.t = bulletType
		w.name = "Goalkeeper"
		w.description = "Very effective anti missile/projectile system."
		w.currentSpeed = 3500.0
		w.targetSpeed = 3500.0
		w.damage = 1
		w.number = 100
		w.coolDown = 200
		w.cost = BaselineCost * 3
		w.blastRadius = 25.0
		w.hitRadius = 10.0
		w.defensive = 1
		w.maxRange = 2500
		w.explosionType = 1
		w.sound = 2
		w.Render(186.0 / 256.0, 85.0 / 256, 211.0 / 256.0)
		Return w
	End Function

	Function Create_Missile1:TWeaponClass(id:Int)
		Local w:TWeaponClass = New TWeaponClass
		w.id = id
		w.t = missileType
		w.name = "Seeker"
		w.description = "Standard seeking missile."
		w.currentSpeed = 500.0
		w.targetSpeed = 2000.0
		w.dps = DefaultMissileDPS
		w.damage = 20
		w.number = 15
		w.coolDown = 5000
		w.cost = BaselineCost * 2
		w.blastRadius = 100.0
		w.hitRadius = 0.0
		w.maxRange = 10000
		w.explosionType = 2
		w.sound = 2
		w.Render(205.0 / 256.0, 92.0 / 256, 92.0 / 256.0)
		Return w
	End Function

	Function Create_Missile2:TWeaponClass(id:Int)
		Local w:TWeaponClass = New TWeaponClass
		w.id = id
		w.t = missileType
		w.name = "Hammerhead"
		w.description = "Harder hitting, slower moving missile."
		w.currentSpeed = 500.0
		w.targetSpeed = 1500.0
		w.dps = DefaultMissileDPS
		w.damage = 50
		w.number = 10
		w.coolDown = 10000
		w.cost = BaselineCost * 5
		w.blastRadius = 250.0
		w.hitRadius = 0.0
		w.maxRange = 10000.0
		w.explosionType = 0
		w.sound = 2
		w.Render(255.0 / 256.0, 255.0 / 256, 0.0 / 256.0)
		Return w

	End Function
	
	Function Create_Missile3:TWeaponClass(id:Int)
		Local w:TWeaponClass = New TWeaponClass
		w.id = id
		w.t = missileType
		w.name = "HARM"
		w.description = "Auto-seeking anti-radar missile. Equipped with a cloaking system."
		w.targetable = 0
		w.radarSeeking = 1
		w.currentSpeed = 500.0
		w.targetSpeed = 2000.0
		w.dps = DefaultMissileDPS
		w.damage = 10
		w.number = 5
		w.coolDown = 25000
		w.cost = BaselineCost * 25
		w.blastRadius = 100.0
		w.hitRadius = 0.0
		w.maxRange = 30000.0
		w.explosionType = 2
		w.sound = 2
		w.Render(200.0 / 256.0, 25.0 / 256, 87.0 / 256.0)
		Return w
	End Function

	Function Create_Missile4:TWeaponClass(id:Int)
		Local w:TWeaponClass = New TWeaponClass
		w.id = id
		w.t = missileType
		w.name = "Chaff"
		w.description = "Shield disrupting nano-fragments, 3x as effective against shields."
		w.currentSpeed = 500.0
		w.targetSpeed = 2000.0
		w.dps = DefaultMissileDPS
		w.damage = 25
		w.number = 15
		w.coolDown = 5000
		w.cost = BaselineCost * 7
		w.blastRadius = 100.0
		w.hitRadius = 0.0
		w.maxRange = 15000
		w.damageShieldMultiplier = 3.0
		w.explosionType = 3
		w.sound = 2
		w.Render(0.0 / 256.0, 139.0 / 256, 139.0 / 256.0)
		Return w
	End Function
	
	Function Create_Missile5:TWeaponClass(id:Int)
		Local w:TWeaponClass = New TWeaponClass
		w.id = id
		w.t = missileType
		w.name = "EMP"
		w.description = "Filled with micro-EMP charges, 3x as effective against systems."
		w.currentSpeed = 500.0
		w.targetSpeed = 2000.0
		w.dps = DefaultMissileDPS
		w.damage = 25
		w.number = 15
		w.coolDown = 5000
		w.cost = BaselineCost * 7
		w.blastRadius = 100.0
		w.hitRadius = 0.0
		w.maxRange = 15000
		w.damageSystemMultiplier = 3.0
		w.explosionType = 3
		w.sound = 2
		w.Render(34.0 / 256.0, 139.0 / 256, 87.0 / 256.0)
		Return w
	End Function
	
	Method Render(rT:Double, gT:Double, bT:Double)
		cR = rT * 256
		cG = gT * 256
		cB = bT * 256

		Local cairo:TCairo = TCairo.Create(TCairoImageSurface.CreateForPixmap(TWeaponClass.ImgSize, TWeaponClass.ImgSize))
		cairo.SetSourceRGBA(rT, gT, bT, 0.75)
		cairo.Arc(TWeaponClass.ImgSize / 2, TWeaponClass.ImgSize / 2, (TWeaponClass.ImgSize / 2) - 2.0, 0, 360)
		cairo.FillPreserve()
		cairo.SetSourceRGBA(1.0, 1.0, 1.0, 1.0)
		cairo.SetLineWidth(1.5)
		cairo.Stroke()
		img = LoadImage(TCairoImageSurface(cairo.getTarget()).pixmap())
		cairo.Destroy()

		Local s:Double = 24
		If t = missileType Then s = 16
		cairo = TCairo.Create(TCairoImageSurface.CreateForPixmap(s, s))
		cairo.SetSourceRGBA(rT, gT, bT, 1.0)
		cairo.Arc(s / 2.0, s / 2.0, s / 2.0, 0, 360)
		cairo.Fill()
		projectileImg = LoadImage(TCairoImageSurface(cairo.getTarget()).pixmap())
		cairo.Destroy()
	End Method 

End Type



