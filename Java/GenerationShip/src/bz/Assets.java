package bz;

import java.util.Random;
import javafx.scene.image.Image;

public class Assets {
    private final Image[] galaxies = new Image[Parameters.ASSET_GALAXY_COUNT];
    private final Image[] nebula = new Image[Parameters.ASSET_NEBULA_COUNT];
    private final double[] galaxySizes = new double[Parameters.ASSET_GALAXY_COUNT];
    
    public Assets() {
        Random r = GenerationShip.getRandom();
        
        // Galaxies
        for (int i = 0; i < Parameters.ASSET_GALAXY_COUNT; i++) {
            String p = "/bz/resources/images/galaxy/" + (i + 1) + ".png";
            galaxySizes[i] = 16 + (r.nextDouble() * (200));
            galaxies[i] = new Image(getClass().getResource(p).toExternalForm(), galaxySizes[i], galaxySizes[i], true, true);
        }
        
        // Nebulae
        for (int i = 0; i < Parameters.ASSET_NEBULA_COUNT; i++) {
            String p = "/bz/resources/images/nebula/" + (i + 1) + ".png";
            nebula[i] = new Image(getClass().getResource(p).toExternalForm(), 1024, 1024, true, true);
        }
    }
    
    public Image getGalaxyImage(int i) {
        return galaxies[i];
    }
    
    public double getGalaxySize(int i) {
        return galaxySizes[i];
    }
    
    public Image getNebulaImage(int i) {
        return nebula[i];
    }
}
