package infection;

import java.net.URL;
import java.util.ResourceBundle;
import javafx.fxml.FXML;
import javafx.fxml.Initializable;
import javafx.scene.canvas.Canvas;

public class FXMLMainController implements Initializable {
    @FXML private Canvas canvas;
       
    @Override
    public void initialize(URL url, ResourceBundle rb) {
    }    
    
    public Canvas GetCanvas() {
        return canvas;
    }
}
