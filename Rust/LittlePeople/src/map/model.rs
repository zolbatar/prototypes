pub const MAP_X: usize = 1;//128;
pub const MAP_Y: usize = 1;//32;
pub const MAP_Z: usize = 1;//128;
pub const MAP_SIZE: usize = MAP_X * MAP_Y * MAP_Z;
pub const VOXEL_MAX: i8 = 32;

pub struct Map {
    pub voxels: [i8; MAP_SIZE],
}
