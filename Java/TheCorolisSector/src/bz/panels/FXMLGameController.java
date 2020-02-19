package bz.panels;

import java.net.URL;
import java.util.ResourceBundle;
import javafx.fxml.FXML;
import javafx.fxml.Initializable;
import javafx.scene.layout.AnchorPane;
import javafx.scene.layout.BorderPane;

public class FXMLGameController implements Initializable {
    @FXML
    private BorderPane content;

    @Override
    public void initialize(URL url, ResourceBundle rb) {
    }    
    
    public BorderPane GetBorderPane() {
        return content;
    }
}
