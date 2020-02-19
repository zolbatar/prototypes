package bz;

import java.util.*;
import java.io.IOException;
import javafx.animation.AnimationTimer;
import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.input.KeyCombination;
import javafx.scene.text.Font;
import javafx.stage.Stage;
import bz.fxml.*;
import bz.render.Render;

public class GenerationShip extends Application {
    private static Assets assets = null;
    private static Parent root;
    private static FXMLMainController controller;
    private static Render render = null;
    private static final Random rand = new Random();
    
    @Override
    public void start(Stage stage) throws Exception {

        // Fonts
        Font.loadFont(getClass().getResource("resources/fonts/" + bz.Parameters.UI_FONT).toExternalForm(), 10);

        // Set stage
        setUserAgentStylesheet(STYLESHEET_MODENA);
        stage.setTitle("Generation Ship");
        stage.setWidth(1366);
        stage.setHeight(768);
//        stage.setMaximized(true);
//        stage.setFullScreen(true);
        stage.setFullScreenExitKeyCombination(KeyCombination.NO_MATCH);
        
        // Forms
        loadFXML();
        Scene scene = new Scene(root);
        stage.setScene(scene);
        stage.show();
        
        // Animation timer
        AnimationTimer timer = new AnimationTimer() {
            private long previous = 0;
            
            @Override
            public void handle(long now) {
                
                // Time delta
                double delta = 0;
                if (previous == 0) {
                    previous = now;
                } else {
                    delta = ((double)now - (double)previous) / 1000000000.0d;
                    previous = now;
                }
                
                // Check canvas
                controller.CheckCanvas();

                // Render
                if (assets != null) {
                    if (render == null) {
                        render = new Render(controller.GetCanvas(), controller.GetCanvasBackground());
                        render.RenderBackground();
                    }
                    render.Render(delta);
                }
            }
        };
        timer.start(); 

        // Load assets thread
        Thread t = new Thread(() -> {
            assets = new Assets();
        });
        t.start();
    }
    
    private void loadFXML() throws IOException {
        FXMLLoader fl = new FXMLLoader(getClass().getResource("fxml/FXMLMain.fxml"));
        root = fl.load();
        controller = (FXMLMainController)fl.getController();
    }
    
    public static Random getRandom() {
        return rand;
    }
    
    public static Assets getAssets() {
        return assets;
    }

    public static void main(String[] args) {
        launch(args);
    }
    
}
