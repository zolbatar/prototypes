extends Node2D

const BLOCK_SIZE = 4;
const AREA_X = 980;
const AREA_Y = 556;
const GRID_X = AREA_X / BLOCK_SIZE;
const GRID_Y = AREA_Y / BLOCK_SIZE; 

func _ready():
	pass
	
func _process(delta):
	print("process")
	update()
	pass
	
func _draw():
	var texture = find_node("viewportAC").get_texture()

	# Get pixels from panel
	var image = texture.get_data()
	var image_out = Image.new()
	image_out.create(AREA_X, AREA_Y, false, Image.FORMAT_RGBA8)
	image.lock()
	var bytes = image.get_data()
	print(bytes.size())
#	for b in bytes:
#		print(b)
#	print("end")
	image_out.lock()
	for y in range(0, GRID_Y):
		for x in range(0, GRID_X):
			var p = image.get_pixel(x, y)
			var c = p#Color(0, 0, 0, 255)
			for block_y in range(0, BLOCK_SIZE - 1):
				for block_x in range(0, BLOCK_SIZE - 1):
					image_out.set_pixel(x * BLOCK_SIZE + block_x, y * BLOCK_SIZE + block_y, c)
	image.unlock()
	image_out.unlock()
	
	# Create texture to display
	var tex = ImageTexture.new()
	tex.create_from_image(image_out, ImageTexture.FLAG_FILTER)

	# Update sprite to show panel
	var sprite = find_node("panelSprite")
	sprite.set_texture(tex)
	pass # Replace with function body.
