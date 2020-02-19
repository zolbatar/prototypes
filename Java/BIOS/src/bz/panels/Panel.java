package bz.panels;

import java.util.*;
import javafx.scene.input.KeyCode;
import bz.BIOS;

public class Panel {
    private final Map<KeyCode, Character> keyMapping = new HashMap<KeyCode, Character>() {
        {
            put(KeyCode.SPACE, ' ');
            put(KeyCode.A, 'A');
            put(KeyCode.B, 'B');
            put(KeyCode.C, 'C');
            put(KeyCode.D, 'D');
            put(KeyCode.E, 'E');
            put(KeyCode.F, 'F');
            put(KeyCode.G, 'G');
            put(KeyCode.H, 'H');
            put(KeyCode.I, 'I');
            put(KeyCode.J, 'J');
            put(KeyCode.K, 'K');
            put(KeyCode.L, 'L');
            put(KeyCode.M, 'M');
            put(KeyCode.N, 'N');
            put(KeyCode.O, 'O');
            put(KeyCode.P, 'P');
            put(KeyCode.Q, 'Q');
            put(KeyCode.R, 'R');
            put(KeyCode.S, 'S');
            put(KeyCode.T, 'T');
            put(KeyCode.U, 'U');
            put(KeyCode.V, 'V');
            put(KeyCode.W, 'W');
            put(KeyCode.X, 'X');
            put(KeyCode.Y, 'Y');
            put(KeyCode.Z, 'Z');
            put(KeyCode.DIGIT0, '0');
            put(KeyCode.DIGIT1, '1');
            put(KeyCode.DIGIT2, '2');
            put(KeyCode.DIGIT3, '3');
            put(KeyCode.DIGIT4, '4');
            put(KeyCode.DIGIT5, '5');
            put(KeyCode.DIGIT6, '6');
            put(KeyCode.DIGIT7, '7');
            put(KeyCode.DIGIT8, '8');
            put(KeyCode.DIGIT9, '9');
        }
    };
    
    public void Init() {
    }

    public void PostReset() {
    }

    public void KeyPressed(KeyCode e) {
        switch (e) {
            default:
                if (keyMapping.containsKey(e)) {
                    char c = keyMapping.get(e);
                    BIOS.GetConsole().KeyEntered(c);
                }
                break;
        }
    }
    
    public void MouseClicked(int x, int y) {
    }
    
    public void Render(double delta, double time) {
    }

    public void Update(double timeSeconds) {
    }
    
}
