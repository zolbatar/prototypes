package bz.library;

import java.util.ArrayList;
import java.util.Collection;
import java.util.List;
import javafx.scene.canvas.*;
import javafx.scene.transform.Rotate;

public class Helpers {
    public static double Radians360 = Math.toRadians(360);
    
    public static <T extends Comparable<? super T>> List<T> asSortedList(Collection<T> c) {
        List<T> list = new ArrayList<>(c);
        java.util.Collections.sort(list);
        return list;
    }    

    public static boolean LineIntersectCircle(Point p, double radius, Point p1, Point p2) {
        Profiler.Enter("Helpers::LineIntersectCircle");
        Point lp1 = new Point (p1.GetX() - p.GetX(), p1.GetY() - p.GetY());
        Point lp2 = new Point (p2.GetX() - p.GetX(), p2.GetY() - p.GetY());
        double x2mx1 = lp2.GetX() - lp1.GetX();
        double y2my1 = lp2.GetY() - lp1.GetY();
        double a = (x2mx1 * x2mx1) + (y2my1 * y2my1);
        double b = 2 * ((lp1.GetX() * x2mx1) + (lp1.GetY() * y2my1));
        double c = (lp1.GetX() * lp1.GetX()) + (lp1.GetY() * lp1.GetY()) - (radius * radius);
        double delta = (b * b) - (4 * a * c);
        Profiler.Leave("Helpers::LineIntersectCircle");
        return delta >= 0;
    }

    public static Point PolarToCartesian(double l, double angle) {
        Profiler.Enter("Helpers::PolarToCartesian");
        double x = l * Math.cos(angle);
        double y = l * Math.sin(angle);
        Profiler.Leave("Helpers::PolarToCartesian");
        return new Point(x, y);
    }

    public static double PolarToCartesianX(double l, double angle) {
        Profiler.Enter("Helpers::PolarToCartesianX");
        double x = l * Math.cos(angle);
        Profiler.Leave("Helpers::PolarToCartesianX");
        return x;
    }
    
    public static double PolarToCartesianY(double l, double angle) {
        Profiler.Enter("Helpers::PolarToCartesianY");
        double y = l * Math.sin(angle);
        Profiler.Leave("Helpers::PolarToCartesianY");
        return y;
    }

    public static double DistanceBetweenPoints(double x1, double y1, double x2, double y2) {
        Profiler.Enter("Helpers::DistanceBetweenPoints");
        double deltaY = y1 - y2;
        double deltaX = x2 - x1;
 	double r = Math.sqrt((deltaX * deltaX) + (deltaY * deltaY));
        Profiler.Leave("Helpers::DistanceBetweenPoints");
	return r;
    }

    public static double AngleBetweenPoints(double x1, double y1, double x2, double y2) {
        Profiler.Enter("Helpers::AngleBetweenPoints");
	float deltaY = (float)(y1 - y2);
	float deltaX = (float)(x2 - x1);
	double r = Math.atan2(deltaY, deltaX);
        Profiler.Leave("Helpers::AngleBetweenPoints");
        return r;
    }
    
    public static double AddDegAngle(double a, double add) {
        return Math.toRadians(Math.toDegrees(a) + add);
    }

    public static double RadDegConvert(double a) {
        double d = Math.toDegrees(a);
        return d;
    }
    
    private static final Rotate r = new Rotate();
    public static void SetRotation(GraphicsContext gc, double angle, double px, double py) {
        Profiler.Enter("Helpers::SetRotation");
        r.setAngle(angle);
        r.setPivotX(px);
        r.setPivotY(py);
        gc.setTransform(r.getMxx(), r.getMyx(), r.getMxy(), r.getMyy(), r.getTx(), r.getTy());
        Profiler.Leave("Helpers::SetRotation");
    }

    public static Point RotateAroundOrigin(double x, double y, double angle) {
        Profiler.Enter("Helpers::RotateAroundOrigin");
	double newX = x * Math.cos(angle) - y * Math.sin(angle);
	double newY = x * Math.sin(angle) + y * Math.cos(angle);
        Profiler.Leave("Helpers::RotateAroundOrigin");
        return new Point(newX, newY);
    }

    public static double RotateAroundOriginX(double x, double y, double angle) {
        Profiler.Enter("Helpers::RotateAroundOriginX");
	double newX = x * Math.cos(angle) - y * Math.sin(angle);
        Profiler.Leave("Helpers::RotateAroundOriginX");
        return newX;
    }

    public static double RotateAroundOriginY(double x, double y, double angle) {
        Profiler.Enter("Helpers::RotateAroundOriginY");
	double newY = x * Math.sin(angle) + y * Math.cos(angle);
        Profiler.Leave("Helpers::RotateAroundOriginY");
        return newY;
    }

    public static String PositionToString(double p) {
        return String.format("%.2f", p);
    }

    public static String DistanceToString(double km) {
        if (km < 10 || km < -10) {
            return String.format("%.1f m", km * 1000.0);
        } else {
            return String.format("%.1f km", km);
        }
    }
    
    public static String DistanceToTime(double km, double speed) {
        double t = km / speed;
        if (t > 1000) {
            return "A long time";
        } else {
            return String.format("%.2f seconds", t);
        }
    }
    
    public static double AdjustAngle(double angle) {
        Profiler.Enter("Helpers::AdjustAngle");
        while (angle < 0) {
            angle += Helpers.Radians360;
        }
        while (angle >= Helpers.Radians360) {
            angle -= Helpers.Radians360;
        }
        Profiler.Leave("Helpers::AdjustAngle");
        return angle;
    }

    public static double AdjustAngleDegrees(double angle) {
        Profiler.Enter("Helpers::AdjustAngleDegrees");
        while (angle < 0) {
            angle += 360;
        }
        while (angle >= 360) {
            angle -= 360;
        }
        Profiler.Leave("Helpers::AdjustAngleDegrees");
        return angle;
    }
}

