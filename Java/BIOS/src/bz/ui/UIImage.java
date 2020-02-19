package bz.ui;

import static bz.ui.RetroUI.LEVELS;
import javafx.scene.image.Image;
import javafx.scene.image.PixelReader;

public class UIImage {
    
    public static void RenderImage(Image img, int xPos, int yPos) {
        RenderImage(img, xPos, yPos, RenderType.COLOUR);
    }
    
    public static void RenderImage(Image img, int xPos, int yPos, RenderType type) {
        PixelReader pixelReader = img.getPixelReader();
        double w = img.getWidth();
        byte[][] screen = RetroUI.GetScreen();
        for (int y = 0; y < img.getHeight(); y++) {
            for (int x = 0; x < w; x++) {
                double val = 0.0;
                switch (type) {
                    case OPACITY:
                        val = ((double)screen[xPos + x][yPos + y]) / (LEVELS - 1);
                        val = val + pixelReader.getColor(x, y).getOpacity();
                        if (val > 1.0) {
                            val = 1.0;
                        }
                        break;
                    case COLOUR:
                        val = pixelReader.getColor(x, y).getBrightness();
                        break;
                }
                if (val > 0) {
                    byte v = (byte)(val * (LEVELS - 1));
                    if (v >= LEVELS) {
                        v = LEVELS - 1;
                    }
                    screen[xPos + x][yPos + y] = v;
                }
            }
        }
    }

    public static void RenderImageRight(Image img, int xPos, int yPos) {
        RenderImage(img, (int)(xPos - img.getWidth()), yPos);
    }

    public static void RenderImageCentre(Image img, int yPos) {
        RenderImage(img, (RetroUI.WIDTH - (int)img.getWidth()) / 2, yPos);
    }
    
    public static void RenderImageCentreInWidth(Image img, int xPos, int xPos2, int yPos) {
        double w = xPos2 - xPos;
        w = (w - img.getWidth()) / 2;
        RenderImage(img, (int)w + xPos, yPos);
    }

}
