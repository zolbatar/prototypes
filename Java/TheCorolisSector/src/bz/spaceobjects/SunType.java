package bz.spaceobjects;

import javafx.scene.image.Image;
import javafx.scene.paint.Color;

public class SunType {
    private final Image image;
    private final Color average;
    
    public SunType(Image image, Color average) {
        this.image = image;
        this.average = average;
    }
    
    public Color GetAverage() {
        return average;
    }
    
    public Image GetImage() {
        return image;
    }
}
