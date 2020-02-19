package bz.panels;

import bz.BIOS;
import javafx.scene.input.KeyCode;

public class PanelBIOS extends Panel {

    @Override
    public void KeyPressed(KeyCode e) {
        switch (e) {
//                    case TAB:
//                        break;
            default:
                int code = e.ordinal();
                if (e.isLetterKey()) {
                    char c = e.toString().charAt(0);
                    BIOS.GetConsole().KeyEntered(c);
                }
                break;
        }
    }
}
