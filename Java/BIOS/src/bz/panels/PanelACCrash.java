package bz.panels;

import bz.BIOS;
import bz.font.ConsoleFont;
import bz.ui.ClickList;
import javafx.scene.image.Image;
import javafx.scene.input.KeyCode;
import bz.ui.RetroUI;
import bz.ui.UIImage;
import bz.ui.UIShapes;
import bz.ui.UIString;
import javafx.scene.paint.Color;

public class PanelACCrash extends Panel {
    private boolean rebooting = true;
    private double lastTime = 0;
    private int phase = 0, search = 0;
    private final ClickList clickList = new ClickList();

    public PanelACCrash() {
    }
    
    @Override
    public void Init() {
        RetroUI.SetConsoleFont(ConsoleFont.VGA);
        RetroUI.Reset();
    }

    @Override
    public void PostReset() {
        rebooting = false;
        RetroUI.WriteString("Firmware checksum error, unable to boot.¬n¬nSearching for bluetooth keyboard");
        lastTime = BIOS.GetTime();
    }

    @Override
    public void Render(double delta, double time) {
        if (!rebooting) {
            if (phase == 0) {
                lastTime += delta;
                if (lastTime > 1.0) {
                    lastTime = 0;
                    RetroUI.WriteCharacter('.');
                    search++;
                    if (search == 10) {
                        RetroUI.WriteString("found.¬n¬nSearching for network boot images");
                        phase = 1;
                        search = 0;
                    }
                }
            } else if (phase == 1) {
                lastTime += delta;
                if (lastTime > 1.0) {
                    lastTime = 0;
                    RetroUI.WriteCharacter('.');
                    search++;
                    if (BIOS.GetRandom().nextDouble() > 0.9 || search > 6) {
                        RetroUI.WriteString("found 1.¬n¬n");
                        RetroUI.WriteString("[1] Nu-DOS¬n¬n");
                        RetroUI.WriteString("Enter [1-1] to load boot image.");
                        phase = 2;
                    }
                }
            } else if (phase == 2) {
                
            }
        }
    }

    @Override
    public void MouseClicked(int x, int y) {
        String r = this.clickList.CheckClick(x, y);
        if (r != null) {
            switch (r) {
            }
        }
   }
    
    @Override
    public void Update(double timeSeconds) {
    }

    @Override
    public void KeyPressed(KeyCode e) {
    }

}
