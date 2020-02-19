package bz;

import java.net.URL;
import java.util.ResourceBundle;
import javafx.event.EventHandler;
import javafx.fxml.FXML;
import javafx.fxml.Initializable;
import javafx.scene.canvas.Canvas;
import javafx.scene.layout.AnchorPane;
import javafx.scene.image.ImageView;
import javafx.scene.image.Image;
import javafx.scene.input.KeyEvent;
import javafx.scene.input.MouseEvent;
import javafx.stage.Stage;

public class FXMLMainController implements Initializable {
    private static EventHandler<KeyEvent> keyEventHandler;
    @FXML
    private Canvas canvas;
    @FXML
    private AnchorPane pane;
    @FXML
    private ImageView background;
       
    @Override
    public void initialize(URL url, ResourceBundle rb) {
        CreateKeyHandler();
    }    
    
    public Canvas GetCanvas() {
        return canvas;
    }
    
    public void SetBackground(Image img) {
        background.setImage(img);
    }
    
    public int GetWidth() {
        background.setFitWidth(pane.getWidth());
        return (int)pane.getWidth();
    }
    
    public int GetHeight() {
        background.setFitHeight(pane.getHeight());
        return (int)pane.getHeight();
    }
    
    public int GetWidthCanvas(double w) {
       if (w == 0) {
           background.setFitWidth(canvas.getWidth() + 4);   
       } else {
           background.setFitWidth(w);   
       }
       return (int)canvas.getWidth();
    }
    
    public int GetHeightCanvas(double h) {
       if (h == 0) {
            background.setFitHeight(canvas.getHeight() + 4);
       } else {
           background.setFitHeight(h);   
       }
        return (int)canvas.getHeight();
    }

    private void CreateKeyHandler() {
        keyEventHandler = (final KeyEvent e) -> {
            BIOS.GetPanel().KeyPressed(e.getCode());
            e.consume();
        };
    }

    public void InstallKeyhandler(Stage stage) {
        stage.addEventFilter(KeyEvent.KEY_PRESSED, keyEventHandler);
    }

    public void RemoveKeyhandler(Stage stage) {
        stage.removeEventFilter(KeyEvent.KEY_PRESSED, keyEventHandler);
    }

    @FXML
    public void onMouseClicked(MouseEvent event) {
        BIOS.GetPanel().MouseClicked((int)event.getX() / 3, (int)event.getY() / 3);
    }
}
