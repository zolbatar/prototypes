use ggez;
use ggez::event;
use ggez::nalgebra as na;
use ggez::{conf, graphics, Context, ContextBuilder, GameResult};
use std::env;
use std::path;

struct MainState {
    pos_x: f32,
}

impl MainState {
    fn new() -> ggez::GameResult<MainState> {
        let s = MainState { pos_x: 0.0 };
        Ok(s)
    }
}

impl event::EventHandler for MainState {
    fn update(&mut self, _ctx: &mut ggez::Context) -> ggez::GameResult {
        self.pos_x = self.pos_x % 800.0 + 1.0;
        Ok(())
    }

    fn draw(&mut self, ctx: &mut ggez::Context) -> ggez::GameResult {
        graphics::clear(ctx, [0.1, 0.2, 0.3, 1.0].into());

        let circle = graphics::Mesh::new_circle(
            ctx,
            graphics::DrawMode::fill(),
            na::Point2::new(self.pos_x, 380.0),
            100.0,
            2.0,
            graphics::WHITE,
        )?;
        graphics::draw(ctx, &circle, (na::Point2::new(0.0, 0.0),))?;

        graphics::present(ctx)?;
        Ok(())
    }
}

pub fn main() {
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
    let cb = ContextBuilder::new("bios", "Bee Zombie Games")
        .window_mode(
            conf::WindowMode::default()
                .fullscreen_type(conf::FullscreenType::Windowed)
                .resizable(true)
                .dimensions(screen_width as f32, screen_height as f32),
        )
        .window_setup(conf::WindowSetup::default().title("BIOS").samples(
            conf::NumSamples::from_u32(1).expect("Option msaa needs to be 1, 2, 4, 8 or 16!"),
        ))
        .add_resource_path(resource_dir);

    // Build context
    let (mut ctx, mut event_loop) = cb.build().unwrap();

    // Dump out path info so we know where ggez is looking for stuff
    println!("Full filesystem info: {:#?}", ctx.filesystem);

    // Output renderer type
    println!("Renderer: {}", graphics::renderer_info(&ctx).unwrap());

    // Create game state
    let mut state = MainState::new().unwrap();

    // Run!
    match event::run(&mut ctx, &mut event_loop, &mut state) {
        Ok(_) => println!("Exited cleanly."),
        Err(e) => println!("Error occured: {}", e),
    }
}
