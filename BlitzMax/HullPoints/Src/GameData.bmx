SuperStrict
Import "Buttons.bmx"
Import "Colour.bmx"
Import "Fleet.bmx"
Import "GFX.bmx"
Import "Piece.bmx"
Import "Profiler.bmx"
Import "Sound.bmx"
Import "Starfield.bmx"
Import "Vessel.bmx"
Import "WeaponClass.bmx"

' 0: Debris = 40
' 1: Blast = 40
' 2: Dark small blast = 32
' 3: Nuke = 64
' 4: Ship destroy = 48

Type TGameData
	Const Steps:Int = 54
	Const NoPlanets:Int = 9, NoStars:Int = 9, NoAsteroids:Int = 9, NoExplosions:Int = 5, ToolbarHeight:Int = 60, OverlayWidth:Int = 180, SnapSize:Double = 24.0, MiniMapWidth:Int = 250
	Field planets:TImage[], stars:TImage[], asteroids:TImage[], sound:TGameSound
	Field pieces:TPiece[]
	Field fleetColours:TColour[3], pos:Int, lastTime:Long
	Field sf:TStarField, buttons:TButtons, fleets:TList, weapons:TWeaponClass[]
	Field defaultOnOff:Int[,], defaultCondition:Double[,], defaultAutoFire:Double[,]
	Field spinner:TImage, spinner2:TImage, targeter:TImage, player1Icon:TImage, player2Icon:TImage, shield:TImage, hull:TImage
	Field exhaust1:TImage, exhaust2:TImage, missileFlame:TImage, railgunFlame:TImage
	Field missile:TImage, shrapnel:TImage
	Field explosions:TImage[], explosionSizes:Int[] = [40, 40, 32, 64, 48], halo:TImage, warp:TImage, electric:TImage

	Function Create:TGameData(gfx:TGFX, t:TImageFont)
		Local gd:TGameData = New TGameData
		gd.fleets = CreateList()
		gd.Common(gfx, t)
		Return gd
	End Function
	
	Function CreateWithLoad:TGameData(gfx:TGFX, t:TImageFont)
		Local gd:TGameData = New TGameData
		gd.fleets = CreateList()
		gd.Common(gfx, t)
		gd.LoadGD()
		Return gd	
	End Function
	
	Method Common(gfx:TGFX, t:TImageFont)
		?debug
   			TProfiler.Enter("GameData::Common")
  		?
		lastTime = MilliSecs()
		fleetColours[0] = TColour.Create(113, 113, 198)
		fleetColours[1] = TColour.Create(240, 128, 128)
		fleetColours[2] = TColour.Create(255, 255, 255)
		LoadPlanetsStarsAsteroids(gfx, t)
		sound = TGameSound.Create()
		RenderStatus(gfx, t)
		buttons = TButtons.Create()
		RenderStatus(gfx, t)
		pieces = CreatePieceArray()
		RenderStatus(gfx, t)
		weapons = TWeaponClass.Create()
		RenderStatus(gfx, t)
		defaultOnOff = TVessel.BuildOnOffArray()
		defaultCondition = TVessel. BuildConditionArray()
		defaultAutoFire = TVessel.BuildAutofireArray()
		RenderStatus(gfx, t)
		halo = LoadAnimImage("Res/Effects/Halo.png", 512, 512, 0, 8, FILTEREDIMAGE|MIPMAPPEDIMAGE)
		RenderStatus(gfx, t)
		warp = LoadAnimImage("Res/Effects/WarpPoint.png", 256, 256, 0, 16, FILTEREDIMAGE|MIPMAPPEDIMAGE)
		RenderStatus(gfx, t)
		electric = LoadAnimImage("Res/Effects/Electric.png", 256, 256, 0, 16, FILTEREDIMAGE|MIPMAPPEDIMAGE)
		RenderStatus(gfx, t)
		missile = LoadImage("Res/MissileShot.png", FILTEREDIMAGE|MIPMAPPEDIMAGE)
		RenderStatus(gfx, t)
		shrapnel = LoadImage("Res/Shrapnel.png", FILTEREDIMAGE|MIPMAPPEDIMAGE)
		RenderStatus(gfx, t)
		shield = LoadImage("Res/Shield.png", FILTEREDIMAGE|MIPMAPPEDIMAGE)
		RenderStatus(gfx, t)
		hull = LoadImage("Res/Hull.png", FILTEREDIMAGE|MIPMAPPEDIMAGE)
		RenderStatus(gfx, t)
		spinner = LoadImage("Res/Spinner.png", FILTEREDIMAGE|MIPMAPPEDIMAGE)
		RenderStatus(gfx, t)
		spinner2 = LoadImage("Res/Spinner2.png", FILTEREDIMAGE|MIPMAPPEDIMAGE)
		RenderStatus(gfx, t)
		targeter = LoadImage("Res/Targeter.png", FILTEREDIMAGE|MIPMAPPEDIMAGE)
		RenderStatus(gfx, t)
		player1Icon = LoadImage("Res/Player1Icon.png", FILTEREDIMAGE|MIPMAPPEDIMAGE)
		RenderStatus(gfx, t)
		player2Icon = LoadImage("Res/Player2Icon.png", FILTEREDIMAGE|MIPMAPPEDIMAGE)
		RenderStatus(gfx, t)
		exhaust1 = LoadAnimImage("Res/Effects/Exhaust1.png", 128, 128, 0, 32, FILTEREDIMAGE|MIPMAPPEDIMAGE)
		RenderStatus(gfx, t)
		exhaust2 = LoadAnimImage("Res/Effects/Exhaust2.png", 128, 128, 0, 32, FILTEREDIMAGE|MIPMAPPEDIMAGE)
		RenderStatus(gfx, t)
		missileFlame = LoadImage("Res/MissileFlame.png", FILTEREDIMAGE|MIPMAPPEDIMAGE)
		RenderStatus(gfx, t)
		railgunFlame = LoadImage("Res/RailgunFlame.png", FILTEREDIMAGE|MIPMAPPEDIMAGE)
		RenderStatus(gfx, t)
		explosions = New TImage[NoExplosions]
		RenderStatus(gfx, t)
		For Local i:Int = 0 To NoExplosions - 1
			explosions[i] = LoadAnimImage("Res/Effects/Explosion" + (i + 1) + ".png", 128, 128, 0, explosionSizes[i], FILTEREDIMAGE|MIPMAPPEDIMAGE)
			RenderStatus(gfx, t)
		Next
		?debug
   			TProfiler.Leave("GameData::Common")
  		?
	End Method
	
	Method LoadPlanetsStarsAsteroids(gfx:TGFX, t:TImageFont)
		?debug
   			TProfiler.Enter("GameData::LoadPlanetsStarsAsteroids")
  		?
		planets = New TImage[noPlanets]
		stars = New TImage[noStars]
		asteroids = New TImage[noAsteroids]
		For Local i:Int = 0 To NoStars - 1
			stars[i] = LoadImage("Res/Stars/Star" + (i + 1) + ".png", FILTEREDIMAGE)
			RenderStatus(gfx, t)
		Next
		For Local i:Int = 0 To NoPlanets - 1
			planets[i] = LoadImage("Res/Planets/Planet" + (i + 1) + ".png", FILTEREDIMAGE)
			RenderStatus(gfx, t)
		Next
		For Local i:Int = 0 To NoAsteroids - 1
			asteroids[i] = LoadImage("Res/Asteroids/Asteroid" + (i + 1) + ".png", FILTEREDIMAGE)
			RenderStatus(gfx, t)
		Next
		?debug
   			TProfiler.Leave("GameData::LoadPlanetsStarsAsteroids")
  		?
	End Method
	
	Method RenderStatus(gfx:TGFX, t:TImageFont)
		?debug
   			TProfiler.Enter("GameData::RenderStatus")
  		?
'		Print "Time (" + pos + "): " + (MilliSecs() - lastTime)
'		lastTime = MilliSecs()
		Cls
		SetBlend(SOLIDBLEND)
		SetColor(48, 48, 48)
		SetOrigin(gfx.width / 2, gfx.height / 2)
		SetScale(1, 1)
		DrawImage(stars[0], 0, 0)
		SetOrigin(0, 0)
		SetBlend(ALPHABLEND)
		SetColor(255, 255, 255)
		SetImageFont(t)
		DrawText("Hull Points", (gfx.width / 2) - (TextWidth("HULL POINTS") / 2), 100)

		' Progress
		Local prop:Double = Double(pos) / Double(TGameData.Steps)
		SetColor(113, 113, 198)
		SetAlpha(0.5)
		DrawRect((gfx.width / 2) - 250, gfx.height - 50, 500.0, 20)
		SetAlpha(1.0)
		DrawRect((gfx.width / 2) - 250, gfx.height - 50, prop * 500.0, 20)

		SetColor(255, 255, 0)
		gfx.CenteredText(TGFX.FontXLarge, "Loading...please wait", (gfx.height / 2) - 25)

'		SetColor(255, 255, 0)
'		gfx.CenteredText(TGFX.FontLarge, "A Bee Zombie Games Production", gfx.height - 50)
		gfx.UIScanlines()
		Flip
		pos :+ 1
		?debug
   			TProfiler.Leave("GameData::RenderStatus")
  		?
	End Method

	Method LoadGD()
		?debug
   			TProfiler.Enter("GameData::LoadGD")
  		?

		' Load fleets
		For Local f:String = EachIn ListFiles(CurrentDir() + "/Fleet/", "flt", CreateList())
			Print "Loading fleet: " + f
			Local file:TStream = ReadFile(f)
			If Not file RuntimeError "Failed to load " + f
			Local fleet:TFleet = TFleet.LoadFleet(file, f, pieces)
			ListAddLast(fleets, fleet)
			CloseStream file
		Next
		?debug
   			TProfiler.Leave("GameData::LoadGD")
  		?
	End Method
	
	Method SaveGD()
		?debug
   			TProfiler.Enter("GameData::SaveGD")
  		?
		For Local fleet:TFleet = EachIn fleets
			fleet.SaveFleet()
		Next
		?debug
   			TProfiler.Leave("GameData::SaveGD")
  		?
	End Method

End Type


