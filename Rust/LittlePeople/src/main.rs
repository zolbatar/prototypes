use crate::dispatcher::{create_dispatch, run_dispatch};
use crate::model::game::{register_resources, set_deltatime};
use crate::model::world::create_world;
use std::time::SystemTime;

mod dispatcher;
mod model;
mod systems;

fn main() {
    // Init
    let mut world = create_world();
    register_resources(&mut world);
    let mut dispatcher = create_dispatch();

    // Game loop
    let mut last_time = SystemTime::now();
    for _ in 0..10 {
        let new_time = SystemTime::now();
        set_deltatime(
            &mut world,
            (new_time.duration_since(last_time).unwrap().as_nanos() as f64) / 1_000_000_000.0,
        );
        last_time = new_time;
    }
    run_dispatch(&mut dispatcher, &mut world);
    let a = 10;
    println!("{}", a);
    println!("Hello, world!");
}
