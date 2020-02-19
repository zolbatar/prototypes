package bz.helpers;

public class Maths {

    public static double PolarToCartesianX(double l, double angle) {
        return l * Math.cos(angle);
    }
    
    public static double PolarToCartesianY(double l, double angle) {
        return l * Math.sin(angle);
    }

    public static double DistanceBetweenPoints(double x1, double y1, double x2, double y2) {
        double deltaY = y1 - y2;
        double deltaX = x2 - x1;
 	return Math.sqrt((deltaX * deltaX) + (deltaY * deltaY));
    }

    public static double AngleBetweenPoints(double x1, double y1, double x2, double y2) {
	float deltaY = (float)(y1 - y2);
	float deltaX = (float)(x2 - x1);
	return Math.atan2(deltaY, deltaX);
    }    

}
