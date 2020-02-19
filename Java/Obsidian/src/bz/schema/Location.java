package bz.schema;

public class Location {
    private final String id;
    private final double latitude, longitude;
    
    public Location(String ID, double latitude, double longitude) {
        this.id = ID;
        this.latitude = latitude;
        this.longitude = longitude;
    }
    
    public double getLatitude() {
        return latitude;
    }
    
    public double getLongitude() {
        return longitude;
    }
}
