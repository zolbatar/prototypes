package bz.ui;

import javafx.scene.SnapshotParameters;
import javafx.scene.image.Image;
import javafx.scene.layout.Pane;
import javafx.scene.paint.Color;
import javafx.scene.shape.Rectangle;

public class UIShapes {

    public static Image CreateBox(double width, double height, double stroke, double cornerRadius, Color fillColor, Color strokeColor) {
        SnapshotParameters sn = new SnapshotParameters();
        sn.setFill(Color.BLACK);
        Pane p = new Pane();
        Rectangle r = new Rectangle(0, 0, width, height);
        r.setArcHeight(cornerRadius);
        r.setArcWidth(cornerRadius);
        r.setFill(fillColor);
        r.setStroke(strokeColor);
        r.setStrokeWidth(stroke);
        p.getChildren().add(r);
        return p.snapshot(sn, null);
    }
    
    public static Image CreateProgressBar(double width, double height, double stroke, double cornerRadius, double proportion, Color fillColor, Color strokeColor, Color foreColor) {
        SnapshotParameters sn = new SnapshotParameters();
        sn.setFill(Color.BLACK);
        Pane p = new Pane();
        Rectangle r = new Rectangle(0, 0, width, height);
        r.setArcHeight(cornerRadius);
        r.setArcWidth(cornerRadius);
        r.setFill(fillColor);
        r.setStroke(strokeColor);
        r.setStrokeWidth(stroke);
        p.getChildren().add(r);
        r = new Rectangle(0, 0, (width * proportion) - (stroke * 4), height - (stroke * 4));
        r.setX(stroke * 2);
        r.setY(stroke * 2);
        r.setFill(foreColor);
        r.setStrokeWidth(0);
        p.getChildren().add(r);
        return p.snapshot(sn, null);
    }
}
