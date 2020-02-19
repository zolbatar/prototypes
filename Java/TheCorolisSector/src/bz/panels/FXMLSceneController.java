package bz.panels;

import java.net.URL;
import java.util.ResourceBundle;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.fxml.Initializable;
import javafx.scene.layout.AnchorPane;

public class FXMLSceneController implements Initializable {
    @FXML
    private AnchorPane content;
    
    @Override
    public void initialize(URL url, ResourceBundle rb) {
    }    
    
    public void ClearAndSetScene(AnchorPane scene) {
        content.getChildren().clear();
        content.getChildren().add(scene);
    }
    
}
