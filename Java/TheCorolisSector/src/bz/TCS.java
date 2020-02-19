package bz;

import java.util.Random;
import java.net.URL;
import java.io.IOException;
import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.layout.AnchorPane;
import javafx.scene.Scene;
import javafx.scene.text.Font;
import javafx.stage.Stage;
import javafx.beans.value.*;
import javafx.animation.AnimationTimer;
import bz.library.Profiler;
import bz.panels.*;
import bz.panels.menu.*;
import bz.panels.subpanels.*;
import bz.assets.Assets;
import bz.game.Difficulty;
import bz.game.Game;
import bz.game.GameSize;
import bz.game.render.RenderMap;

public class TCS extends Application {
    private final static Random random = new Random();
    private static Parent root;
    private static Stage stage;
    private static AnchorPane paneMenu, paneGame;
    private static AnchorPane paneMap, paneInfo, paneSelected;
    private static FXMLSceneController controllerScene;
    private static FXMLGameController controllerGame;
    private static FXMLMenuController controllerMenu;
    private static FXMLMapController controllerMap;
    private static FXMLInfoController controllerInfo;
    private static FXMLSelectedController controllerSelected;
    private static GameMode mode = GameMode.STARTING;
    private static RenderMap render;
    private static Game game;
    private static double stageWidth, stageHeight;
    private static long time = -1;
    private static double timeCum = 0;
    private static Assets assets;
   
    @Override
    public void start(Stage stage) throws Exception {
        TCS.stage = stage;
        Font.loadFont(getClass().getResource("assets/fonts/Square.ttf").toExternalForm(), 10);
        LoadPanels();
        setUserAgentStylesheet(STYLESHEET_MODENA);
        stage.setTitle("The Corolis Sector");
//        stage.setFullScreen(true);
        stage.setMaximized(true);
        Scene scene = new Scene(root);
        stage.setScene(scene);
        stage.show();
        ResizeBackground();
        
        // Listeners on resize
        stage.widthProperty().addListener(new ChangeListener<Number>() {
            @Override public void changed(ObservableValue<? extends Number> observableValue, Number oldSceneWidth, Number newSceneWidth) {
                ResizeBackground();
            }
        });
        stage.heightProperty().addListener(new ChangeListener<Number>() {
            @Override public void changed(ObservableValue<? extends Number> observableValue, Number oldSceneHeight, Number newSceneHeight) {
                ResizeBackground();
            }
        });

        // Animation timer
        AnimationTimer timer = new AnimationTimer() {
            @Override
            public void handle(long now) {
                if (mode == GameMode.STARTING) {
                    SceneMenu();
                }
                RenderLoop(now);
            }
        };
        timer.start(); 
        
        // Show menu
        render = new RenderMap(controllerMap);
        
//        assets = new Assets();
//        game = new Game(Difficulty.MEDIUM, GameSize.NORMAL);
//        TCS.SceneGame(game);
    }

    @Override
    public void stop() throws Exception {
        Profiler.WriteFile();
    }
    
    public static void Close() {
        stage.close();
    }
    
    public static RenderMap GetRenderMap() {
        return render;
    }
    
    public static Random GetRandom() {
        return random;
    }
    
    public static Assets GetAssets() {
        return assets;
    }
    
    public static Game GetGame() {
        return game;
    }
    
    public static void SceneMenu() {
        controllerScene.ClearAndSetScene(paneMenu);
        if (assets == null) {
            Thread t = new Thread(() -> {
                mode = GameMode.MAINMENU;
                assets = new Assets();
            });
            t.start();
        }
    }

    public static void ShowMenu() {
        TCS.controllerMenu.ShowMenu();
    }
    
    public static void SceneGame(Game newGame) {
        BuildGamePanes();
        controllerScene.ClearAndSetScene(paneGame);
        mode = GameMode.GAME;
        game = newGame;
    }

    public static void BuildGamePanes() {
        controllerGame.GetBorderPane().setLeft(paneInfo);
        controllerGame.GetBorderPane().setCenter(paneMap);
        controllerGame.GetBorderPane().setRight(paneSelected);
    }

    private void ResizeBackground() {
        System.out.println("Resizing background.");
        stageWidth = root.getBoundsInLocal().getWidth();
        stageHeight = root.getBoundsInLocal().getHeight();
        URL url = this.getClass().getResource("/bz/assets/images/Background.png");
        root.setStyle("-fx-background-image: url('" + url + "'); -fx-background-size: " + stageWidth + "px " + stageHeight + "px; -fx-background-position: center center;");
    }
    
    private static void RenderLoop(long now) {
        Profiler.Enter("TheCorolisSector::RenderLoop");
        double delta = 0;
        if (time != -1) {
            delta = (now - time) / 1000;
        }
        time = now;
        double timeSeconds = delta / 1000000.0;
        timeCum += timeSeconds;
        switch (mode) {
            case LOADING:
                break;
            case MAINMENU:
                TCS.controllerMenu.Update();
                break;
            case GAME:
                render.Render();
                break;
        }
        Profiler.Leave("TheCorolisSector::RenderLoop");
    }

    private void LoadPanels() throws IOException {
        FXMLLoader fxmlLoader = new FXMLLoader(getClass().getResource("panels/FXMLScene.fxml"));
        root = fxmlLoader.load();
        controllerScene = (FXMLSceneController)fxmlLoader.getController();
        
        // Scene
        fxmlLoader = new FXMLLoader(getClass().getResource("panels/FXMLGame.fxml"));
        paneGame = LoadPanel(fxmlLoader);
        controllerGame = (FXMLGameController)fxmlLoader.getController();

        // Menu
        fxmlLoader = new FXMLLoader(getClass().getResource("panels/menu/FXMLMenu.fxml"));
        paneMenu = LoadPanel(fxmlLoader);
        controllerMenu = (FXMLMenuController)fxmlLoader.getController();

        // Subpanels
        fxmlLoader = new FXMLLoader(getClass().getResource("panels/subpanels/FXMLMap.fxml"));
        paneMap = LoadPanel(fxmlLoader);
        controllerMap  = (FXMLMapController)fxmlLoader.getController();
        fxmlLoader = new FXMLLoader(getClass().getResource("panels/subpanels/FXMLInfo.fxml"));
        paneInfo = LoadPanel(fxmlLoader);
        controllerInfo  = (FXMLInfoController)fxmlLoader.getController();
        fxmlLoader = new FXMLLoader(getClass().getResource("panels/subpanels/FXMLSelected.fxml"));
        paneSelected = LoadPanel(fxmlLoader);
        controllerSelected  = (FXMLSelectedController)fxmlLoader.getController();
    }
    
    private AnchorPane LoadPanel(FXMLLoader fxmlLoader) throws IOException {
        AnchorPane pane = fxmlLoader.load();
        AnchorPane.setTopAnchor(pane, 0.0);
        AnchorPane.setBottomAnchor(pane, 0.0);
        AnchorPane.setLeftAnchor(pane, 0.0);
        AnchorPane.setRightAnchor(pane, 0.0);
        return pane;
    }

    public static void main(String[] args) {
        launch(args);
    }
    
    public static FXMLMenuController GetControllerMenu() {
        return controllerMenu;
    }
    
    // Sound
    public static void BeepMenu() {
        if (assets != null) {    
            assets.PlayHi();
        }
    }
    
    public static double GetTime() {
        return timeCum;
    }
    
}
