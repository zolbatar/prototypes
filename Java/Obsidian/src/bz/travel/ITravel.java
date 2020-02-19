package bz.travel;

import java.time.Duration;
import bz.schema.Location;

public interface ITravel {

    public double distanceBetweenPoints(Location location1, Location location2);
    public Duration distanceInTime(double distanceInMetres);

}
