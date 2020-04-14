extends Node2D

func _ready():
	pass
	
func _process(delta):
	pass
	
func _draw():
	var texture = find_node("viewportAC").get_texture()
	print(texture.get_height())

	# Get pixels from panel
	var image = texture.get_data()
	var image_out = Image.new()
	image_out.create(402, 248, false, Image.FORMAT_RGBA8)
	image.lock()
	image_out.lock()
	for y in range(0,83):
		print(y * 3)
		for x in range(0,134):
			var p = image.get_pixel(x, y)
			var c = Color(0, 0, 0, 255)
			image_out.set_pixel(x * 3, y * 3, c)
			image_out.set_pixel(x * 3 + 1, y * 3, c)
			image_out.set_pixel(x * 3, y * 3 + 1, c)
			image_out.set_pixel(x * 3 + 1, y * 3 + 1, c)
	image.unlock()
	image_out.unlock()
	
	# Create texture to display
	var tex = ImageTexture.new()
	tex.create_from_image(image_out, ImageTexture.FLAG_FILTER)

	# Update sprite to show panel
	var sprite = find_node("panelSprite")
	sprite.set_texture(tex)
	pass # Replace with function body.
