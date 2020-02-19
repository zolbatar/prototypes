package bz.console;

import bz.ui.RetroUI;

public class Console {
    private RetroUI ui;
    
    public Console(RetroUI ui) {
        this.ui = ui;
    }
    
    public void KeyEntered(char c) {
        ui.WriteCharacter(c);
    }
    
}
