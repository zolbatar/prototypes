package infection.ui;

import java.util.*;
import javafx.scene.canvas.*;
import javafx.scene.paint.Color;
import javafx.scene.image.*;
import javafx.scene.image.WritableImage;

public class RetroUI {
    private static final int WIDTH = 320, HEIGHT = 256, PIXEL_SIZE = 2, SPACE_SIZE = 1;
    private static final int COLOUR_VARIANCE = 6, LEVELS = 4, PADDING = 16;
    private final byte[][] screen = new byte[WIDTH][HEIGHT];
    private final Random rand = new Random();
    private final Image background;
    private final Image[] levels = new Image[LEVELS];
    
    public RetroUI() {
        background = CreateBackgroundImage();
        levels[0] = CreateImage(PIXEL_SIZE, PIXEL_SIZE, Color.rgb(133, 148, 3));
        levels[1] = CreateImage(PIXEL_SIZE, PIXEL_SIZE, Color.rgb(129, 144, 3));
        levels[2] = CreateImage(PIXEL_SIZE, PIXEL_SIZE, Color.rgb(86, 114, 2));
        levels[3] = CreateImage(PIXEL_SIZE, PIXEL_SIZE, Color.rgb(22, 73, 2));
        RandomContent();
    }
    
    private Color GetVariedBackgroundColour() {
        int halfV = COLOUR_VARIANCE / 2;
        int r = 151 + (rand.nextInt(COLOUR_VARIANCE) - halfV);
        int g = 161 + (rand.nextInt(COLOUR_VARIANCE) - halfV);
        return Color.rgb(r, g, 0);
    }
    
    private int GetWidth() {
        return (int)((WIDTH * (PIXEL_SIZE + SPACE_SIZE)) - SPACE_SIZE + (PADDING * 2));
    }
    
    private int GetHeight() {
        return (int)((HEIGHT * (PIXEL_SIZE + SPACE_SIZE)) - SPACE_SIZE + (PADDING * 2));
    }

    private Image CreateBackgroundImage() {
        int width = GetWidth();
        int height = GetHeight();
        WritableImage img = new WritableImage(width, height);
        PixelWriter pixelWriter = img.getPixelWriter();
        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                pixelWriter.setColor(x, y, GetVariedBackgroundColour());
            }
        }
        return img;
    } 
    
    private Image CreateImage(int width, int height, Color color) {
        WritableImage img = new WritableImage(width, height);
        PixelWriter pixelWriter = img.getPixelWriter();
        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                pixelWriter.setColor(x, y, color);
            }
        }
        return img;
    }
    
    private void RandomContent() {
        for (int y = 0; y < HEIGHT; y++) {
            for (int x = 0; x < WIDTH; x++) {
//                screen[x][y] = (byte)rand.nextInt(LEVELS + 1);
                screen[x][y] = 4;
            }
        }
    }
    
    public void Render(Canvas canvas) {
        GraphicsContext gc = canvas.getGraphicsContext2D();
        gc.setGlobalAlpha(1.0);
        gc.drawImage(background, 0, 0);
        for (int y = 0; y < HEIGHT; y++) {
            int yPos = PADDING + (y * (PIXEL_SIZE + SPACE_SIZE));
            for (int x = 0; x < WIDTH; x++) {
                int xPos = PADDING + (x * (PIXEL_SIZE + SPACE_SIZE));
                int i = screen[x][y];
                if (i > 0) {
                    Image img = levels[i - 1];
                    double a = (rand.nextDouble() / 4) + 0.75;
                    gc.setGlobalAlpha(a);
                    gc.drawImage(img, xPos, yPos);
                }
            }
        }
        // Render pixels
//        gc.setFill(backgroundColour);
//        gc.fillRect(0, 0, WIDTH, HEIGHT);
    }
}
