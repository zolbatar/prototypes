use crate::dispatcher::run_dispatch;
use crate::map::model::Map;
use crate::map::render::render_map;
use crate::model::game::set_deltatime;
use ggez::event::{self, EventHandler};
use ggez::graphics::Color;
use ggez::{conf, graphics, Context, ContextBuilder, GameResult};
use specs::prelude::*;
use specs::Dispatcher;
use std::env;
use std::path;
use std::time::SystemTime;

struct LittlePeopleGraphicsState {
    frames: u64,
    last_time: SystemTime,
    dispatcher: Dispatcher<'static, 'static>,
    world: World,
    colour_background: Color,
    map: Map,
    screen_width: usize,
    screen_height: usize,
}

impl LittlePeopleGraphicsState {
    pub fn new(
        _ctx: &mut Context,
        dispatcher: Dispatcher<'static, 'static>,
        world: World,
        map: Map,
        screen_width: usize,
        screen_height: usize,
    ) -> LittlePeopleGraphicsState {
        LittlePeopleGraphicsState {
            frames: 0,
            last_time: SystemTime::now(),
            dispatcher,
            world,
            map,
            screen_width,
            screen_height,
            colour_background: Color::new(0.1, 0.1, 0.1, 1.0),
        }
    }
}

impl EventHandler for LittlePeopleGraphicsState {
    fn update(&mut self, _ctx: &mut Context) -> GameResult<()> {
        let new_time = SystemTime::now();
        set_deltatime(
            &mut self.world,
            (new_time.duration_since(self.last_time).unwrap().as_nanos() as f64) / 1_000_000_000.0,
        );
        self.last_time = new_time;
        run_dispatch(&mut self.dispatcher, &mut self.world);
        Ok(())
    }

    fn draw(&mut self, ctx: &mut Context) -> GameResult<()> {
        graphics::clear(ctx, self.colour_background);
        self.frames += 1;
        render_map(ctx, &self.map, self.screen_width, self.screen_height);
        graphics::present(ctx)
    }
}

pub fn graphics_run(dispatcher: Dispatcher<'static, 'static>, world: World, map: Map) {
    let screen_width = 1024;
    let screen_height = 768;

    // Set resources folder
    let resource_dir = if let Ok(manifest_dir) = env::var("CARGO_MANIFEST_DIR") {
        let mut path = path::PathBuf::from(manifest_dir);
        path.push("resources");
        path
    } else {
        path::PathBuf::from("./resources")
    };

    // Create a context
    let cb = ContextBuilder::new("little_people", "Bee Zombie Games")
        .window_mode(
            conf::WindowMode::default()
                .fullscreen_type(conf::FullscreenType::Windowed)
                .resizable(true)
                .dimensions(screen_width as f32, screen_height as f32),
        )
        .window_setup(conf::WindowSetup::default().title("Little People").samples(
            conf::NumSamples::from_u32(1).expect("Option msaa needs to be 1, 2, 4, 8 or 16!"),
        ))
        .add_resource_path(resource_dir);

    // Build context
    let (mut ctx, mut event_loop) = cb.build().unwrap();

    // Dump out path info so we know where ggez is looking for stuff
    println!("Full filesystem info: {:#?}", ctx.filesystem);

    // Output renderer type
    println!("Renderer: {}", graphics::renderer_info(&ctx).unwrap());

    // Run!
    let mut my_game = LittlePeopleGraphicsState::new(
        &mut ctx,
        dispatcher,
        world,
        map,
        screen_width,
        screen_height,
    );

    // Run!
    match event::run(&mut ctx, &mut event_loop, &mut my_game) {
        Ok(_) => println!("Exited cleanly."),
        Err(e) => println!("Error occured: {}", e),
    }
}
