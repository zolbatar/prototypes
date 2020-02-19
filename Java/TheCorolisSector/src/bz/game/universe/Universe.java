package bz.game.universe;

import java.util.*;
import bz.Parameters;
import bz.TCS;
import bz.library.Helpers;
import bz.library.Point;
import bz.game.*;

public class Universe {
    private final GameSize size;
    private final int numberSectors;
    private final List<SolarSystem> systems;
    private final SolarSystem home, enemy;
    
    public Universe(GameSize size) {
        this.size = size;
        switch (size) {
            default:
                numberSectors = 16;
                break;
            case QUICK:
                numberSectors = 8;
                break;
            case LONG:
                numberSectors = 32;
                break;
        }
        systems = new ArrayList<>(numberSectors);
        
        // Populate
        double leftest_x = Double.MAX_VALUE;
        double rightest_x = Double.MIN_VALUE;
        SolarSystem currentHome = null, currentEnemy = null;
        
        // Create systems
        for (int i = 0; i < numberSectors; i++) {
            Point p = GetNextUniversePoint();
            SolarSystem s = new SolarSystem(p);
            systems.add(s);

            // Friendly/enemy starting sector
            if (p.GetX() < leftest_x) {
                leftest_x = p.GetX();
                currentHome = s;
            }
            if (p.GetX() > rightest_x) {
                rightest_x = p.GetX();
                currentEnemy = s;
            }
        }
        home = currentHome;
        enemy = currentEnemy;
/*        homeSector.SetAlignment(0.5);
        homeSector.SetPlanetTypeTerran();
        targetSector.SetAlignment(-0.5);
        targetSector.SetPlanetTypeAlien();*/
    }
    
    public List<SolarSystem> GetSystems() {
        return systems;
    }

    private Point GetNextUniversePoint() {
        double x = 0.0, y = 0.0;
        boolean close = true;
        while (close) {
            close = false;
            x = (TCS.GetRandom().nextDouble() * (this.GetUniverseSize() - (Parameters.UNIVERSE_PADDING * 2))) - (this.GetUniverseSize() / 2) + Parameters.UNIVERSE_PADDING;
            y = (TCS.GetRandom().nextDouble() * (this.GetUniverseSize() - (Parameters.UNIVERSE_PADDING * 2))) - (this.GetUniverseSize() / 2) + Parameters.UNIVERSE_PADDING;
            for (SolarSystem s : systems) {
                Point p = s.GetPosition();
                double dist = Helpers.DistanceBetweenPoints(x, y, p.GetX(), p.GetY());
                if (dist < DistanceBetweenSystems()) {
                    close = true;
                    break;
                }
            }
        }
        return new Point(x, y);
    }
    
    public double GetUniverseSize() {
        switch (size) {
            default:
                return 96.0;
            case QUICK:
                return 64.0;
            case LONG:
                return 128.0;
        }
    }

    public double DistanceBetweenSystems() {
        switch (size) {
            default:
                return 8.0;
            case QUICK:
                return 12.0;
            case LONG:
                return 16.0;
        }
    }
}
