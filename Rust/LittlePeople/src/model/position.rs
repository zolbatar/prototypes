use specs::{prelude::*, Component};

#[derive(Component, Debug)]
#[storage(VecStorage)]
pub struct Position {
    x: i32,
    y: i32,
    z: i32,
    fraction_x: f32,
    fraction_y: f32,
    fraction_z: f32,
}

impl Position {
    pub fn init(x: i32, y: i32, z: i32) -> Position {
        Position {
            x,
            y,
            z,
            fraction_x: 0.5,
            fraction_y: 0.5,
            fraction_z: 0.0,
        }
    }
}

#[derive(Component)]
#[storage(VecStorage)]
#[allow(dead_code)]
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
