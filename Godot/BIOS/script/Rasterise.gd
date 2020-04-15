extends Node2D

const BLOCK_SIZE = 3;
const AREA_X = 980;
const AREA_Y = 556;
const GRID_X = AREA_X / BLOCK_SIZE;
const GRID_Y = AREA_Y / BLOCK_SIZE;

const LEVELS = 8; 
const STEP = 1.0 / LEVELS / 2
const LCD_COLOUR = Color(89.0 / 256.0, 108.0 / 256.0, 42.0 / 256.0)
#const LCD_COLOUR = Color(164.0 / 256.0, 183.0 / 256.0, 99.0 / 256.0)
const LCD_DARKEST = Color(0.0 / 256.0, 0.0 / 256.0, 0.0 / 256.0)
var levels = []

func _ready():
	print("Grid size: ", GRID_X, ",", GRID_Y)
	# Create cell colours
	for l in range(0, LEVELS):
		levels.push_back(LCD_COLOUR.linear_interpolate(LCD_DARKEST, (l + 1) * STEP))

func rasterise(image):
	var image_out = Image.new()
	image_out.create(AREA_X, AREA_Y, false, Image.FORMAT_RGBA8)
	image.lock()
	image_out.lock()
	for y in range(0, GRID_Y):
		for x in range(0, GRID_X):
			var c = rgba_to_level(image.get_pixel(x, y))
			for block_y in range(0, BLOCK_SIZE - 0):
				for block_x in range(0, BLOCK_SIZE - 0):
					image_out.set_pixel(x * BLOCK_SIZE + block_x, y * BLOCK_SIZE + block_y, c)
	image.unlock()
	image_out.unlock()
	
	# Create texture to display
	var tex = ImageTexture.new()
	tex.create_from_image(image_out, 0)
	return tex
	
func rgba_to_level(c):
	var c_linear = 0.2126 * c[0] + 0.7152 * c[1] + 0.0722 * c[2] * c[3]
	var band = int(c_linear * LEVELS)
	return level_to_rgba(band)
	
func level_to_rgba(band):
	if band == 0:
		return Color("#00000000")
	band -= 1
	if band >= LEVELS:
		band = LEVELS - 1
	return levels[band]

