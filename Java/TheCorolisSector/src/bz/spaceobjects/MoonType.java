package bz.spaceobjects;

import javafx.scene.image.Image;

public class MoonType {
    private final Image image;
    
    public MoonType(Image image) {
        this.image = image;
    }
    
    public Image GetImage() {
        return image;
    }
}
