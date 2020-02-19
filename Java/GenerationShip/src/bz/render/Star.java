package bz.render;

import java.util.Random;
import javafx.scene.SnapshotParameters;
import javafx.scene.canvas.GraphicsContext;
import javafx.scene.paint.Color;
import javafx.scene.image.Image;
import javafx.scene.canvas.Canvas;
import bz.Parameters;
import javafx.scene.effect.BlendMode;

public class Star {
    private final int COLOUR_BASE = 128;
    private final int COLOUR_ADJUST = 127;
    private double x, y;
    private final double size, halfSize, depth;
    private final Image img;
    
    public Star(double x, double y, Random r) {
        this.x = x;
        this.y = y;
        this.size = r.nextDouble() * 1.25 + 0.75;
        this.depth = r.nextDouble();
        this.halfSize = size / 2;
        Color color = Color.rgb(r.nextInt(COLOUR_ADJUST) + COLOUR_BASE, r.nextInt(COLOUR_ADJUST) + COLOUR_BASE, r.nextInt(COLOUR_ADJUST) + COLOUR_BASE);
        
        // Cache it for speed
        SnapshotParameters sn = new SnapshotParameters();
        sn.setFill(Color.TRANSPARENT);
        Canvas c = new Canvas();
        c.setWidth(size);
        c.setHeight(size);
        GraphicsContext gc = c.getGraphicsContext2D();
        gc.setFill(color);
        gc.fillOval(0.5, 0.5, size - 0.5, size - 0.5);
        img = c.snapshot(sn, null);
    }
    
    public void setNewX(double x) {
        this.x = x;
        this.y = -10;
    }
    
    public void render(GraphicsContext gc) {
        gc.save();
        gc.setGlobalBlendMode(BlendMode.SRC_OVER);
        gc.drawImage(img, x - halfSize, y - halfSize);
        gc.restore();
    }
    
    public boolean animate(double delta, double h) {
        y += (delta * Parameters.RENDER_STARMOVESPEED * depth);
        return y > h + 10;
    }
}
