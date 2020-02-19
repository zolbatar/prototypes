package bz.render;

import bz.GenerationShip;
import bz.helpers.Graphics;
import java.util.Random;
import javafx.scene.canvas.GraphicsContext;
import javafx.scene.effect.BlendMode;
import javafx.scene.image.Image;

public class Nebula {
    private final double rot, y, x, xCentre, yCentre, depth, size;
    private final Image img;
    
    public Nebula(double x, double y, Random r, int i, double size) {
        this.rot = r.nextDouble() * 360;
        this.depth = (r.nextDouble() * 0.25) + 0.75;
        this.x = x;
        this.y = y;
        this.size = size;
        this.xCentre = x + (size / 2);
        this.yCentre = y + (size / 2);
        this.img = GenerationShip.getAssets().getNebulaImage(i);
    }

    public void render(GraphicsContext gc) {
        gc.save();
        gc.setGlobalBlendMode(BlendMode.ADD);
        gc.setGlobalAlpha(depth * 0.25);
        Graphics.setRotation(gc, rot, xCentre, yCentre);
        gc.drawImage(img, x, y, size, size);
        gc.restore();
    }

    public void animate(double delta) {
    }
 
    public double getX() {
        return x;
    }
    
    public double getY() {
        return y;
    }
    
    public double getSize() {
        return img.getWidth();
    }
}
