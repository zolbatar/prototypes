package bz.render;

import java.util.*;
import javafx.scene.canvas.GraphicsContext;
import bz.GenerationShip;
import bz.Parameters;

public class Stars {
    private final List<Star> stars;
    private final int numberOfStars;
    
    public Stars(double w, double h) {
        numberOfStars = (int)(w * h * Parameters.RENDER_STARDENSITY);
        stars = new ArrayList(numberOfStars); 
        generateInitial(w, h);
    }
    
    public final void generateInitial(double w, double h) {
        Random r = GenerationShip.getRandom();
        for (int i = 0; i < numberOfStars; i++) {
            double x = r.nextDouble() * w;
            double y = r.nextDouble() * h;
            
            // Add  
            stars.add(new Star(x, y, r));
        }
    }
    
    public final void renderAndAnimate(GraphicsContext gc, double delta, double w, double h) {
        for (Star s : stars) {
            s.render(gc);
            if (s.animate(delta, h)) {
                double x = GenerationShip.getRandom().nextDouble() * w;
                s.setNewX(x);
            }
        }
    }
    
}
