package bz.ui;

import bz.font.RenderTTF;
import javafx.scene.SnapshotParameters;
import javafx.scene.image.Image;
import javafx.scene.paint.Color;
import javafx.scene.text.FontSmoothingType;
import javafx.scene.text.Text;

public class UIString {
    
    public static Image CreateImageString(String s, RenderTTF font, double size, double opacity) {
       return CreateImageString(s, font, size, opacity, Color.WHITE, Color.BLACK);
    }

    public static Image CreateImageString(String s, RenderTTF font, double size, double opacity, Color text, Color fill) {
        SnapshotParameters sn = new SnapshotParameters();
        sn.setFill(fill);
        Text t = new Text();
        t.setFontSmoothingType(FontSmoothingType.GRAY);
        t.setFont(font.GetFont(size));
        t.setText(s);
        t.setFill(text);
        t.setOpacity(opacity);
        Image img = t.snapshot(sn, null);
        return img;
    }
    
}
