use crate::dispatcher::{create_dispatch, run_dispatch};
use crate::model::world::create_world;

mod dispatcher;
mod model;
mod systems;

fn main() {
    let mut world = create_world();
    let mut dispatcher = create_dispatch();
    run_dispatch(&mut dispatcher, &mut world);
    let a = 10;
    println!("{}", a);
    println!("Hello, world!");
}
