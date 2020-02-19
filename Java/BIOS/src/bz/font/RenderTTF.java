package bz.font;

import java.util.HashMap;
import java.util.Map;
import java.util.logging.Level;
import java.util.logging.Logger;
import javafx.scene.text.Font;

public class RenderTTF {
    protected String fontPath;
    private Map<Integer, javafx.scene.text.Font> fontCache = new HashMap<>(); 
    
    public Font GetFont(double size) {
        int fsize = (int)size;
        if (fontCache.containsKey(fsize)) {
            return fontCache.get(fsize);
        } else {
            String fi = getClass().getResource(fontPath).toExternalForm();
            javafx.scene.text.Font f = javafx.scene.text.Font.loadFont(fi, fsize);
            while (f == null) {
                System.out.println("Can't load font: " + Double.toString(size) + ", retrying.");
                try {
                    Thread.sleep(10);
                } catch (InterruptedException ex) {
                    Logger.getLogger(RenderTTF.class.getName()).log(Level.SEVERE, null, ex);
                }
                f = javafx.scene.text.Font.loadFont(fi, fsize);
            }
            fontCache.put(fsize, f);
            return f;
        }
    }
}
