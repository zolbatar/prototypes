use sdl2::event::Event;
use sdl2::keyboard::Keycode;
use std::time::Duration;

mod gfx;

pub fn main() {
    let sdl_context = sdl2::init().unwrap();
    let mut gfx_context = gfx::setup(sdl_context);
    gfx::clear(&mut gfx_context);
    let mut event_pump = sdl_context.event_pump().unwrap();
    let mut i = 0;
    'running: loop {
        /*        i = (i + 1) % 255;
                canvas.set_draw_color(Color::RGB(i, 64, 255 - i));
                canvas.clear();
                for event in event_pump.poll_iter() {
                    match event {
                        Event::Quit { .. }
                        | Event::KeyDown {
                            keycode: Some(Keycode::Escape),
                            ..
                        } => break 'running,
                        _ => {}
                    }
                }
                // The rest of the game loop goes here...
        */
        gfx::present(&mut gfx_context);
        ::std::thread::sleep(Duration::new(0, 1_000_000_000u32 / 60));
    }
}
