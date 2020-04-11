package bz.ui;

import bz.BIOS;
import java.util.*;
import javafx.scene.canvas.*;
import javafx.scene.paint.Color;
import javafx.scene.image.*;
import javafx.scene.image.WritableImage;
import bz.font.*;

public class RetroUI {
    public static final Color ExtremelyLightGrey = Color.rgb(24,24,24);
    public static final Color VeryLightGrey = Color.rgb(48,48,48);
    public static final int LEVELS = 8;
    public static final int WIDTH = 400, HEIGHT = 232, PIXEL_SIZE = 2, SPACE_SIZE = 1;
    private static final int COLOUR_VARIANCE = 10;
    private static int width, height;
    private static final byte[][] screen = new byte[WIDTH][HEIGHT];
    private static final byte[][] screenPrevious = new byte[WIDTH][HEIGHT];
    private static Image background, panel;
    private static final Image[] levels = new Image[LEVELS];
    private static final SystemFont font = new SystemFont();
    private static final Thin8x8Font thin = new Thin8x8Font();
    private static final TinyFont tiny = new TinyFont();
    private static int xCursor = 0, yCursor = 0;
    private static List<Character> queue = new ArrayList<>(2048);
    private static boolean resetting = false;
    private static int resetFrame = 0;
    private static RenderTTF bebasNeueFont = new RenderTTFBebasNeue();
    private static RenderTTF sansFont = new RenderTTFRobotoRegular();
    private static RenderTTF sansFontBold = new RenderTTFRobotoRegularBold();
    private static RenderTTF sansFontBlack = new RenderTTFRobotoBlack();
    private static RenderTTF sansFontLight = new RenderTTFRobotoLight();
    private static RenderTTFSquare squareFont = new RenderTTFSquare();
    private static ConsoleFont consoleFont = ConsoleFont.THIN;
    
    public RetroUI() {
        panel = new Image(getClass().getResource("/bz/resources/Panel.png").toExternalForm(), 1366, 768, true, true);
        background = CreateBackgroundImage();
        SetBackgroundImage();
        levels[0] = CreateImage(PIXEL_SIZE, PIXEL_SIZE, Color.rgb(133, 148, 3));
        levels[1] = CreateImage(PIXEL_SIZE, PIXEL_SIZE, Color.rgb(117, 137, 3));
        levels[2] = CreateImage(PIXEL_SIZE, PIXEL_SIZE, Color.rgb(101, 127, 3));
        levels[3] = CreateImage(PIXEL_SIZE, PIXEL_SIZE, Color.rgb(85, 116, 3));
        levels[4] = CreateImage(PIXEL_SIZE, PIXEL_SIZE, Color.rgb(69, 106, 2));
        levels[5] = CreateImage(PIXEL_SIZE, PIXEL_SIZE, Color.rgb(53, 95, 2));
        levels[6] = CreateImage(PIXEL_SIZE, PIXEL_SIZE, Color.rgb(37, 85, 2));
        levels[7] = CreateImage(PIXEL_SIZE, PIXEL_SIZE, Color.rgb(22, 73, 2));
        font.Init();
        tiny.Init();
        thin.Init();
        SetContent(0);
    }
    
    public static byte[][] GetScreen() {
        return screen;
    }
    
    public static RenderTTF GetBebasNeue() {
        return bebasNeueFont;
    }
    
    public static RenderTTF GetSansFont() {
        return sansFont;
    }
    
    public static RenderTTF GetSansFontBold() {
        return sansFontBold;
    }

    public static RenderTTF GetSansFontBlack() {
        return sansFont;
    }

    public static RenderTTF GetSansFontLight() {
        return sansFont;
    }

    public static RenderTTF GetSquareFont() {
        return squareFont;
    }
    
    public static void Reset() {
        resetting = true;
        resetFrame = 0;
        xCursor = 0;
        yCursor = 0;
    }
    
    public static void NewLine() {
        yCursor++;
        xCursor = 0;
        CheckCursor();
    }
    
    public static void WriteString(String s) {
        for (char c : s.toCharArray()) {
            queue.add(c);
        }
    }
    
    public static void WriteCharacter(char c) {
        queue.add(c);
    }
    
    private static void CheckCursor() {
        if (xCursor == (WIDTH / 8)) {
            xCursor = 0;
            yCursor++;
        }
        
        // Scroll?
        if (yCursor == (HEIGHT / 8)) {
            for (int y = 8; y < HEIGHT; y++) {
                for (int x = 0; x < WIDTH; x++) {
                byte i = screen[x][y];
                screenPrevious[x][y - 8] = screen[x][y - 8];
                screen[x][y - 8] = i;
                screen[x][y] = 0;
                }
            }
            yCursor--;
        }
    }
    
    private static Color GetVariedBackgroundColour() {
        int halfV = COLOUR_VARIANCE;
        int r = 151 + (BIOS.GetRandom().nextInt(COLOUR_VARIANCE) - halfV);
        int g = 161 + (BIOS.GetRandom().nextInt(COLOUR_VARIANCE) - halfV);
        return Color.rgb(r, g, 0);
    }
    
    private static Image CreateBackgroundImage() {
        width = BIOS.GetMainController().GetWidthCanvas(1366);
        height = BIOS.GetMainController().GetHeightCanvas(768);
        WritableImage img = new WritableImage(width, height);
        PixelWriter pixelWriter = img.getPixelWriter();
        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                pixelWriter.setColor(x, y, GetVariedBackgroundColour());
            }
        }
        BIOS.GetMainController().SetBackground(img);
        return img;
    } 
    
    private static void SetBackgroundImage() {
        BIOS.GetMainController().SetBackground(panel);
    }
    
    private static Image CreateImage(int width, int height, Color color) {
        WritableImage img = new WritableImage(width, height);
        PixelWriter pixelWriter = img.getPixelWriter();
        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                pixelWriter.setColor(x, y, color);
            }
        }
        return img;
    }
    
    public static final void SetContent(int i) {
        for (int y = 0; y < HEIGHT; y++) {
            for (int x = 0; x < WIDTH; x++) {
                screenPrevious[x][y] = screen[x][y];
                screen[x][y] = (byte)i;
            }
        }
    }

    private static void RandomContent() {
        for (int y = 0; y < HEIGHT; y++) {
            for (int x = 0; x < WIDTH; x++) {
                screenPrevious[x][y] = screen[x][y];
                screen[x][y] = (byte)BIOS.GetRandom().nextInt(LEVELS);
            }
        }
    }
    
    public static void SetPixel(int x, int y, byte v) {
        screen[x][y] = v;
    }
    
    public static void Render(Canvas canvas) {
        GraphicsContext gc = canvas.getGraphicsContext2D();
        gc.setGlobalAlpha(1.0);
        gc.clearRect(0, 0, width, height);
        if (resetting) {
            switch (resetFrame) {
                case 0:
                    RandomContent();
                    resetFrame++;
                    break;
/*                case 4:
                    SetContent(3);
                    resetFrame++;
                    break;
                case 16:
                    SetContent(2);
                    resetFrame++;
                    break;
                case 17:
                    SetContent(1);
                    resetFrame++;
                    break;
                case 18:
                    SetContent(0);
                    resetFrame++;
                    break;
                case 24:
                    resetting = false;
                    BIOS.GetPanel().PostReset();
                    break;*/
                default:
                    resetFrame++;
                    break;
            }
        } else {
            RenderCharacter();
        }
        for (int y = 0; y < HEIGHT; y++) {
            int yPos = y * (PIXEL_SIZE + SPACE_SIZE);
            for (int x = 0; x < WIDTH; x++) {
                int xPos = x * (PIXEL_SIZE + SPACE_SIZE);
                byte i = screen[x][y];
                byte p = screenPrevious[x][y];
                byte c = (byte)(((double)(i * 3) + (double)p) / 4.0);

                // New
                Image img = levels[c];
                double a = (BIOS.GetRandom().nextDouble() / 4) + 0.75;
                gc.setGlobalAlpha(a);
                gc.drawImage(img, xPos, yPos);

                screenPrevious[x][y] = i;
            }
        }
    }
    
    private static void RenderCharacter() {
        while (!queue.isEmpty()) {
            char c = queue.get(0);
            queue.remove(0);
            
            // Special?
            if (c == '¬') {
                c = queue.get(0);
                queue.remove(0);
                switch (c) {
                    case 'n':
                        NewLine();
                        break;
                }
                continue;
            }
            
            switch (consoleFont) {
                case VGA:
                    font.RenderCharacter(c, xCursor++, yCursor);
                    break;
                case THIN:
                    thin.RenderCharacter(c, xCursor++, yCursor);
                    break;
                case TINY:
                    tiny.RenderCharacter(c, xCursor++, yCursor);
                    break;
            }
            CheckCursor();
        }
    } 
    
    public static void SetConsoleFont(ConsoleFont cf) {
        consoleFont = cf;
    }

}
