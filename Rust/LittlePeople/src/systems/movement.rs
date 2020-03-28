use crate::model::game::LittlePeople;
use crate::model::position::{Destination, Position};
use specs::{ReadStorage, System};

impl<'a> System<'a> for LittlePeople {
    type SystemData = ReadStorage<'a, Position>;

    fn run(&mut self, position: Self::SystemData) {
        use specs::Join;

        for position in position.join() {
            println!("Hello, {:?}", &position);
        }
    }
}
