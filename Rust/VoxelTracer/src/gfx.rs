use sdl2::pixels::Color;
use sdl2::video::Window;
use sdl2::render::WindowCanvas;

pub struct GfxContext {
    pub window: Window,
    pub canvas: WindowCanvas,
}

pub fn setup(sdl_context: sdl2::Sdl) -> &'static GfxContext {
    let video_subsystem = sdl_context.video().unwrap();

    let window = video_subsystem
        .window("Some Graphical Thingy", 800, 600)
        .position_centered()
        .build()
        .unwrap();
    let mut canvas = window.into_canvas().build().unwrap();
    &GfxContext { window, canvas }
}

pub fn clear(context: &mut GfxContext) {
    context.canvas.set_draw_color(Color::RGB(0, 255, 255));
    context.canvas.clear();
}

pub fn present(context: &mut GfxContext) {
    context.canvas.present();
}
