package bz.library;

public class Point {
    private double X;
    private double Y;
    
    public Point(double x, double y) {
        X = x;
        Y = y;
    }
    
    public Point Clone() {
        return new Point(X, Y);
    }
    
    public double GetX() {
        return X;
    }

    public double GetY() {
        return Y;
    }
    
    public void SetX(double v) {
        X = v;
    }

    public void SetY(double v) {
        Y = v;
    }
}
