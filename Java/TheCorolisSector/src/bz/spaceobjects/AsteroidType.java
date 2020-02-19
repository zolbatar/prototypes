package bz.spaceobjects;

import javafx.scene.image.Image;

public class AsteroidType {
    private final Image image;
    
    public AsteroidType(Image image) {
        this.image = image;
    }
    
    public Image GetRender() {
        return image;
    }
}
