package bz.util;

import java.util.Random;
import bz.schema.*;
import bz.travel.StraightLine;

public class DataGenerate {
    public static Random r = new Random();

    public static Schema generate(int noResources, int noTasks) {
        Schema s = new Schema();
        generateResources(s, noResources);
        generateTasks(s, noTasks);
        return s;
    }
    
    private static void generateResources(Schema s, int noResources) {
        
    }
    
    private static void generateTasks(Schema s, int noTasks) {
        
    }
    
    private static Location generateLocation(Schema s, String id, double centreLatitude, double centreLongitude, double radius) {
        double angle = r.nextDouble() * 2.0 * Math.PI;
        radius = r.nextDouble() * radius;
        double latitude = centreLatitude + StraightLine.latitudeDistance(radius * Math.cos(angle));
        Location l = new Location(
            id, 
            latitude,
            centreLongitude + StraightLine.longitudeDistance(radius * Math.sin(angle), latitude));
    }
    
}
