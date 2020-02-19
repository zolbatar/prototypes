package infection;

import javafx.animation.AnimationTimer;
import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.stage.Stage;
import javafx.scene.layout.AnchorPane;
import infection.ui.RetroUI;
import javafx.scene.Cursor;

public class Infection extends Application {
    private FXMLMainController controller;
    private RetroUI ui;
    
    @Override
    public void start(Stage stage) throws Exception {
        FXMLLoader loader = new FXMLLoader(getClass().getResource("FXMLMain.fxml"));
        AnchorPane root = loader.load();
        controller = (FXMLMainController)loader.getController();
        Scene scene = new Scene(root);
        stage.setTitle("Infection!");
        stage.setScene(scene);
        scene.setCursor(Cursor.NONE);
        stage.show();
        
        // UI
        ui = new RetroUI();
        
        // Update timer
        new AnimationTimer() {
            @Override
            public void handle(long now) {
                ui.Render(controller.GetCanvas());
            }
        }.start();    
    }

    public static void main(String[] args) {
        launch(args);
    }
    
}
