use crate::dispatcher::create_dispatch;
use crate::graphics::graphics_run;
use crate::model::game::register_resources;
use crate::model::world::create_world;
use crate::map::init::build_map;

mod dispatcher;
mod graphics;
mod map;
mod model;
mod systems;

fn main() {
    let mut world = create_world();
    let map = build_map();
    register_resources(&mut world);
    let dispatcher = create_dispatch();
    graphics_run(dispatcher, world, map);
}
