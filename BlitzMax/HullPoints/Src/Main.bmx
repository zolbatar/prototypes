SuperStrict
Import "ChooserFleet.bmx"
Import "ChooserMission.bmx"
Import "GameData.bmx"
Import "GFX.bmx"
Import "Helper.bmx"
Import "Starfield.bmx"

' find Src/*.bmx -type f -exec wc -l {} \; | awk '{total += $1} END{print total}'

Local p:Program = New Program
p.Main()

Type Program	
	Field width:Int = 1300, height:Int = 650

	Method Main()	
		SeedRnd(MilliSecs())
		Local t:TImageFont = LoadImageFont("Res/Depleted Uranium.ttf", 150)
		Local gfx:TGFX = TGFX.Create(width, height)
		Local gd:TGameData = TGameData.CreateWithLoad(gfx, t)
		gd.sf = TStarfield.Create(gfx, gd.stars)
		Local m:Double = gfx.width * 0.2
		Local r:Double = ((m * m) +  (0.25 * (gfx.width * gfx.width))) / (2 * m) 'r = (m² + ¼c²)/2m

		' Key
		Local planetIndex:Int = 6
		SetColor(255, 255, 255)
		gd.sf.p = MilliSecs()
		While Not KeyHit(KEY_Q)
			gd.sf.img = 0
			gd.sf.Render(1.0)
			Planet(gfx, gd, planetIndex, gd.sf.r, r * 2, m)
			SetColor(255, 255, 255)
			SetImageFont(t)
			DrawText("Hull Points", (gfx.width / 2) - (TextWidth("HULL POINTS") / 2), 50)
			gfx.CenteredText(TGFX.FontXXLarge, "1 - Fleet Design", gfx.height - 450)
			gfx.CenteredText(TGFX.FontXXLarge, "2 - Mission Builder", gfx.height - 350)
			gfx.CenteredText(TGFX.FontXXLarge, "P - Play", gfx.height - 250)
			gfx.CenteredText(TGFX.FontXXLarge, "Q - Quit", gfx.height - 150)
'			SetColor(255, 255, 0)
'			gfx.CenteredText(TGFX.FontLarge, "A Bee Zombie Games Production", gfx.height - 50)
			gfx.UIScanlines()
			Flip()

			If KeyHit(KEY_1) Then TChooserFleet.Start(gfx, gd)
			If KeyHit(KEY_2) Then TChooserMission.Start(gfx, gd)
'			If KeyHit(KEY_A) Then planetIndex :+ 1
			
			PollSystem()
			gd.sf.Cycle()
		End While
	End Method
	
	Function Planet(gfx:TGFX, gd:TGameData, index:Int, r:Double, rL:Double, m:Double)
		SetRotation(r)
		SetScale(rL / 1024, rL / 1024)
		DrawImage(gd.planets[index], gfx.width / 2, -gfx.height + m)
		SetScale(1.0, 1.0)
		SetRotation(0)
	End Function
	
End Type
