package bz.panels.menu;

import java.net.URL;
import java.util.ResourceBundle;
import javafx.fxml.Initializable;
import javafx.fxml.FXML;
import javafx.scene.control.Label;
import javafx.scene.control.ProgressBar;
import javafx.scene.control.ToggleButton;
import javafx.scene.layout.StackPane;
import javafx.event.ActionEvent;
import bz.Parameters;
import bz.TCS;
import bz.game.Difficulty;
import bz.game.Game;
import bz.game.GameSize;
import java.util.logging.Level;
import java.util.logging.Logger;

public class FXMLMenuController implements Initializable {
    private boolean menuHidden = false;
    private double pos = 0.0;
    private String text = "";
    @FXML
    private Label lbLoading;
    @FXML
    private ProgressBar pbLoading;
    @FXML
    private StackPane spMenu;
    @FXML
    private StackPane spStartGame;
    @FXML
    private ToggleButton tbEasy;
    @FXML
    private ToggleButton tbMedium;
    @FXML
    private ToggleButton tbHard;
    @FXML
    private ToggleButton tbSmall;
    @FXML
    private ToggleButton tbMediumSize;
    @FXML
    private ToggleButton tbLarge;
    
    @Override
    public void initialize(URL url, ResourceBundle rb) {
    }    
    
    public void Update() {
        if (text.isEmpty()) {
            lbLoading.setVisible(false);
            pbLoading.setVisible(false);
            TCS.ShowMenu();
        } else {
            lbLoading.setText(text);
            pbLoading.setProgress(pos);
        }
    }
    
    public void ResetProgress() {
        SetProgress(0, "");
        lbLoading.setVisible(true);
        pbLoading.setVisible(true);
    }
    
    public void FinishProgress() {
        SetProgress(0, "");
    }

    public void SetProgress(int position) {
        pos = (double)position / (double)Parameters.LOADING_STEPS;
    }

    public void SetProgress(int position, String t) {
        text = t;
        pos = (double)position / (double)Parameters.LOADING_STEPS;
    }

    public void ShowMenu() {
        spMenu.setVisible(true);
        menuHidden = false;
    }
    
    public void HideMenu() {
        spMenu.setVisible(false);
        menuHidden = true;
    }

    @FXML
    private void quitGame(ActionEvent event) {
        TCS.Close();
    }

    @FXML
    private void playGame(ActionEvent event) {
        HideMenu();
        spStartGame.setVisible(true);
        TCS.BeepMenu();
    }

    @FXML
    private void choosePlay(ActionEvent event) {
        spStartGame.setVisible(false);
        TCS.BeepMenu();
        Difficulty d;
        if (tbMedium.isSelected()) {
            d = Difficulty.MEDIUM;
        } else if (tbHard.isSelected()) {
            d = Difficulty.HARD;
        } else {
            d = Difficulty.EASY;
        }
        GameSize gs;
        if (tbMediumSize.isSelected()) {
            gs = GameSize.NORMAL;
        } else if (tbLarge.isSelected()) {
            gs = GameSize.LONG;
        } else {
            gs = GameSize.QUICK;
        }
        Game game = new Game(d, gs);
        TCS.SceneGame(game);
    }

    @FXML
    private void chooseCancel(ActionEvent event) {
        ShowMenu();
        spStartGame.setVisible(false);
        TCS.BeepMenu();
    }
}
