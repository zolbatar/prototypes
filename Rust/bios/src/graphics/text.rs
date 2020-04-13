use ggez;
use ggez::error::GameResult;
use ggez::graphics;
use ggez::graphics::{Font, Scale, Text};
use ggez::nalgebra as na;

pub fn load_font(ctx: &mut ggez::Context, font: &str) -> Font {
    Font::new(ctx, format!("/fonts/{}.ttf", font)).unwrap()
}

pub fn render_text(ctx: &mut ggez::Context, font: Font, size: f32, text: &str, x: f32, y: f32) -> GameResult {
    let mut text = Text::new(text);
    text.set_font(font, Scale::uniform(size));
    graphics::draw(ctx, &text, (na::Point2::new(x, y),))?;
    Ok(())
}
