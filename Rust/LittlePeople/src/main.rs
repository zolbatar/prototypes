use crate::model::world::create_world;

mod model;

fn main() {
    let mut world = create_world();
    let a = 10;
    println!("{}", a);
    println!("Hello, world!");
}
