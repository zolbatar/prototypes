use crate::map::model::{Map, MAP_SIZE, VOXEL_MAX};
use rand::Rng;

pub fn build_map() -> Map {
    // Empty map
    let mut map = Map {
        voxels: [0; MAP_SIZE],
    };

    // Create some random blocks for testing
    let mut rng = rand::thread_rng();
    for x in 0..MAP_SIZE {
        map.voxels[x] = rng.gen_range(0, VOXEL_MAX);
    }

    map
}
