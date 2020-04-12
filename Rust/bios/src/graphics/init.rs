use crate::constants::{SCREEN_HEIGHT, SCREEN_WIDTH};
use ggez;
use ggez::event::EventsLoop;
use ggez::{conf, graphics, ContextBuilder};
use std::env;
use std::path;

pub fn init_ggez() -> (ggez::Context, EventsLoop) {
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
                .dimensions(SCREEN_WIDTH as f32, SCREEN_HEIGHT as f32),
        )
        .window_setup(
            conf::WindowSetup::default()
                .title("BIOS")
                .samples(conf::NumSamples::from_u32(1).unwrap()),
        )
        .add_resource_path(resource_dir);

    // Build context
    let (ctx, event_loop) = cb.build().unwrap();

    // Dump out path info so we know where ggez is looking for stuff
    println!("Full filesystem info: {:#?}", ctx.filesystem);

    // Output renderer type
    println!("Renderer: {}", graphics::renderer_info(&ctx).unwrap());

    (ctx, event_loop)
}
