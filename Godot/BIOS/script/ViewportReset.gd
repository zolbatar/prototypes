extends Viewport

var cum_time = 0
var texRandom = null
var texOn = null
var texOff = null

func _ready():
	
	# Create all pixels on
	var image = Image.new()
	image.create(Rasterise.GRID_X, Rasterise.GRID_Y, false, Image.FORMAT_RGBA8)
	image.lock()
	for y in range(0, Rasterise.GRID_Y):
		for x in range(0, Rasterise.GRID_X):
			var c = Rasterise.level_to_rgba(Rasterise.LEVELS - 1)
			image.set_pixel(x, y, c)
	image.unlock()
	
	# Create texture to display
	texOn = ImageTexture.new()
	texOn.create_from_image(image, 0)

	# Create all pixels on
	image = Image.new()
	image.create(Rasterise.GRID_X, Rasterise.GRID_Y, false, Image.FORMAT_RGBA8)
	image.lock()
	for y in range(0, Rasterise.GRID_Y):
		for x in range(0, Rasterise.GRID_X):
			var c = Rasterise.level_to_rgba(0)
			image.set_pixel(x, y, c)
	image.unlock()
	
	# Create texture to display
	texOff = ImageTexture.new()
	texOff.create_from_image(image, 0)

	# Create random
	image = Image.new()
	image.create(Rasterise.GRID_X, Rasterise.GRID_Y, false, Image.FORMAT_RGBA8)
	image.lock()
	for y in range(0, Rasterise.GRID_Y):
		for x in range(0, Rasterise.GRID_X):
			var c = Rasterise.level_to_rgba(randi() % Rasterise.LEVELS)
			image.set_pixel(x, y, c)
	image.unlock()
	
	# Create texture to display
	texRandom = ImageTexture.new()
	texRandom.create_from_image(image, 0)

func _process(delta):
	cum_time += delta

func get_texture():
	if cum_time < 0.25:
		return texRandom
	elif cum_time < 0.4:
		return texOn
	elif cum_time < 0.5:
		return texOff
	else:
		Globals.screen = Globals.screen_after_reset
		return texOff

