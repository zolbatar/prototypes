package bz.render;

import bz.GenerationShip;
import bz.Parameters;
import bz.helpers.Maths;
import java.util.ArrayList;
import java.util.List;
import java.util.Random;
import javafx.scene.canvas.GraphicsContext;

public class Nebulae {
    private final List<Nebula> nebulae;
    private int numberOfNebulae;
    
    public Nebulae(double w, double h) {
        numberOfNebulae = (int)(w * h * Parameters.RENDER_NEBULADENSITY);
        if (numberOfNebulae > Parameters.ASSET_NEBULA_COUNT) {
            numberOfNebulae = Parameters.ASSET_NEBULA_COUNT;
        }
        nebulae = new ArrayList(numberOfNebulae); 
        generateInitial(w, h);
    }

    public final void generateInitial(double w, double h) {
        Random r = GenerationShip.getRandom();
        for (int i = 0; i < numberOfNebulae; i++) {
            int type = r.nextInt(Parameters.ASSET_NEBULA_COUNT);
            double size = 1024 + (r.nextDouble() * 1024);
            double x = (r.nextDouble() * (w + 1000)) - 500;
            double y = (r.nextDouble() * (h + 1000)) - 500;
            nebulae.add(new Nebula(x, y, r, type, size));
        }
    }

    public final void render(GraphicsContext gc) {
        for (Nebula g : nebulae) {
            g.render(gc);
        }
    }
}
