package bz.library.gfx;

public class Colour {
    private final float r, g, b;
    
    public Colour(float r, float g, float b) {
        this.r = r;
        this.g = g;
        this.b = b;
    }
    
    public float GetRed() {
        return r;
    }
    
    public float GetGreen() {
        return g;
    }

    public float GetBlue() {
        return b;
    }
}
