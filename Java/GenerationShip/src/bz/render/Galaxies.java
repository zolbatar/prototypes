package bz.render;

import bz.GenerationShip;
import bz.Parameters;
import bz.helpers.Maths;
import java.util.ArrayList;
import java.util.List;
import java.util.Random;
import javafx.scene.canvas.GraphicsContext;

public class Galaxies {
    private final List<Galaxy> galaxies;
    private int numberOfGalaxies;
    
    public Galaxies(double w, double h) {
        numberOfGalaxies = (int)(w * h * Parameters.RENDER_GALAXYDENSITY);
        if (numberOfGalaxies > Parameters.ASSET_GALAXY_COUNT) {
            numberOfGalaxies = Parameters.ASSET_GALAXY_COUNT;
        }
        galaxies = new ArrayList(numberOfGalaxies); 
        generateInitial(w, h);
    }
    
    public final void generateInitial(double w, double h) {
        List<Integer> n = new ArrayList(Parameters.ASSET_GALAXY_COUNT);
        for (int i = 0; i < Parameters.ASSET_GALAXY_COUNT; i++) {
            n.add(i);
        }

        Random r = GenerationShip.getRandom();
        for (int i = 0; i < numberOfGalaxies; i++) {
            Integer type = n.get(r.nextInt(n.size()));
            n.remove(type);
            double size = GenerationShip.getAssets().getGalaxySize(type);
            
            boolean want;
            double x, y;
            do {
                x = (r.nextDouble() * (w - 300)) + 150;
                y = (r.nextDouble() * (h - 300)) + 150;

                // Too close?
                want = true;
                for (Galaxy g : galaxies) {
                    
                    if (Maths.DistanceBetweenPoints(x, y, g.getX(), g.getY()) < (g.getSize() + size) * 0.75) {
                        want = false;
                        break;
                    }
                }
            } while (!want);
            
            // Add  
            galaxies.add(new Galaxy(x, y, r, type));
        }
    }

    public final void render(GraphicsContext gc) {
        for (Galaxy g : galaxies) {
            g.render(gc);
        }
    }
}
