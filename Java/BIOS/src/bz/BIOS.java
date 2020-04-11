package bz;

import java.util.concurrent.atomic.AtomicBoolean;
import javafx.animation.AnimationTimer;
import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.stage.Stage;
import javafx.scene.layout.AnchorPane;
import javafx.scene.Cursor;
import bz.ui.RetroUI;
import bz.console.Console;
import bz.library.Profiler;
import bz.panels.*;
import java.util.Random;
import java.util.logging.Level;
import java.util.logging.Logger;

public class BIOS extends Application {
    private static FXMLMainController controller;
    private static RetroUI ui;
    private static Console console;
    private static PanelType panelType = PanelType.PANEL_AC;
    private static Panel panel;
    private static PanelAC panelAC;
    private static PanelACCrash panelACCrash;
    private static boolean pauseRendering = false;
    public AtomicBoolean stopThreads = new AtomicBoolean(false);
    private final GameUpdateThread updateThread;
    private Thread t1;
    private static long time = -1;
    private static double timeCum = 0;
    private static final Random rand = new Random();

    public BIOS() {
        updateThread = new GameUpdateThread();
    }
    
    @Override
    public void stop() throws Exception {
        if (t1 != null) {
            Stop();
        }
        Profiler.WriteFile();
    }

    @Override
    public void start(Stage stage) throws Exception {
        FXMLLoader loader = new FXMLLoader(getClass().getResource("FXMLMain.fxml"));
        AnchorPane root = loader.load();
        controller = (FXMLMainController)loader.getController();
        Scene scene = new Scene(root);
        stage.setTitle("BIOS");
//        stage.setMaximized(true);
        stage.setWidth(1366);
        stage.setHeight(768);
        stage.setScene(scene);
//        stage.setFullScreen(true);
//        scene.setCursor(Cursor.NONE);
        stage.show();
        controller.InstallKeyhandler(stage);
        
        // UI
        ui = new RetroUI();
        console = new Console(ui);    
        StartThreads();
        
        // Setup panels
        panelAC = new PanelAC();
        panelACCrash = new PanelACCrash();
        
        // Start with AC
        panel = panelAC;
//        panel = panelACCrash;
        panel.Init();
        
        // Update timer
        new AnimationTimer() {
            @Override
            public void handle(long now) {
                double delta = 0;
                if (time != -1) {
                    delta = (now - time) / 1000;
                }
                time = now;
                double timeSeconds = delta / 1000000.0;
                timeCum += timeSeconds;
                if (panel != null) {
                    panel.Render(delta / 1000000, timeCum);
                }
                if (!pauseRendering) {
                    ui.Render(controller.GetCanvas());
                }
            }
        }.start();    
    }
    
    public static void SetPanelACCrash() {
        panel = panelACCrash;
        panel.Init();
    }
    
    public static Random GetRandom() {
        return rand;
    }
    
    public static double GetTime() {
        return timeCum;
    }
    
    public static void PauseRendering() {
        pauseRendering = true;
    }
    
    public static Panel GetPanel() {
        return panel;
    }
    
    public static Console GetConsole() {
        return console;
    }
    
    public static FXMLMainController GetMainController() {
        return controller;
    }

    public static void main(String[] args) {
        launch(args);
    }
    
    class GameUpdateThread implements Runnable {
        protected long lastTime = -1;
        
        @Override
        public final void run() {
            lastTime = System.nanoTime();

            while (!stopThreads.get()) {
                long x = System.nanoTime();
                double delta = x - lastTime;
                lastTime = x;
                UpdateThread(delta / 1000000000.0);
                
                try {
                    // Wait
                    Thread.sleep(25);
                } catch (InterruptedException ex) {
                    Logger.getLogger(BIOS.class.getName()).log(Level.SEVERE, null, ex);
                }
            }
        }
        
        private void UpdateThread(double timeSeconds) {
            if (panel != null) {
                panel.Update(timeSeconds);
            }
        }
    }
    
    public void StartThreads() {
        t1 = new Thread(updateThread);
        t1.start();
    }

    public void Stop() {
        stopThreads.set(true);
    }

}