use crate::map::model::{Map, MAP_SIZE, MAP_X, MAP_Y, MAP_Z, VOXEL_MAX};
use ggez;
use ggez::graphics;
use ggez::nalgebra as na;
use ggez::Context;

const SPACING: f32 = 10.0;

pub fn render_map(ctx: &mut Context, map: &Map, screen_width: usize, screen_height: usize) {
    let circle = graphics::Mesh::new_circle(
        ctx,
        graphics::DrawMode::fill(),
        na::Point2::new(0.0, 0.0),
        2.0,
        2.0,
        graphics::WHITE,
    )
    .unwrap();

    // Work out position adjustment
    let x_adjust = (screen_width as f32 / 2.0) - (MAP_X as f32 / 2.0 * SPACING);
    let z_adjust = (screen_height as f32 / 2.0) - (MAP_Z as f32 / 2.0 * SPACING);

    for x in 0..MAP_X {
        for z in 0..MAP_Z {
            for y in 0..MAP_Y {
                let index = (x * MAP_Z) + (y * MAP_X * MAP_Z);
                let voxel = map.voxels[index];

                let p = na::Point2::new(x as f32 * SPACING + x_adjust, z as f32 * SPACING + z_adjust);
                graphics::draw(ctx, &circle, (p,)).unwrap();
            }
        }
    }
}
