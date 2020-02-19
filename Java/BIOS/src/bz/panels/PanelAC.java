package bz.panels;

import javafx.scene.image.*;
import javafx.scene.input.KeyCode;
import javafx.scene.layout.Pane;
import javafx.scene.shape.*;
import javafx.scene.text.Text;
import javafx.scene.SnapshotParameters;
import javafx.scene.paint.Color;
import bz.BIOS;
import bz.ui.*;

public class PanelAC extends Panel {
    private double temperature = 20.0, temperatureSet = 20.0, searchStarted, progress = 0;
    private boolean inCelsius = true, recyleOnly = false, rebooting = true, updating = false;
    private int fanSpeed = 1, mode = 1;
    private final ClickList clickList = new ClickList();
    
    // Main screen
    private final Image imgTxtTitle, imgSun, imgSnow, imgRain, imgWind, imgFanSpeed, imgMode, imgModeSelected, imgModeNotSelected;
    private final Image imgSelected, imgNotSelected, imgC, imgF, imgCSelected, imgFSelected, imgTempSelected, imgTempNotSelected;
    private final Image imgFreshAir, imgOnSelected, imgOffSelected, imgOn, imgOff, imgOnOffNotSelected, imgOnOffSelected;
    private final Image imgTemperature, imgPlus, imgNegative, imgReset, imgUpdate, imgButtonOuter;
    private Image imgFanSpeed1, imgFanSpeed2, imgFanSpeed3;
    private Image imgThermometerC, imgThermometerF;
    
    // Reset screen
    private final Image imgSearching, imgUpdating, imgInstalling, imgMess1, imgMess2;
    
    public PanelAC() {
        imgSearching = UIString.CreateImageString("Searching for update server...".toUpperCase(), RetroUI.GetSansFont(), 15.0, 1.0);
        imgUpdating = UIString.CreateImageString("Downloading update...".toUpperCase(), RetroUI.GetSansFont(), 15.0, 1.0);
        imgInstalling = UIString.CreateImageString("Installing...".toUpperCase(), RetroUI.GetSansFont(), 15.0, 1.0);
        imgMess1 = UIString.CreateImageString("Do NOT reset the unit while update is in progress as this can cause", RetroUI.GetSansFont(), 12.0, 1.0);
        imgMess2 = UIString.CreateImageString("the unit to become inoperable and require service.", RetroUI.GetSansFont(), 12.0, 1.0);

        // Main screen
        imgSun = new Image(getClass().getResource("/bz/panels/AssetsAC/Sun.png").toExternalForm(), 30, 30, true, true);
        imgSnow = new Image(getClass().getResource("/bz/panels/AssetsAC/Snow.png").toExternalForm(), 30, 30, true, true);
        imgRain = new Image(getClass().getResource("/bz/panels/AssetsAC/Rain.png").toExternalForm(), 30, 30, true, true);
        imgWind = new Image(getClass().getResource("/bz/panels/AssetsAC/Wind.png").toExternalForm(), 30, 30, true, true);
        imgTxtTitle = UIString.CreateImageString("Primax Air Conditioning".toUpperCase(), RetroUI.GetBebasNeue(), 30.0, 1.0);
        imgCSelected = UIString.CreateImageString("°C".toUpperCase(), RetroUI.GetSansFontBold(), 12.0, 1.0, Color.WHITE, RetroUI.VeryLightGrey);
        imgFSelected = UIString.CreateImageString("°F".toUpperCase(), RetroUI.GetSansFontBold(), 12.0, 1.0, Color.WHITE, RetroUI.VeryLightGrey);
        imgFreshAir = UIString.CreateImageString("Recycle Only:", RetroUI.GetSansFont(), 16.0, 1.0);
        imgOn = UIString.CreateImageString("On", RetroUI.GetSansFontLight(), 16.0, 0.75);
        imgOff = UIString.CreateImageString("Off", RetroUI.GetSansFontLight(), 16.0, 0.75);
        imgOnSelected = UIString.CreateImageString("On", RetroUI.GetSansFontLight(), 16.0, 1.0, Color.WHITE, RetroUI.VeryLightGrey);
        imgOffSelected = UIString.CreateImageString("Off", RetroUI.GetSansFontLight(), 16.0, 1.0, Color.WHITE, RetroUI.VeryLightGrey);
        imgC = UIString.CreateImageString("°C", RetroUI.GetSansFontLight(), 12.0, 0.75);
        imgF = UIString.CreateImageString("°F", RetroUI.GetSansFontLight(), 12.0, 0.75);
        imgFanSpeed = UIString.CreateImageString("Fan Speed:", RetroUI.GetSansFont(), 16.0, 1.0);
        imgMode = UIString.CreateImageString("Mode:", RetroUI.GetSansFont(), 16.0, 1.0);
        imgTemperature = UIString.CreateImageString("Temperature:", RetroUI.GetSansFont(), 16.0, 1.0);
        imgPlus = UIString.CreateImageString("+", RetroUI.GetSansFont(), 23.0, 1.0);
        imgNegative = UIString.CreateImageString("-", RetroUI.GetSansFont(), 23.0, 1.0);
        imgReset = UIString.CreateImageString("Reset", RetroUI.GetSansFont(), 9.0, 1.0);
        imgUpdate = UIString.CreateImageString("Update", RetroUI.GetSansFont(), 9.0, 1.0);
        
        // Boxes
        imgSelected = UIShapes.CreateBox(40, 20, 1.5, 2.0, RetroUI.VeryLightGrey, Color.WHITE);
        imgTempSelected = UIShapes.CreateBox(18, 17, 1.5, 2.0, RetroUI.VeryLightGrey, Color.WHITE);
        imgModeSelected = UIShapes.CreateBox(32, 32, 1.5, 2.0, RetroUI.VeryLightGrey, Color.WHITE);
        imgOnOffSelected = UIShapes.CreateBox(65, 21, 1.0, 2.0, RetroUI.VeryLightGrey, Color.WHITE);
        imgNotSelected = UIShapes.CreateBox(40, 20, 1.0, 2.0, Color.BLACK, Color.LIGHTGRAY);
        imgTempNotSelected = UIShapes.CreateBox(18, 17, 1.0, 2.0, Color.BLACK, Color.LIGHTGRAY);
        imgModeNotSelected = UIShapes.CreateBox(32, 32, 1.0, 2.0, Color.BLACK, Color.LIGHTGRAY);
        imgOnOffNotSelected = UIShapes.CreateBox(65, 21, 1.0, 2.0, Color.BLACK, Color.LIGHTGRAY);
        imgButtonOuter = UIShapes.CreateBox(40, 12, 0.75, 2.0, Color.BLACK, Color.LIGHTGRAY);
    }
    
    private void RebuildThermos() {
        if (temperature >= 35) {
            temperature = 35;
        } else if (temperature < 15) {
            temperature = 15;
        }
        imgThermometerC = CreateThermometer(true);
        imgThermometerF = CreateThermometer(false);
        if (fanSpeed == 1) {
            imgFanSpeed1 = UIString.CreateImageString("L", RetroUI.GetSansFontBold(), 14.0, 1.0, Color.WHITE, RetroUI.VeryLightGrey);
            imgFanSpeed2 = UIString.CreateImageString("M", RetroUI.GetSansFontLight(), 14.0, 0.75);
            imgFanSpeed3 = UIString.CreateImageString("H", RetroUI.GetSansFontLight(), 14.0, 0.75);
        } else if (fanSpeed == 2) {
            imgFanSpeed1 = UIString.CreateImageString("L", RetroUI.GetSansFontLight(), 14.0, 0.75);
            imgFanSpeed2 = UIString.CreateImageString("M", RetroUI.GetSansFontBold(), 14.0, 1.0, Color.WHITE, RetroUI.VeryLightGrey);
            imgFanSpeed3 = UIString.CreateImageString("H", RetroUI.GetSansFontLight(), 14.0, 0.75);
        } else if (fanSpeed == 3) {
            imgFanSpeed1 = UIString.CreateImageString("L", RetroUI.GetSansFontLight(), 14.0, 0.75);
            imgFanSpeed2 = UIString.CreateImageString("M", RetroUI.GetSansFontLight(), 14.0, 0.75);
            imgFanSpeed3 = UIString.CreateImageString("H", RetroUI.GetSansFontBold(), 14.0, 1.0, Color.WHITE, RetroUI.VeryLightGrey);
        }
    }
    
    @Override
    public void Init() {
        RetroUI.Reset();
    }

    @Override
    public void PostReset() {
        rebooting = false;
        temperatureSet = 20;
        fanSpeed = 1;
        mode = 1;
    }

    @Override
    public void Render(double delta, double time) {
        clickList.Clear();
        if (!rebooting) {
            if (!updating) {
                RedrawMain();
            } else {
                RedrawUpdating(delta, time);
            }
        }
    }
    
    private void RedrawUpdating(double delta, double time) {
        RetroUI.SetContent(0);
        UIImage.RenderImageCentre(imgTxtTitle, 0);
        if (time - searchStarted < 5.0) {
            UIImage.RenderImageCentre(imgSearching, 50);
        } else if (progress < 100.0) {
            UIImage.RenderImageCentre(imgUpdating, 50);
            progress += delta * ((BIOS.GetRandom().nextDouble() * 0.5) + 0.5) * 15.0;
            if (progress > 100.0) {
                progress = 100.0;
            }
            Image img = UIShapes.CreateProgressBar(150, 10, 1.0, 2.0, progress / 100.0, Color.BLACK, Color.LIGHTGRAY, Color.DARKGRAY);
            UIImage.RenderImageCentre(img, 80);
       } else if (progress < 200.0) {
            UIImage.RenderImageCentre(imgInstalling, 50);
            UIImage.RenderImageCentre(imgMess1, 130);
            UIImage.RenderImageCentre(imgMess2, 150);
            progress += delta * ((BIOS.GetRandom().nextDouble() * 0.5) + 0.5) * 25.0;
            if (progress > 200.0) {
                progress = 200.0;
                updating = false;
                rebooting = true;
                RetroUI.Reset();
            }
            Image img = UIShapes.CreateProgressBar(150, 10, 1.0, 2.0, (progress - 100.0) / 100.0, Color.BLACK, Color.LIGHTGRAY, Color.DARKGRAY);
            UIImage.RenderImageCentre(img, 80);
        }

        // Reset
        UIImage.RenderImage(imgButtonOuter, 355, 5);
        UIImage.RenderImageCentreInWidth(imgReset, 358, 395, 6);
        clickList.AddItem(355, 5, 40, 12, "Reset");
    }
    
    private void RedrawMain() {
        RetroUI.SetContent(0);
        RebuildThermos();
        UIImage.RenderImageCentre(imgTxtTitle, 0);
        if (inCelsius) {
            UIImage.RenderImage(imgThermometerC, 10, 25);
            UIImage.RenderImage(imgTempSelected, 7, 7);
            UIImage.RenderImage(imgTempNotSelected, 33, 7);
            UIImage.RenderImage(imgCSelected, 11, 9);
            UIImage.RenderImage(imgF, 37, 9);
        } else {
            UIImage.RenderImage(imgThermometerF, 10, 25);
            UIImage.RenderImage(imgTempNotSelected, 7, 7);
            UIImage.RenderImage(imgTempSelected, 33, 7);
            UIImage.RenderImage(imgC, 11, 9);
            UIImage.RenderImage(imgFSelected, 37, 9);
        }
        clickList.AddItem(7, 7, 18, 17, "C");
        clickList.AddItem(33, 7, 18, 17, "F");
 
        // Mode
        UIImage.RenderImageRight(imgMode, 200, 50);
        if (mode == 1) {
            UIImage.RenderImage(imgModeSelected, 215, 43);
        } else {
            UIImage.RenderImage(imgModeNotSelected, 215, 43);
        }
        UIImage.RenderImage(imgSnow, 217, 45, RenderType.OPACITY);
        clickList.AddItem(215, 43, 32, 32, "Heat");
        if (mode == 2) {
            UIImage.RenderImage(imgModeSelected, 251, 43);
        } else {
            UIImage.RenderImage(imgModeNotSelected, 251, 43);
        }
        UIImage.RenderImage(imgSun, 253, 45, RenderType.OPACITY);
        clickList.AddItem(251, 43, 32, 32, "Cold");
        if (mode == 3) {
            UIImage.RenderImage(imgModeSelected, 287, 43);
        } else {
            UIImage.RenderImage(imgModeNotSelected, 287, 43);
        }
        clickList.AddItem(287, 43, 32, 32, "Air");
        UIImage.RenderImage(imgWind, 289, 45, RenderType.OPACITY);
        if (mode == 4) {
            UIImage.RenderImage(imgModeSelected, 323, 43);
        } else {
            UIImage.RenderImage(imgModeNotSelected, 323, 43);
        }
        clickList.AddItem(323, 43, 32, 32, "Dehumidify");
        UIImage.RenderImage(imgRain, 325, 45, RenderType.OPACITY);

        int y = 97;
        UIImage.RenderImageRight(imgFanSpeed, 200, y);
        // Low speed
        if (fanSpeed == 1) {
            UIImage.RenderImage(imgSelected, 215, y - 2);
        } else {
            UIImage.RenderImage(imgNotSelected, 215, y - 2);
        }
        clickList.AddItem(215, y - 2, 40, 20, "L");
        UIImage.RenderImage(imgFanSpeed1, 232, y + 1);
        
        // Medium speed
        int x = (int)(232 + 30 + 20);
        if (fanSpeed == 2) {
            UIImage.RenderImage(imgSelected, x - 17, y - 2);
        } else {
            UIImage.RenderImage(imgNotSelected, x - 17, y - 2);
        }
        clickList.AddItem(x - 17, y - 2, 40, 20, "M");
        UIImage.RenderImage(imgFanSpeed2, x - 2, y + 1);
        
        // High speed
        x = (int)(232 + 60 + 40);
        if (fanSpeed == 3) {
            UIImage.RenderImage(imgSelected, x - 17, y - 2);
        } else {
            UIImage.RenderImage(imgNotSelected, x - 17, y - 2);
        }
        clickList.AddItem(x - 17, y - 2, 40, 20, "H");
        UIImage.RenderImage(imgFanSpeed3, x - 1, y + 1);

        // Fresh air
        y = 140;
        UIImage.RenderImageRight(imgFreshAir, 200, y);
        if (recyleOnly) {
            UIImage.RenderImage(imgOnOffSelected, 215, y - 2);
            UIImage.RenderImage(imgOnSelected, 237, y);
            UIImage.RenderImage(imgOnOffNotSelected, 290, y - 2);
            UIImage.RenderImage(imgOff, 312, y);
        } else {
            UIImage.RenderImage(imgOnOffNotSelected, 215, y - 2);
            UIImage.RenderImage(imgOn, 237, y);
            UIImage.RenderImage(imgOnOffSelected, 290,y - 2);
            UIImage.RenderImage(imgOffSelected, 312, y);
        }
        clickList.AddItem(215, y - 2, 65, 21, "FreshAirOn");
        clickList.AddItem(290, y - 2, 65, 21, "FreshAirOff");

        // Temperature
        UIImage.RenderImageRight(imgTemperature, 200, 186);
        if (this.inCelsius) {
            Image imgTemp = UIString.CreateImageString(String.valueOf((int)temperatureSet), RetroUI.GetSansFontBold(), 24.0, 1.0);
            UIImage.RenderImageCentreInWidth(imgTemp, 215 + 32, 323, 182);
        } else {
            Image imgTemp = UIString.CreateImageString(String.valueOf((int)this.CelsiusToFahrenheit(temperatureSet)), RetroUI.GetSansFontBold(), 24.0, 1.0);
            UIImage.RenderImageCentreInWidth(imgTemp, 215 + 32, 323, 182);
        }
        UIImage.RenderImage(imgModeNotSelected, 215, 180);
        UIImage.RenderImage(imgNegative, 226, 182);
        UIImage.RenderImage(imgModeNotSelected, 323, 180);
        UIImage.RenderImage(imgPlus, 334, 182);
        clickList.AddItem(215, 180, 32, 32, "-");
        clickList.AddItem(323, 180, 32, 32, "+");
        
        // Buttons
        UIImage.RenderImage(imgButtonOuter, 355, 5);
        UIImage.RenderImageCentreInWidth(imgReset, 358, 395, 6);
        UIImage.RenderImage(imgButtonOuter, 355, 20);
        UIImage.RenderImageCentreInWidth(imgUpdate, 358, 395, 21);
        clickList.AddItem(355, 5, 40, 12, "Reset");
        clickList.AddItem(355, 20, 40, 12, "Update");
    }
    
    @Override
    public void MouseClicked(int x, int y) {
        String r = this.clickList.CheckClick(x, y);
        if (r != null) {
            switch (r) {
                case "C":
                    inCelsius = true;
                    temperatureSet = Math.round(temperatureSet);
                    break;
                case "F":
                    inCelsius = false;
                    double a = Math.round(this.CelsiusToFahrenheit(temperatureSet));
                    temperatureSet = this.FahrenheitToCelsius(a);
                    break;
                case "Heat":
                    mode = 1;
                    break;
                case "Cold":
                    mode = 2;
                    break;
                case "Air":
                    mode = 3;
                    break;
                case "Dehumidify":
                    mode = 4;
                    break;
                case "L":
                    fanSpeed = 1;
                    break;
                case "M":
                    fanSpeed = 2;
                    break;
                case "H":
                    fanSpeed = 3;
                    break;
                case "FreshAirOn":
                    recyleOnly = true;
                    break;
                case "FreshAirOff":
                    recyleOnly = false;
                    break;
                case "-":
                    TempDown();
                    break;
                case "+":
                    TempUp();
                    break;
                case "Reset":
                    if (updating && progress > 100 && progress < 200) {
                        BIOS.SetPanelACCrash();
                    }
                    rebooting = true;
                    RetroUI.Reset();
                    break;
                case "Update":
                    updating = true;
                    progress = 0;
                    searchStarted = BIOS.GetTime();
                    break;
            }
        }
    }
    
    @Override
    public void Update(double timeSeconds) {
        double diff = (temperatureSet - temperature) * timeSeconds * 0.01;
        double diffRoom = (20 - temperature) * timeSeconds * 0.01;

        // Do we need to change the temperature
        switch (mode) {
            case 2: // Heating
                if (diff > 0) {

                    // The further from 20 it is, the harder it is to change the temperature
                    double diffNormal = Math.abs(temperatureSet - 20) * 0.0001;
                    diff -= diffNormal;

                    temperature += (diff * ((double)fanSpeed / 3));
                } else if (diffRoom > 0) {
                    double diffNormal = Math.abs(temperatureSet - 20) * 0.0001;
                    diffRoom -= diffNormal;
                    temperature -= (diffRoom * ((double)fanSpeed / 3));
                }
                break;
            case 1: // Cooling
                if (diff < 0) {

                    // The further from 20 it is, the harder it is to change the temperature
                    double diffNormal = Math.abs(temperatureSet - 20) * 0.0001;
                    diff -= diffNormal;

                    temperature += (diff * ((double)fanSpeed / 3));
                } else if (diffRoom < 0) {
                   double diffNormal = Math.abs(temperatureSet - 20) * 0.0001;
                    diffRoom -= diffNormal;
                    temperature += (diffRoom * ((double)fanSpeed / 3));
                }
                break;
            case 3: // Vent only
            case 4: // Dehumidify
                if (diffRoom > 0 && temperature < 20) {
                    double diffNormal = Math.abs(temperatureSet - 20) * 0.0001;
                    diffRoom -= diffNormal * 0.1;
                    temperature -= (diffRoom * ((double)fanSpeed / 3));
                } else if (diffRoom < 0 && temperature > 20) {
                    double diffNormal = Math.abs(temperatureSet - 20) * 0.0001;
                    diffRoom -= diffNormal * 0.1;
                    temperature += (diffRoom * ((double)fanSpeed / 3));
                }
                break;
        }
    }

    @Override
    public void KeyPressed(KeyCode e) {
        switch (e) {
            default:
//                super.KeyPressed(e);
                break;
        }
    }
    
    private void TempUp() {
        if (inCelsius) {
            temperatureSet++;
        } else {
            temperatureSet = this.FahrenheitToCelsius(Math.round(this.CelsiusToFahrenheit(temperatureSet + 1.8)));
        }
        if (temperatureSet >= 35) {
            temperatureSet = 35;
        } else if (temperatureSet < 15) {
            temperatureSet = 15;
        }
   }

    private void TempDown() {
        if (inCelsius) {
            temperatureSet--;
        } else {
            temperatureSet = this.FahrenheitToCelsius(Math.round(this.CelsiusToFahrenheit(temperatureSet - 1.8)));
        }
        if (temperatureSet >= 35) {
            temperatureSet = 35;
        } else if (temperatureSet < 15) {
            temperatureSet = 15;
        }
    }

    private Image CreateThermometer(boolean inCelsius) {
        // Thermometer
        SnapshotParameters sn = new SnapshotParameters();
        sn.setFill(Color.BLACK);
        Pane p = new Pane();
        Circle c = new Circle(20, 180, 18);
        c.setStrokeWidth(0);
        c.setFill(Color.LIGHTGRAY);
        p.getChildren().add(c);
        c = new Circle(20, 20, 10);
        c.setStrokeWidth(0);
        c.setFill(Color.LIGHTGRAY);
        p.getChildren().add(c);
        Rectangle r = new Rectangle(11, 20, 18, 160);
        r.setFill(Color.BLACK);
        r.setStroke(Color.LIGHTGRAY);
        r.setStrokeWidth(2.0);
        p.getChildren().add(r);
        c = new Circle(20, 20, 8);
        c.setStrokeWidth(0);
        c.setFill(Color.BLACK);
        p.getChildren().add(c);
        c = new Circle(20, 180, 16);
        c.setStrokeWidth(0);
        c.setFill(Color.GRAY);
        p.getChildren().add(c);
        
        // Temperatures
        if (inCelsius) {
            for (double t = 15; t <= 35; t++) {
                double y = 160 - ((t - 15) * 7);
                Line l = new Line(32, y, 35, y);
                l.setStroke(Color.LIGHTGRAY);
                l.setStrokeWidth(1.0);
                p.getChildren().add(l);
            }
            for (double t = 15; t <= 35; t += 5) {
                double y = 160 - ((t - 15) * 7);
                Line l = new Line(32, y, 40, y);
                l.setStroke(Color.WHITE);
                l.setStrokeWidth(1.0);
                p.getChildren().add(l);
                Text te = new Text(42, y + 4, String.valueOf(t));
                te.setFont(RetroUI.GetSansFontLight().GetFont(12));
                te.setFill(Color.WHITE);
                te.setStrokeWidth(0.0);
                p.getChildren().add(te);
            }
        } else {
            for (double t = 60; t <= 95; t += 2) {
                double y = 160 - ((FahrenheitToCelsius(t) - 15) * 7);
                Line l = new Line(32, y, 35, y);
                l.setStroke(Color.LIGHTGRAY);
                l.setStrokeWidth(1.0);
                p.getChildren().add(l);
            }
            for (double t = 60; t <= 95; t += 10) {
                double y = 160 - ((FahrenheitToCelsius(t) - 15) * 7);
                Line l = new Line(32, y, 40, y);
                l.setStroke(Color.WHITE);
                l.setStrokeWidth(1.0);
                p.getChildren().add(l);
                Text te = new Text(42, y + 4, String.valueOf(t));
                te.setFont(RetroUI.GetSansFontLight().GetFont(12));
                te.setFill(Color.WHITE);
                te.setStrokeWidth(0.0);
                p.getChildren().add(te);
            }
        }
        
        // Render temperature
        double y = 160 - ((temperature - 15) * 7);
        double h = 180 - y;
        r = new Rectangle(12, y, 16, h);
        r.setFill(Color.GRAY);
        r.setStrokeWidth(0.0);
        p.getChildren().add(r);
        if (temperature >= 35) {
            c = new Circle(20, 20, 8);
            c.setStrokeWidth(0);
            c.setFill(Color.GRAY);
            p.getChildren().add(c);
        }

        return p.snapshot(sn, null);
    }
    
    private double CelsiusToFahrenheit(double v) {
        return ((9 * v) / 5) + 32;
    }
    
    private double FahrenheitToCelsius(double v) {
        return ((v - 32) * 5) / 9; 
    }

}
