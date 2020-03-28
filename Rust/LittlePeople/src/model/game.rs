use specs::prelude::*;

#[derive(Default)]
pub struct DeltaTime(f64);

pub fn register_resources(world: &mut World) {
    world.insert(DeltaTime(0.00));
}

pub fn set_deltatime(world: &mut World, time: f64) {
    println!("{}", time);
    let mut delta = world.write_resource::<DeltaTime>();
    *delta = DeltaTime(time);
}

pub fn get_deltatime(d: &DeltaTime) -> f64 {
    d.0
}
