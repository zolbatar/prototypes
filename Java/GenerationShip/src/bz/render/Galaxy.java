package bz.render;

import java.util.Random;
import javafx.scene.canvas.GraphicsContext;
import javafx.scene.image.Image;
import bz.GenerationShip;
import bz.helpers.Graphics;
import javafx.scene.effect.BlendMode;

public class Galaxy {
    private final double rot, x, y, xCentre, yCentre, depth;
    private final Image img;
    
    public Galaxy(double x, double y, Random r, int i) {
        this.rot = r.nextDouble() * 360;
        this.depth = (r.nextDouble() * 0.25) + 0.75;
        this.xCentre = x;
        this.yCentre = y;
        double size = GenerationShip.getAssets().getGalaxySize(i);
        this.x = xCentre - (size / 2);
        this.y = yCentre - (size / 2);
        this.img = GenerationShip.getAssets().getGalaxyImage(i);
    }

    public void render(GraphicsContext gc) {
        gc.save();
        gc.setGlobalBlendMode(BlendMode.ADD);
        gc.setGlobalAlpha(depth);
        Graphics.setRotation(gc, rot, xCentre, yCentre);
        gc.drawImage(img, x, y);
        gc.restore();
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
