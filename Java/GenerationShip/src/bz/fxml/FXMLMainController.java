package bz.fxml;

import java.net.URL;
import java.util.ResourceBundle;
import javafx.fxml.FXML;
import javafx.fxml.Initializable;
import javafx.scene.canvas.Canvas;
import javafx.scene.layout.AnchorPane;

public class FXMLMainController implements Initializable {
    @FXML private AnchorPane pane;
    @FXML private Canvas canvas;
    @FXML private Canvas canvasBackground;

    @Override
    public void initialize(URL url, ResourceBundle rb) {
    }    
    
    public void CheckCanvas() {
        canvas.setWidth(pane.getWidth());
        canvas.setHeight(pane.getHeight());
        canvasBackground.setWidth(pane.getWidth());
        canvasBackground.setHeight(pane.getHeight());
    }
    
    public Canvas GetCanvas() {
        return canvas;
    }
    
    public Canvas GetCanvasBackground() {
        return canvasBackground;
    }

}
