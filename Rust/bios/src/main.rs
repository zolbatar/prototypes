use crate::graphics::init::init_ggez;
use crate::graphics::lcd::{convert_and_render, create_lcd};
use crate::graphics::text::{load_font, render_text};
use ggez;
use ggez::event;
use ggez::graphics::Font;

mod constants;
mod graphics;

struct MainState {
    pos_x: f32,
    font_sans: Font,
}

impl MainState {
    fn new(ctx: &mut ggez::Context) -> ggez::GameResult<MainState> {
        let s = MainState {
            pos_x: 0.0,
            font_sans: load_font(ctx, "Roboto-Regular"),
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
        let canvas = create_lcd(ctx)?;
        render_text(ctx, self.font_sans, 100.0, "foo", 0.0, 0.0)?;
        convert_and_render(canvas, ctx)?;
        Ok(())
    }
}

pub fn main() {
    let (mut ctx, mut event_loop) = init_ggez();

    // Create game state
    let mut state = MainState::new(&mut ctx).unwrap();

    // Run!
    match event::run(&mut ctx, &mut event_loop, &mut state) {
        Ok(_) => println!("Exited cleanly."),
        Err(e) => println!("Error occured: {}", e),
    }
}
