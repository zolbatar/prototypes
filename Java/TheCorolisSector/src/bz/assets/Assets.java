package bz.assets;

import javafx.scene.media.AudioClip;
import javafx.scene.image.Image;
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.util.LinkedList;
import java.util.List;
import java.util.logging.Level;
import java.util.logging.Logger;
import javafx.scene.image.PixelReader;
import javafx.scene.paint.Color;
import bz.spaceobjects.PlanetType;
import bz.spaceobjects.MoonType;
import bz.spaceobjects.AsteroidType;
import bz.spaceobjects.SunType;
import bz.Parameters;
import bz.TCS;

public class Assets {
    private final int numberOfPlanets = 8, numberOfAsteroids = 8, numberOfSuns = 4, numberOfMoons = 8;
    private final AsteroidType[] asteroids;
    private final MoonType[] moons;
    private final PlanetType[] planets;
    private final SunType[] suns;
    private final AudioClip audioBeepLo, audioBeepHi;
    public final Color ColourBlue100_50;

    public Assets() {
        TCS.GetControllerMenu().ResetProgress();
        int position = 0;
        
        // Colours
        ColourBlue100_50 = Color.rgb(0, 100, 0, 0.5);
        
        // Load asteriods
        TCS.GetControllerMenu().SetProgress(position, "Loading asteroids..."); 
        asteroids = new AsteroidType[numberOfAsteroids];
        for (int i = 0; i < numberOfAsteroids; i++) {
            String s = "/bz/assets/asteroids/Asteroid" + Integer.toString(i + 1) + ".png";
            System.out.println("Loading asteroid: " + s);
            Image img = new Image(getClass().getResource(s).toExternalForm(), 512, 512, true, Parameters.SMOOTH);
            AsteroidType asteroid = new AsteroidType(img);
            asteroids[i] = asteroid;
            TCS.GetControllerMenu().SetProgress(position++);        
        }

        // Load moons
        TCS.GetControllerMenu().SetProgress(position, "Loading moons..."); 
        moons = new MoonType[numberOfMoons];
        for (int i = 0; i < numberOfMoons; i++) {
            String s = "/bz/assets/moons/Moon" + Integer.toString(i + 1) + ".png";
            System.out.println("Loading moon: " + s);
            Image img = new Image(getClass().getResource(s).toExternalForm(), 256, 256, true, Parameters.SMOOTH);
            MoonType moon = new MoonType(img);
            moons[i] = moon;
            TCS.GetControllerMenu().SetProgress(position++);        
        }

        // Load planets
        TCS.GetControllerMenu().SetProgress(position, "Loading planets..."); 
        planets = new PlanetType[numberOfPlanets];
        for (int i = 0; i < numberOfPlanets; i++) {
            String s = "/bz/assets/planets/planet" + Integer.toString(i + 1) + ".png";
            System.out.println("Loading planet: " + s);
            Image img = new Image(getClass().getResource(s).toExternalForm(), 1024, 1024, true, Parameters.SMOOTH);

            // Planet definition file
            s = "/bz/assets/planets/planet" + Integer.toString(i + 1) + ".txt";
            String[] linesR = ReadAllLines(s);

            PlanetType planet = new PlanetType(linesR[0], img, GetAverage(img));
            planets[i] = planet;
            TCS.GetControllerMenu().SetProgress(position++);        
        }

        // Load suns
        TCS.GetControllerMenu().SetProgress(position, "Loading suns..."); 
        suns = new SunType[numberOfSuns];
        for (int i = 0; i < numberOfSuns; i++) {
            String s = "/bz/assets/suns/Sun" + Integer.toString(i + 1) + ".png";
            System.out.println("Loading sun: " + s);
            Image img = new Image(getClass().getResource(s).toExternalForm(), 512, 512, true, Parameters.SMOOTH);
            SunType sun = new SunType(img, GetAverage(img));
            suns[i] = sun;
            TCS.GetControllerMenu().SetProgress(position++);        
        }

        // Load audio
        TCS.GetControllerMenu().SetProgress(position, "Loading audio...");        
        audioBeepLo = new AudioClip(getClass().getResource("/bz/assets/audio/BeepLo.aiff").toExternalForm()); TCS.GetControllerMenu().SetProgress(position++);
        audioBeepHi = new AudioClip(getClass().getResource("/bz/assets/audio/BeepHi.aiff").toExternalForm()); TCS.GetControllerMenu().SetProgress(position++);

        TCS.GetControllerMenu().FinishProgress();
    }

    public final Color GetAverage(Image img) {
        PixelReader pixelReader = img.getPixelReader();
        double r = 0.0, g = 0.0, b = 0.0;
        int i = 0;
        for (int y = 0; y < img.getHeight(); y++) {
            for (int x = 0; x < img.getWidth(); x++) {
                Color color = pixelReader.getColor(x, y);
                r += color.getRed();
                g += color.getGreen();
                b += color.getBlue();
                i++;
            }
        }
        r /= i;
        g /= i;
        b /= i;
        return Color.rgb((int)(r * 255), (int)(g * 255), (int)(b * 255));
    }
    
    public final String[] ReadAllLines(String file) {
        List<String> lines = new LinkedList<>();
        try {
            InputStream is = getClass().getResourceAsStream(file);
            if (is == null) {
                System.out.println("Can't open inputstream.");
            }
            BufferedReader in = new BufferedReader(new InputStreamReader(is));
            String line;
            while ((line = in.readLine()) != null) {
                lines.add(line);
            }
        } catch (IOException ex) {
            Logger.getLogger(Assets.class.getName()).log(Level.SEVERE, null, ex);
        }
        return lines.toArray(new String[lines.size()]);
    }
    
    public void PlayLo() {
        this.audioBeepLo.play();
    }

    public void PlayHi() {
        this.audioBeepHi.play();
    }
    
    public int GetNumberOfSuns() {
        return numberOfSuns;
    }

    public int GetNumberOfPlanets() {
        return numberOfPlanets;
    }
    
    public int GetNumberOfMoons() {
        return numberOfMoons;
    }

    public int GetNumberOfAsteroids() {
        return numberOfAsteroids;
    }

    public SunType GetSun(int i) {
        return suns[i];
    }
    
    public PlanetType GetPlanet(int i) {
        return planets[i];
    }

    public MoonType GetMoon(int i) {
        return moons[i];
    }

    public AsteroidType GetAsteroid(int i) {
        return asteroids[i];
    }
}
