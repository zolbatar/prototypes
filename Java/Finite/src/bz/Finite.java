package bz;

import bz.library.gfx.OpenGL;
import bz.universe.World;

public class Finite {
    private static OpenGL gl;
    private static World world;

    public static void Init() {
        gl = new OpenGL();
        gl.Windowed(1366, 768);
        world = new World();
    }
    
    public static void Start() {
        while (!gl.CheckForClose()) {
            gl.RenderStart();
            world.Render(gl);
            gl.RenderEnd();
        }
    }
    
    public static void main(String[] args) {
        try {
            Init();
            Start();
        } finally {
            // Ensure we shut down OpenGL properly
            if (gl != null) {
                gl.Terminate();
            }
        }
     }
    
}
