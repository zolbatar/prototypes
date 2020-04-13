use crate::constants::{RENDER_SIZE_HEIGHT, RENDER_SIZE_WIDTH};
use ggez::conf::NumSamples;
use ggez::error::GameResult;
use ggez::graphics;
use ggez::graphics::{set_canvas, Canvas, Color, Rect};
use ggez::nalgebra as na;

pub fn create_lcd(ctx: &mut ggez::Context) -> GameResult<Canvas> {
    // Create a canvas to draw to, we do "magic" to make this look like an LCD
    let canvas = Canvas::new(ctx, RENDER_SIZE_WIDTH, RENDER_SIZE_HEIGHT, NumSamples::One)?;
    set_canvas(ctx, Some(&canvas));

    // Set background colour to an LCD type gray
    //    #[cfg(feature = "lcd-grey")]
    //    graphics::clear(ctx, [0.67, 0.75, 0.72, 1.0].into());
    //    #[cfg(feature = "lcd-green")]
    //   graphics::clear(ctx, [0.60, 0.63, 0.0, 1.0].into());

    Ok(canvas)
}

pub fn convert_and_render(canvas: Canvas, ctx: &mut ggez::Context) -> GameResult {
    let rect = graphics::Mesh::new_rectangle(
        ctx,
        graphics::DrawMode::fill(),
        Rect {
            x: 0.0,
            y: 0.0,
            w: 32.0,
            h: 32.0,
        },
        Color::from_rgba(255, 0, 0, 255),
    )?;
    graphics::draw(ctx, &rect, (na::Point2::new(0.0, 0.0),))?;

    // Set back to drawing on actual render surface
    set_canvas(ctx, None);

    // Consume the canvas
    let image = canvas.into_inner();
    dbg!(&image);
    let pixels = image.to_rgba8(ctx)?;

    // Now we go through EACH pixel in the saved canvas and render it to screen
    //let pixels = canvas.image().to_rgba8(ctx)?;
    for pixel in pixels {
        print!("{} ", pixel);
    }
    std::process::exit(0);

    graphics::draw(ctx, &canvas, (na::Point2::new(0.0, 0.0),))?;

    // Now present so the user can see something!
    graphics::present(ctx)?;
    Ok(())
}
