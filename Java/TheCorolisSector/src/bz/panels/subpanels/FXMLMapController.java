package bz.panels.subpanels;

import bz.Parameters;
import java.util.*;
import java.net.URL;
import java.util.ResourceBundle;
import javafx.fxml.FXML;
import javafx.fxml.Initializable;
import javafx.scene.layout.AnchorPane;
import javafx.scene.canvas.Canvas;
import javafx.scene.input.MouseEvent;
import bz.TCS;
import bz.game.universe.SolarSystem;
import bz.library.Helpers;
import bz.library.Point;

public class FXMLMapController implements Initializable {
    private Point currentMouse = null;
    @FXML
    private AnchorPane pane;
    @FXML
    private Canvas canvas;
    
    @Override
    public void initialize(URL url, ResourceBundle rb) {
    }    
    
    public boolean CheckCanvas() {
        if (pane.getWidth() == 0) {
            return false;
        }
        canvas.setWidth(pane.getWidth());
        canvas.setHeight(pane.getHeight());
        return true;
    }
    
    public Canvas GetCanvas() {
        return canvas;
    }
    
    public double GetWidth() {
        return pane.getWidth();
    }

    public double GetHeight() {
        return pane.getHeight();
    }
    
    public Point GetMousePosition() {
        return currentMouse;
    }
    
    @FXML
    private void onMouseEntered(MouseEvent event) {
        currentMouse = new Point(event.getX(), event.getY());
    }
    
    @FXML
    private void onMouseExited(MouseEvent event) {
        currentMouse = null;
    }

    @FXML
    private void onMouseMoved(MouseEvent event) {
        currentMouse = new Point(event.getX(), event.getY());
    }

}
