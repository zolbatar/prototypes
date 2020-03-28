use crate::model::person::Person;
use crate::model::position::{Destination, Position};
use specs::prelude::*;

fn register_components(world: &mut World) {
    world.register::<Person>();
    world.register::<Position>();
    world.register::<Destination>();
}

pub fn create_world() -> World {
    let mut world = World::new();
    register_components(&mut world);

    // Build map

    // Create people
    world
        .create_entity()
        .with(Position::init(0, 0, 0))
        .with(Destination::init(5, 5, 0))
        .build();

    world
}

/*pub fn run_world(world: &mut World) {
    let mut little_people = LittlePeople::init();
    little_people.run_now(&world);
    world.maintain();
}*/
