package bz.universe;

import java.util.Random;
import bz.library.gfx.OpenGL;
import bz.library.gfx.Colour;

public class World {
    public static final float STANDARD_SCALE = 0.1f;
    private static final Colour[] colour = new Colour[BlockTypes.values().length];
    private static final int SIZE_X = 10, SIZE_Y = 10, SIZE_Z = 10;
    private static final byte[][][] world = new byte[SIZE_X][SIZE_Y][SIZE_Z];
    
    public World() {
        Random r = new Random();
        
        // Build world
        for (int x = 0; x < SIZE_X; x++) {
            for (int y = 0; y < SIZE_Y; y++) {
                int h = r.nextInt(10);
                for (int z = 0; z < h; z++) {
                    world[x][y][z] = 1;
                }
            }
        }
        
        for (int i = 0; i < BlockTypes.values().length; i++) {
            colour[i] = new Colour(r.nextFloat(), r.nextFloat(), r.nextFloat());
        }
    }
    
    public void Render(OpenGL gl) {
        Random r = new Random();
        for (int x = 0; x < SIZE_X; x++) {
            for (int y = 0; y < SIZE_Y; y++) {
                for (int z = 0; y < SIZE_Z; y++) {
                    byte v = world[x][y][z];
                    if (v >= 1) {
                        gl.AddCube((float)x * STANDARD_SCALE, (float)y * STANDARD_SCALE, -(float)z * STANDARD_SCALE - 10.0f, 1.0f, colour[r.nextInt(6)]);
                    } else {
                        break;
                    }
                }
            }
        }
        gl.AddCube(2.5f, 2.5f, -20.0f, 1.0f, colour[0], colour[1], colour[2], colour[3], colour[4], colour[5]);
    }
}
