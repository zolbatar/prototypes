use crate::model::game::LittlePeople;
use specs::prelude::*;
use specs::{Dispatcher, DispatcherBuilder};

pub fn create_dispatch() -> Dispatcher<'static, 'static> {
    let dispatcher = DispatcherBuilder::new()
        .with(LittlePeople::init(), "little_people", &[])
        .build();
    dispatcher
}

pub fn run_dispatch(dispatcher: &mut Dispatcher, world: &mut World) {
    dispatcher.dispatch(world);
    world.maintain();
}
