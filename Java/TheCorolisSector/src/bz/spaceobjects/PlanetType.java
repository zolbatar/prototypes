package bz.spaceobjects;

import javafx.scene.image.Image;
import javafx.scene.paint.Color;

public class PlanetType {
    private final String type;
    private final Image image;
    private final Color average;
    
    public PlanetType(String type, Image image, Color average) {
        this.type = type;
        this.image = image;
        this.average = average;
    }
    
    public Color GetAverage() {
        return average;
    }
    
    public String GetType() {
        return type;
    }
    
    public Image GetImage() {
        return image;
    }
}
