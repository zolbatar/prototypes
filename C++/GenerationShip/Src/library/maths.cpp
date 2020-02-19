#include "maths.h"

double DistanceBetweenPoints(double x1, double y1, double x2, double y2)
{
    double deltaY = y1 - y2;
    double deltaX = x2 - x1;
    return std::sqrt((deltaX * deltaX) + (deltaY * deltaY));
}