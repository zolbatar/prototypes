package bz.panels;

import bz.ui.ClickList;
import bz.ui.RetroUI;
import javafx.scene.input.KeyCode;

public class PanelTemplate extends Panel {
    private boolean rebooting = true;
    private final ClickList clickList = new ClickList();
    
    @Override
    public void Init() {
        RetroUI.Reset();
    }

    @Override
    public void PostReset() {
        rebooting = false;
    }

    @Override
    public void Render(double delta, double time) {
        if (!rebooting) {
            RetroUI.SetContent(0);
        }
    }

    @Override
    public void MouseClicked(int x, int y) {
    }
    
    @Override
    public void Update(double timeSeconds) {
    }

    @Override
    public void KeyPressed(KeyCode e) {
    }
}
