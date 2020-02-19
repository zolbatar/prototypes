package bz.game.render;

import java.util.*;
import java.util.concurrent.ConcurrentHashMap;
import javafx.scene.canvas.Canvas;
import javafx.scene.canvas.GraphicsContext;
import bz.panels.subpanels.FXMLMapController;
import bz.Parameters;
import bz.TCS;
import bz.library.Point;
import bz.library.Profiler;
import bz.game.Game;
import bz.game.universe.*;
import bz.library.Helpers;
import bz.spaceobjects.*;

public class RenderMap {
    private final FXMLMapController controller;
    private double width, height, scale, size, sizeX, sizeY;
    private static final ConcurrentHashMap<Integer, HoverSystem> hovers = new ConcurrentHashMap<>(Parameters.CHASHMAP_INITIALCAPACITY, Parameters.CHASHMAP_LOADFACTOR, Parameters.CHASHMAP_CONCURRENCY);
    
    public RenderMap(FXMLMapController controller) {
        this.controller = controller;
    }
    
    public void Render() {
        if (controller.CheckCanvas()) {
            
            // Get game
            Game game = TCS.GetGame();
            
            // Setup canvas
            Canvas canvas = controller.GetCanvas();
            GraphicsContext gc = canvas.getGraphicsContext2D();
            
            // Setup and clear
            width = canvas.getWidth();
            height = canvas.getHeight();
            gc.clearRect(0.0, 0.0, width, height);
            
            // Size
            size = game.GetUniverse().GetUniverseSize();
            sizeX = size / Parameters.UNIVERSE_SECTIONS_X;
            sizeY = size / Parameters.UNIVERSE_SECTIONS_Y;
            double w = (width - Parameters.RENDER_PADDING) / size;
            double h = (height - Parameters.RENDER_PADDING) / size;
            scale = Math.min(w, h);

            // Grid
            RenderGrid(gc);
            
            // Match mouse position with objects
            Point mouse = controller.GetMousePosition();
            if (mouse != null) {
                List<SolarSystem> systems = TCS.GetGame().GetUniverse().GetSystems();
                for (SolarSystem s : systems) {
                    Point p = s.GetTranslatedPosition();
                    double dist = Helpers.DistanceBetweenPoints(p.GetX(), p.GetY(), mouse.GetX(), mouse.GetY());
                    if (dist <= Parameters.RENDER_SUN_SIZE) {
                        TCS.GetRenderMap().HoverSystem(s);
                    }
                }
            }
            
            // Update hovers
            double time = TCS.GetTime();
            for (HoverSystem hs : hovers.values()) {
                double duration = time - hs.lastTime;
                if (duration > 5.0) {
                    hovers.remove(hs.s.GetID());
                }
            }
            
            // Render systems
            for (SolarSystem s: game.GetUniverse().GetSystems()) {
                Point p =  s.GetPosition();
                Point pt = s.GetTranslatedPosition();
                Point t = TranslateXYUniverse(p);
                pt.SetX(t.GetX());
                pt.SetY(t.GetY());
                double r = Parameters.RENDER_SUN_SIZE;
                gc.drawImage(s.GetSun().GetImage(), t.GetX() - (r / 2), t.GetY() - (r / 2), r, r);
                r = Parameters.RENDER_SUN_INNER;
                gc.setLineWidth(Parameters.RENDER_SUN_BORDER);
                gc.setStroke(s.GetSun().GetAverage());
                gc.strokeOval(t.GetX() - (r / 2), t.GetY() - (r / 2), r, r);
                
                // Slide out into?
                if (hovers.containsKey(s.GetID())) {
                    int i = 0;
                    for (PlanetType pl : s.GetPlanets()) {
                        double a = Parameters.RENDER_PLANET_SPACING * i + Parameters.RENDER_PLANET_INITIALSPACE;
                        r = Parameters.RENDER_PLANET_SIZE;
                        gc.drawImage(pl.GetImage(), t.GetX() - (r / 2) + a, t.GetY() - (r / 2), r, r);
                        r = Parameters.RENDER_PLANET_INNER;
                        gc.setLineWidth(Parameters.RENDER_PLANET_BORDER);
                        gc.setStroke(pl.GetAverage());
                        gc.strokeOval(t.GetX() - (r / 2) + a, t.GetY() - (r / 2), r, r);
                        i++;
                    }
                }
            }
        }
    }

    private void RenderGrid(GraphicsContext gc) {
        Profiler.Enter("UniverseRender::RenderGrid");

        // Colour
        gc.setLineWidth(0.75);
        gc.setStroke(TCS.GetAssets().ColourBlue100_50);
        
        // Horizontal gridlines
        for (int x = 0; x <= Parameters.UNIVERSE_SECTIONS_X; x++) {
            double posX = (x - (Parameters.UNIVERSE_SECTIONS_X / 2)) * sizeX;
            Point t = TranslateXYUniverse(posX, -size / 2);
            Point b = TranslateXYUniverse(posX, size / 2);
            gc.strokeLine(t.GetX(), t.GetY(), b.GetX(), b.GetY());
        }

        // Vertical gridlines
        for (int y = 0; y <= Parameters.UNIVERSE_SECTIONS_Y; y++) {
            double posY = (y - (Parameters.UNIVERSE_SECTIONS_Y / 2)) * sizeY;
            Point t = TranslateXYUniverse(-size / 2, posY);
            Point b = TranslateXYUniverse(size / 2, posY);
            gc.strokeLine(t.GetX(), t.GetY(), b.GetX(), b.GetY());
        }

        Profiler.Leave("UniverseRender::RenderGrid");
    }

    public Point TranslateXYUniverse(double x, double y) {
        Profiler.Enter("UniverseRender::TranslateXYUniverse");
        Point pOut = new Point(x * scale + (width / 2), y * scale + (height / 2));
        Profiler.Leave("UniverseRender::TranslateXYUniverse");
        return pOut;
    }          

    public Point TranslateXYUniverse(Point p) {
        Profiler.Enter("UniverseRender::TranslateXYUniverse");
        Point pOut = new Point(p.GetX() * scale + (width / 2), p.GetY() * scale + (height / 2));
        Profiler.Leave("UniverseRender::TranslateXYUniverse");
        return pOut;
    }         
    
    public void HoverSystem(SolarSystem s) {
        if (!hovers.containsKey(s.GetID())) {
            HoverSystem hs = new HoverSystem(s);
            hovers.put(s.GetID(), hs);
        } else {
            HoverSystem hs = hovers.get(s.GetID());
            hs.lastTime = TCS.GetTime();
        }
    }
    
    private class HoverSystem {
        public SolarSystem s;
        double time;
        double lastTime;
        
        public HoverSystem(SolarSystem s) {
            this.s = s;
            this.time = TCS.GetTime();
        }
    }
}
