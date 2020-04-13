extends Node2D

func _ready():
	pass
	
func _process(delta):
	var image = find_node("viewportAC").get_texture().get_data()
	print(image)
	image.lock()
	for y in range(0,10):
		for x in range(0,10):
			var p = image.get_pixel(x, y)
			print(p)
	image.unlock()
	pass
	
func _draw():
	pass # Replace with function body.
