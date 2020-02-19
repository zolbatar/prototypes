package bz.travel;

import bz.schema.Location;
import java.time.Duration;

public class StraightLine implements ITravel {

    private final static double EARTH_RADIUS = 6367450;
    private final static double SECONDS_PER_METRE = 0.0559234073 / 1000.0;

    @Override
    public double distanceBetweenPoints(Location location1, Location location2) {
        double startLatInRad = Math.toRadians(location1.getLatitude());
        double startLongInRad = Math.toRadians(location1.getLongitude());
        double endLatInRad = Math.toRadians(location2.getLatitude());
        double endLongInRad = Math.toRadians(location2.getLongitude());
        double longitude = endLongInRad - startLongInRad;
        double latitude = endLatInRad - startLatInRad;
        double sinHalfLatitude = Math.sin(latitude * 0.5);
        double sinHalfLongitude = Math.sin(longitude * 0.5);
        double a = sinHalfLatitude * sinHalfLatitude + Math.cos(startLatInRad) * Math.cos(endLatInRad) * sinHalfLongitude * sinHalfLongitude;
        double c = Math.atan2(Math.sqrt(a), Math.sqrt(1.0 - a));
        return EARTH_RADIUS * (c + c);
    }

    @Override
    public Duration distanceInTime(double distanceInMetres) {
        return Duration.ofMillis((long)(distanceInMetres * SECONDS_PER_METRE));
    }

    public static double latitudeDistance(double metres) {
        return Math.toDegrees(metres / EARTH_RADIUS);
    }

    public static double longitudeDistance(double metres, double latitude) {
        return Math.toDegrees(metres / (EARTH_RADIUS * Math.cos(Math.toRadians(latitude))));
    }

}
