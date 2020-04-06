extends Spatial

var preScript = preload("res://scripts/softnoise.gd")
var rng = RandomNumberGenerator.new()
const NOISE_ADJUST = 0.1
const VOXEL_SIZE = 0.003
const VOXEL_SIZE_MULTIPLY = 2
const VOXEL_SCENE_SIZE = 192
const VOXEL_START = VOXEL_SCENE_SIZE / 2 * VOXEL_SIZE * VOXEL_SIZE_MULTIPLY

# Called when the node enters the scene tree for the first time.
func _ready():
	create_terrain()
	

# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta):
#	print("Delta:", delta)
	pass

func create_terrain():
	var softnoise = preScript.SoftNoise.new()
	for z in range(VOXEL_SCENE_SIZE):
		for x in range(VOXEL_SCENE_SIZE):
			
			# Calculate a random height
			var height: float = softnoise.openSimplex2D(x * NOISE_ADJUST, z * NOISE_ADJUST) * 10.0
			
			if height > 0:
				for y in range(0, height + 1):
					var voxel: MeshInstance = MeshInstance.new()
					voxel.mesh = CubeMesh.new()
					var material: SpatialMaterial = SpatialMaterial.new()
					material.set_albedo(Color.forestgreen)
					voxel.set_surface_material(0, material)
					voxel.translate(Vector3(
						VOXEL_START - x * VOXEL_SIZE * VOXEL_SIZE_MULTIPLY, 
						y * VOXEL_SIZE * VOXEL_SIZE_MULTIPLY, 
						VOXEL_START - z * VOXEL_SIZE * VOXEL_SIZE_MULTIPLY))
					voxel.set_scale(Vector3(VOXEL_SIZE, VOXEL_SIZE, VOXEL_SIZE))
					add_child(voxel)
			else:
					var voxel: MeshInstance = MeshInstance.new()
					voxel.mesh = CubeMesh.new()
					var material: SpatialMaterial = SpatialMaterial.new()
					material.set_albedo(Color.blue)
					voxel.set_surface_material(0, material)
					voxel.translate(Vector3(
						VOXEL_START - x * VOXEL_SIZE * VOXEL_SIZE_MULTIPLY, 
						0, 
						VOXEL_START - z * VOXEL_SIZE * VOXEL_SIZE_MULTIPLY))
					voxel.set_scale(Vector3(VOXEL_SIZE, VOXEL_SIZE, VOXEL_SIZE))
					add_child(voxel)
