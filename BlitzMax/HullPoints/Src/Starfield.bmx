SuperStrict
Import "GFX.bmx"

Type TStarField
	Field stars:TImage[]
	Field w:Int, h:Int, img:Int, r:Double, p:Long, x:Double, y:Double
	
	Function Create:TStarField(gfx:TGFX, stars:TImage[])
		Local o:TStarField = New TStarField
		o.stars = stars
		o.w = gfx.width
		o.h = gfx.height
		Return o
	End Function
	
	Method SetRandomImage()
		img = Rand(stars.Length - 1)
	End Method
	
	Method PanCycle(x:Double, y:Double)
		Self.x :+ x / 10
		Self.y :+ y / 10
	End Method

	Method Render(zoom:Double)
		SetBlend(SOLIDBLEND)
		SetColor(48, 48, 48)
		SetOrigin((w / 2) + x, (h / 2) + y)
		SetScale(zoom, zoom)
		DrawImage(stars[img], 0, 0)
		SetScale(1, 1)
		SetOrigin(0, 0)
		SetBlend(ALPHABLEND)
		SetColor(255, 255, 255)
	End Method
	
	Method Cycle()
		r :+ Double(MilliSecs() - p) * 0.00025
		p = MilliSecs()
	End Method

End Type
