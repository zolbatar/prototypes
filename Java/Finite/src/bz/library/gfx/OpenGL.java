package bz.library.gfx;

import java.nio.FloatBuffer;
import java.nio.ByteBuffer;
import org.lwjgl.glfw.*;
import org.lwjgl.BufferUtils;
import org.lwjgl.opengl.*;
import static org.lwjgl.glfw.Callbacks.*;
import static org.lwjgl.glfw.GLFW.*;
import static org.lwjgl.opengl.GL11.*;
import static org.lwjgl.system.MemoryUtil.*;
import bz.universe.World;

public class OpenGL {
    private final GLFWErrorCallback errorCallback;
    private GLFWKeyCallback   keyCallback;
    private long window;
    private static final FloatBuffer matrix = BufferUtils.createFloatBuffer(16);
    private static final float PI = (float)Math.PI;
    private static final float[] IDENTITY_MATRIX =
        new float[] {
                1.0f, 0.0f, 0.0f, 0.0f,
                0.0f, 1.0f, 0.0f, 0.0f,
                0.0f, 0.0f, 1.0f, 0.0f,
                0.0f, 0.0f, 0.0f, 1.0f };

    public OpenGL() {
        // Setup an error callback. The default implementation
        // will print the error message in System.err.
        glfwSetErrorCallback(errorCallback = errorCallbackPrint(System.err));

        // Initialize GLFW. Most GLFW functions will not work before doing this.
        if (glfwInit() != GL11.GL_TRUE) {
            throw new IllegalStateException("Unable to initialize GLFW");
        }
        
        // Configure window
        glfwDefaultWindowHints(); // optional, the current window hints are already the default
        glfwWindowHint(GLFW_VISIBLE, GL_FALSE); // the window will stay hidden after creation
        glfwWindowHint(GLFW_RESIZABLE, GL_TRUE); // the window will be resizable
    }
    
    public void Windowed(int width,int height) {
        // Create the window
        window = glfwCreateWindow(width, height, "Bee Zombie Games - Finite", NULL, NULL);
        if (window == NULL) {
            throw new RuntimeException("Failed to create the GLFW window");
        }
 
        // Setup a key callback. It will be called every time a key is pressed, repeated or released.
        glfwSetKeyCallback(window, keyCallback = new GLFWKeyCallback() {
            @Override
            public void invoke(long window, int key, int scancode, int action, int mods) {
                if ( key == GLFW_KEY_ESCAPE && action == GLFW_RELEASE )
                    glfwSetWindowShouldClose(window, GL_TRUE);
            }
        });

        // Get the resolution of the primary monitor
        ByteBuffer vidmode = glfwGetVideoMode(glfwGetPrimaryMonitor());

        // Center our window
        glfwSetWindowPos(
            window,
            (GLFWvidmode.width(vidmode) - width) / 2,
            (GLFWvidmode.height(vidmode) - height) / 2
        );
 
        // Make the OpenGL context current
        glfwMakeContextCurrent(window);
        // Enable v-sync
        glfwSwapInterval(1);
 
        // Make the window visible
        glfwShowWindow(window);

        // Setup context
        GLContext.createFromCurrent();
        glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
        GL11.glViewport(0, 0, width, height);
        GL11.glEnable(GL_DEPTH_TEST);
        glShadeModel (GL_SMOOTH);
        
        // Setup projection
        GL11.glMatrixMode(GL11.GL_PROJECTION);
        GL11.glLoadIdentity();
        gluPerspective(45, (float)width/(float)height, 1.0f, 200.0f);
        GL11.glMatrixMode(GL11.GL_MODELVIEW);    
    }
    
    public void Close() {
        glfwDestroyWindow(window);
        keyCallback.release();
    }
    
    public void Terminate() {
        glfwTerminate();
        errorCallback.release();
    }
    
    public void RenderStart() {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }
    
    public void RenderEnd() {
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    
    public boolean CheckForClose() {
        return glfwWindowShouldClose(window) == GL_TRUE;
    }
    
    public void AddCube(float x, float y, float z, float size, Colour c) {
        AddCube(x, y, z, size, c, c, c, c, c, c);
    }
    
    public void AddCube(float x, float y, float z, float size, Colour c1, Colour c2, Colour c3, Colour c4, Colour c5, Colour c6) {
        GL11.glLoadIdentity();    
        GL11.glTranslatef(x, y, z);
        GL11.glScalef(World.STANDARD_SCALE * size, World.STANDARD_SCALE * size, World.STANDARD_SCALE * size);
//        GL11.glRotatef(x++, 1, 1, 1);
        GL11.glBegin(GL11.GL_QUADS);
        
        // Top
        GL11.glColor3f(c1.GetRed(), c1.GetGreen(), c1.GetBlue());
        GL11.glVertex3f( 1.0f, 1.0f,-1.0f);
        GL11.glVertex3f(-1.0f, 1.0f,-1.0f);
        GL11.glVertex3f(-1.0f, 1.0f, 1.0f);
        GL11.glVertex3f( 1.0f, 1.0f, 1.0f);
        
        // Bottom
        GL11.glColor3f(c2.GetRed(), c2.GetGreen(), c2.GetBlue());
        GL11.glVertex3f( 1.0f,-1.0f, 1.0f);
        GL11.glVertex3f(-1.0f,-1.0f, 1.0f);
        GL11.glVertex3f(-1.0f,-1.0f,-1.0f);
        GL11.glVertex3f( 1.0f,-1.0f,-1.0f);

        // Front
        GL11.glColor3f(c3.GetRed(), c3.GetGreen(), c3.GetBlue());
        GL11.glVertex3f( 1.0f, 1.0f, 1.0f);
        GL11.glVertex3f(-1.0f, 1.0f, 1.0f);
        GL11.glVertex3f(-1.0f,-1.0f, 1.0f);
        GL11.glVertex3f( 1.0f,-1.0f, 1.0f);
        
        // Back
        GL11.glColor3f(c4.GetRed(), c4.GetGreen(), c4.GetBlue());
        GL11.glVertex3f( 1.0f,-1.0f,-1.0f);
        GL11.glVertex3f(-1.0f,-1.0f,-1.0f);
        GL11.glVertex3f(-1.0f, 1.0f,-1.0f);
        GL11.glVertex3f( 1.0f, 1.0f,-1.0f);

        // Left
        GL11.glColor3f(c5.GetRed(), c5.GetGreen(), c5.GetBlue());
        GL11.glVertex3f(-1.0f, 1.0f, 1.0f);
        GL11.glVertex3f(-1.0f, 1.0f,-1.0f);
        GL11.glVertex3f(-1.0f,-1.0f,-1.0f);
        GL11.glVertex3f(-1.0f,-1.0f, 1.0f);

        // Right
        GL11.glColor3f(c6.GetRed(), c6.GetGreen(), c6.GetBlue());
        GL11.glVertex3f( 1.0f, 1.0f,-1.0f);
        GL11.glVertex3f( 1.0f, 1.0f, 1.0f);
        GL11.glVertex3f( 1.0f,-1.0f, 1.0f);
        GL11.glVertex3f( 1.0f,-1.0f,-1.0f);

        GL11.glEnd();
    }
    
    private static void __gluMakeIdentityf(FloatBuffer m) {
        int oldPos = m.position();
        m.put(IDENTITY_MATRIX);
        m.position(oldPos);
    }

    public static void gluPerspective(float fovy, float aspect, float zNear, float zFar) {
        float sine, cotangent, deltaZ;
        float radians = fovy / 2 * PI / 180;

        deltaZ = zFar - zNear;
        sine = (float) Math.sin(radians);

        if ((deltaZ == 0) || (sine == 0) || (aspect == 0)) {
                return;
        }

        cotangent = (float) Math.cos(radians) / sine;

        __gluMakeIdentityf(matrix);

        matrix.put(0 * 4 + 0, cotangent / aspect);
        matrix.put(1 * 4 + 1, cotangent);
        matrix.put(2 * 4 + 2, - (zFar + zNear) / deltaZ);
        matrix.put(2 * 4 + 3, -1);
        matrix.put(3 * 4 + 2, -2 * zNear * zFar / deltaZ);
        matrix.put(3 * 4 + 3, 0);

        glMultMatrix(matrix);
    }
    
}
