package bz;

public class Parameters {
    public static final boolean PROFILE = true, VERBOSE = true;
 
    // Hash map
    public static final int CHASHMAP_INITIALCAPACITY = 64, CHASHMAP_CONCURRENCY = 4;
    public static final float CHASHMAP_LOADFACTOR = 0.9f;
    
    // Main menu, loading assets
    public static final int LOADING_STEPS = 2 + 8 + 8 + 8 + 4;
    public static final boolean SMOOTH = true;
    
    // Universe
    public static final double UNIVERSE_PADDING = 4.0;
    public static final int UNIVERSE_SECTIONS_X = 10, UNIVERSE_SECTIONS_Y = 10;

    // Map render
    public static final double RENDER_PADDING = 20;
    public static final double RENDER_SUN_SIZE = 30, RENDER_SUN_INNER = 25.0, RENDER_SUN_BORDER = 2.0;
    public static final double RENDER_PLANET_SPACING = 18, RENDER_PLANET_INITIALSPACE = 25;
    public static final double RENDER_PLANET_SIZE = 15, RENDER_PLANET_INNER = 13, RENDER_PLANET_BORDER = 1.5;
    
}