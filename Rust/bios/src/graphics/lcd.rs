use crate::constants::{RENDER_SIZE_HEIGHT, RENDER_SIZE_WIDTH};
use ggez::conf::NumSamples;
use ggez::error::GameResult;
use ggez::graphics;
use ggez::graphics::{set_canvas, Canvas};
use ggez::nalgebra as na;

pub fn create_lcd(ctx: &mut ggez::Context) -> GameResult<Canvas> {
    // Create a canvas to draw to, we do "magic" to make this look like an LCD
    let canvas = Canvas::new(ctx, RENDER_SIZE_WIDTH, RENDER_SIZE_HEIGHT, NumSamples::One)?;
    set_canvas(ctx, Some(&canvas));

    // Set background colour to an LCD type gray
    #[cfg(feature = "lcd-grey")]
    graphics::clear(ctx, [0.67, 0.75, 0.72, 1.0].into());
    #[cfg(feature = "lcd-green")]
    graphics::clear(ctx, [0.60, 0.63, 0.0, 1.0].into());

    Ok(canvas)
}

pub fn convert_and_render(canvas: &Canvas, ctx: &mut ggez::Context) -> GameResult {
    set_canvas(ctx, None);
    //        dbg!(&canvas.image());
    graphics::draw(ctx, canvas, (na::Point2::new(0.0, 0.0),))?;
    graphics::present(ctx)?;
    Ok(())
}
