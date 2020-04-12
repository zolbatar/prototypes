use ggez;
use ggez::conf::NumSamples;
use ggez::event;
use ggez::graphics::{set_canvas, Canvas, Font, Mesh, Scale, Text};
use ggez::nalgebra as na;
use ggez::{conf, graphics, ContextBuilder};
use std::env;
use std::path;

struct MainState {
    pos_x: f32,
    font_sans: Font,
}

impl MainState {
    fn new(ctx: &mut ggez::Context) -> ggez::GameResult<MainState> {
        let s = MainState {
            pos_x: 0.0,
            font_sans: Font::new(ctx, "/fonts/Roboto-Regular.ttf").unwrap(),
        };
        Ok(s)
    }
}

impl event::EventHandler for MainState {
    fn update(&mut self, _ctx: &mut ggez::Context) -> ggez::GameResult {
        self.pos_x = self.pos_x % 800.0 + 1.0;
        Ok(())
    }

    fn draw(&mut self, ctx: &mut ggez::Context) -> ggez::GameResult {
        // Create a canvas to draw to, we do "magic" to make this look like an LCD
        let canvas = Canvas::new(ctx, 280, 180, NumSamples::One).unwrap();
        set_canvas(ctx, Some(&canvas));
        graphics::clear(ctx, [0.67, 0.75, 0.72, 1.0].into());

        let circle = Mesh::new_circle(
            ctx,
            graphics::DrawMode::fill(),
            na::Point2::new(self.pos_x, 380.0),
            100.0,
            2.0,
            graphics::WHITE,
        )?;
        graphics::draw(ctx, &circle, (na::Point2::new(0.0, 0.0),))?;
        let mut text = Text::new("foo");
        text.set_font(self.font_sans, Scale::uniform(30.0));
        graphics::draw(ctx, &text, (na::Point2::new(0.0, 0.0),))?;

        // Render this off-screen image
        set_canvas(ctx, None);
        dbg!(&canvas.image());
        graphics::draw(ctx, &canvas, (na::Point2::new(0.0, 0.0),))?;

        graphics::present(ctx)?;
        Ok(())
    }
}

pub fn main() {
    let screen_width = 1366;
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
        .window_setup(
            conf::WindowSetup::default()
                .title("BIOS")
                .samples(conf::NumSamples::from_u32(1).unwrap()),
        )
        .add_resource_path(resource_dir);

    // Build context
    let (mut ctx, mut event_loop) = cb.build().unwrap();

    // Dump out path info so we know where ggez is looking for stuff
    println!("Full filesystem info: {:#?}", ctx.filesystem);

    // Output renderer type
    println!("Renderer: {}", graphics::renderer_info(&ctx).unwrap());

    // Create game state
    let mut state = MainState::new(&mut ctx).unwrap();

    // Run!
    match event::run(&mut ctx, &mut event_loop, &mut state) {
        Ok(_) => println!("Exited cleanly."),
        Err(e) => println!("Error occured: {}", e),
    }
}
