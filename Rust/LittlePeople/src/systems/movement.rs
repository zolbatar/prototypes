use crate::model::game::{get_deltatime, DeltaTime};
use crate::model::position::{Destination, Position};
use specs::join::Join;
use specs::{Read, ReadStorage, System, WriteStorage};

pub struct Movement {}

impl Movement {
    pub fn init() -> Movement {
        Movement {}
    }
}

impl<'a> System<'a> for Movement {
    type SystemData = (
        Read<'a, DeltaTime>,
        ReadStorage<'a, Destination>,
        WriteStorage<'a, Position>,
    );

    fn run(&mut self, data: Self::SystemData) {
        let (delta, destination, mut position) = data;
        let delta = get_deltatime(&delta);
        for (destination, position) in (&destination, &mut position).join() {
            println!("Hello, {:?}", &position);
        }
    }
}
