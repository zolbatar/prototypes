use crate::map::model::{Map, MAP_SIZE, MAP_X, MAP_Y, MAP_Z, VOXEL_MAX};
use ggez;
use ggez::graphics::{draw, DrawMode, Mesh, MeshBuilder, WHITE};
use ggez::nalgebra as na;
use ggez::Context;

const SPACING: f32 = 50.0;

pub fn render_map(ctx: &mut Context, map: &Map, screen_width: usize, screen_height: usize) {
    let circle = Mesh::new_circle(
        ctx,
        DrawMode::fill(),
        na::Point2::new(0.0, 0.0),
        2.0,
        2.0,
        WHITE,
    )
    .unwrap();

    // Calculate steps
    let angle = 30_f32.to_radians();
    let x_increment = SPACING * angle.cos();
    let y_increment = SPACING * angle.sin();

    // Work out position adjustment
    let x_adjust = (screen_width as f32 / 2.0) - (MAP_X as f32 / 2.0 * x_increment);
    let z_adjust = (screen_height as f32 / 2.0) - (MAP_Z as f32 / 2.0 * y_increment);

    for x in 0..MAP_X {
        for z in 0..MAP_Z {
            for y in 0..MAP_Y {
                let index = (x * MAP_Z) + (y * MAP_X * MAP_Z);
                let voxel = map.voxels[index];

                // Position
                let screen_x = x as f32 * x_increment + x_adjust;
                let screen_y = z as f32 * y_increment + z_adjust;
                let p = na::Point2::new(screen_x, screen_y);
                //graphics::draw(ctx, &circle, (p,)).unwrap();

                // Construct a MeshBuilder with all 3 visible sides
                let mesh = MeshBuilder::new()
                    .polygon(
                        DrawMode::fill(),
                        &[
                            na::Point2::new(0.0, 0.0),
                            na::Point2::new(0.0 - x_increment, -y_increment),
                            na::Point2::new(0.0 - x_increment, -y_increment - SPACING),
                            na::Point2::new(0.0, -SPACING),
                            na::Point2::new(0.0, 0.0),
                        ],
                        WHITE,
                    )
                    .unwrap()
                    .polygon(
                        DrawMode::fill(),
                        &[
                            na::Point2::new(0.0, 0.0),
                            na::Point2::new(0.0 + x_increment, -y_increment),
                            na::Point2::new(0.0 + x_increment, -y_increment - SPACING),
                            na::Point2::new(0.0, -SPACING),
                            na::Point2::new(0.0, 0.0),
                        ],
                        WHITE,
                    )
                    .unwrap()
                    .polygon(
                        DrawMode::fill(),
                        &[
                            na::Point2::new(0.0, -SPACING),
                            na::Point2::new(0.0 - x_increment, -y_increment - SPACING),
                            na::Point2::new(0.0, -SPACING - SPACING),
                            na::Point2::new(0.0 + x_increment, -y_increment - SPACING),
                            na::Point2::new(0.0, -SPACING),
                        ],
                        WHITE,
                    )
                    .unwrap()
                    .build(ctx)
                    .unwrap();
                draw(ctx, &mesh, (p,)).unwrap();
            }
        }
    }
}
