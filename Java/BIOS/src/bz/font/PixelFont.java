package bz.font;

import bz.BIOS;
import bz.ui.RetroUI;

public class PixelFont {
    protected int[] raw;
    
    public void Init() {
//        System.out.println("Initialising font: [" + raw.length + "]");
    }
    
    public void RenderCharacter(char a, int x, int y) {
        int position = a * 8;
        for (int i = 0; i < 8; i++) {
            int val = raw[position + i];
            for (int j = 0; j < 8; j++) {
                int v = (val & (1 << j)) >> j;
                if (v == 0) {
                    RetroUI.SetPixel((x * 8) + (7 - j), (y * 8) + i, (byte)0);
                } else {
                    RetroUI.SetPixel((x * 8) + (7 - j), (y * 8) + i, (byte)(v * RetroUI.LEVELS - 1));
                }
            }
        }
    }
}
