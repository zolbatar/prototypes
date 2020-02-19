package bz.game.universe;

import java.util.*;
import bz.library.Point;
import bz.spaceobjects.*;
import bz.TCS;

public class SolarSystem {
    private static int IDSequence = 0;
    private final int ID;
    private final SunType sun;
    private final double sunSize;
    private final PlanetType[] planets;
    private final double[] planetSize;
    private final int numberOfMoons[];
    private final List<List<MoonType>> moons;
    private final List<List<Double>> moonSizes;
    private final Point position, translatedPosition;

    public SolarSystem(Point position) {
        this.position = position;
        this.ID = IDSequence++;
        Random r = TCS.GetRandom();

        // Sun
        sun = SetSunType(r);
        sunSize = ((r.nextDouble() * 5.0) + 5.0) * 1000.0;

        // Planets
        int numPlanets = r.nextInt(3) + 1;
        planets = new PlanetType[numPlanets];
        planetSize = new double[numPlanets];
        numberOfMoons = new int[numPlanets];
        moons = new ArrayList(numPlanets);
        moonSizes = new ArrayList(numPlanets);
        for (int i = 0; i < numPlanets; i++) {
            planets[i] = SetPlanetType(r);
            planetSize[i] = ((r.nextDouble() * 5.0) + 5.0) * 5000.0;
            numberOfMoons[i] = r.nextInt(5);
            List<MoonType> moonSet = new ArrayList<>(numberOfMoons[i]);
            List<Double> moonSizeSet = new ArrayList<>(numberOfMoons[i]);
            for (int j = 0; j < numberOfMoons[i]; j++) {
                moonSet.add(SetMoonType(r));
                moonSizeSet.add(((r.nextDouble() * 3.0) + 0.5) * 2000.0);
            }
            moons.add(moonSet);
            moonSizes.add(moonSizeSet);
        }
        this.translatedPosition = new Point(0, 0);
    }
    
    public int GetID() {
        return ID;
    }
    
    public Point GetTranslatedPosition() {
        return translatedPosition;
    }
    
    public SunType GetSun() {
        return sun;
    }
    
    public Point GetPosition() {
        return position;
    }
    
    public PlanetType[] GetPlanets() {
        return planets;
    }
    
    private SunType SetSunType(Random r) {
        return TCS.GetAssets().GetSun(r.nextInt(bz.TCS.GetAssets().GetNumberOfSuns()));
    }

    private PlanetType SetPlanetType(Random r) {
        return TCS.GetAssets().GetPlanet(r.nextInt(bz.TCS.GetAssets().GetNumberOfPlanets()));
    }

    private MoonType SetMoonType(Random r) {
        return TCS.GetAssets().GetMoon(r.nextInt(bz.TCS.GetAssets().GetNumberOfMoons()));
    }
}
