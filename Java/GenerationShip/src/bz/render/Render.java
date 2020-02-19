package bz.render;

import javafx.scene.canvas.Canvas;
import javafx.scene.canvas.GraphicsContext;
import javafx.scene.paint.Color;

public class Render {
    private final Canvas canvas, background;
    private final Stars stars;
    private final Galaxies galaxies;
    private final Nebulae nebulae;
    
    public Render(Canvas canvas, Canvas background) {
        this.canvas = canvas;
        this.background = background;
        stars = new Stars(canvas.getWidth(), canvas.getHeight());
        galaxies = new Galaxies(canvas.getWidth(), canvas.getHeight());
        nebulae = new Nebulae(canvas.getWidth(), canvas.getHeight());
    }
    
    public final void RenderBackground() {
        double w = background.getWidth();
        double h = background.getHeight();

        // Render
        GraphicsContext gc = background.getGraphicsContext2D();
        gc.setFill(Color.BLACK);
        gc.fillRect(0, 0, w, h);
        galaxies.render(gc);
        nebulae.render(gc);
    }
    
    public final void Render(double delta) {
        double w = canvas.getWidth();
        double h = canvas.getHeight();
        
        // Context
        GraphicsContext gc = canvas.getGraphicsContext2D();
        gc.clearRect(0, 0, w, h);
        
        // Render galaxies, nebulae and stars
        stars.renderAndAnimate(gc, delta, w, h);
    }
}
