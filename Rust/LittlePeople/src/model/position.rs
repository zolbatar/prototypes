use specs::{prelude::*, Component};

const BLOCK_FRACTIONS: i32 = 8;

#[derive(Component)]
#[storage(VecStorage)]
pub struct Position {
    x: i32,
    y: i32,
    z: i32,
    fraction_x: i32,
    fraction_y: i32,
    fraction_z: i32,
}

impl Position {
    pub fn init(x: i32, y: i32, z: i32) -> Position {
        Position {
            x,
            y,
            z,
            fraction_x: BLOCK_FRACTIONS / 2,
            fraction_y: BLOCK_FRACTIONS / 2,
            fraction_z: 0,
        }
    }
}

#[derive(Component)]
#[storage(VecStorage)]
pub struct Destination {
    x: i32,
    y: i32,
    z: i32,
}

impl Destination {
    pub fn init(x: i32, y: i32, z: i32) -> Destination {
        Destination { x, y, z }
    }
}
