use crate::dispatcher::create_dispatch;
use crate::graphics::graphics_run;
use crate::model::game::register_resources;
use crate::model::world::create_world;

mod dispatcher;
mod graphics;
mod model;
mod systems;

fn main() {
    // Init
    let mut world = create_world();
    register_resources(&mut world);
    let dispatcher = create_dispatch();
    graphics_run(dispatcher, world);
}
