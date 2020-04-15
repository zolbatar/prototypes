extends Node2D

func _ready():
	pass
	
func _process(delta):
	update()
	
func _draw():
	var viewport = null
	var tex = null
	if Globals.screen == "RESET":
		viewport = find_node("ViewportReset")
		tex = viewport.get_texture()
	elif Globals.screen == "AC":
		viewport = find_node("ViewportAC")
		tex = viewport.get_texture()
	else:
		print("Screen ", Globals.screen, " not found")

	# Get pixels from panel
	tex = Rasterise.rasterise(tex.get_data())
	
	# Update sprite to show panel
	var sprite = find_node("panelSprite")
	sprite.set_texture(tex)
