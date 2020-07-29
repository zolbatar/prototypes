extends Node2D

func _ready():
	pass
	
func _process(_delta):
	update()
	
func _draw():
	# Get pixels from panel
	var viewport = get_viewport_for_screen()
	var tex = Rasterise.rasterise(viewport.get_texture().get_data())
	
	# Update sprite to show panel
	var sprite = find_node("SpritePanel")
	sprite.set_texture(tex)

func get_viewport_for_screen():
	var viewport = null
	if Globals.screen == "RESET":
		viewport = find_node("ViewportReset")
	elif Globals.screen == "AC":
		viewport = find_node("ViewportAC")
	else:
		print("Screen ", Globals.screen, " not found")
	return viewport

func _input(event):
	if event.is_action_type():
		var x = event.get_position().x - 475;
		var y = event.get_position().y - 225;
		print(x, " ", y)
