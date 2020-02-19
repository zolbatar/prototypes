package bz.helpers;

import javafx.scene.canvas.GraphicsContext;
import javafx.scene.transform.Rotate;

public class Graphics {
    private static final Rotate r = new Rotate();

    public static void setRotation(GraphicsContext gc, double angle, double px, double py) {
        r.setAngle(angle);
        r.setPivotX(px);
        r.setPivotY(py);
        gc.setTransform(r.getMxx(), r.getMyx(), r.getMxy(), r.getMyy(), r.getTx(), r.getTy());
    }
}
