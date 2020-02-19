package straightline

import (
	"math"
	"time"
)

const earthRadiusM float64 = 6367450
const convert2Rad float64 = math.Pi / 180.0
const convert2Deg float64 = 180.0 / math.Pi
const secondsPerMetre float64 = 0.0559234073

func DistanceBetweenPointsLatLong(lat1 float64, lon1 float64, lat2 float64, lon2 float64) float64 {
	dStartLatInRad := lat1 * convert2Rad
	dStartLongInRad := lon1 * convert2Rad
	dEndLatInRad := lat2 * convert2Rad
	dEndLongInRad := lon2 * convert2Rad
	dLongitude := dEndLongInRad - dStartLongInRad
	dLatitude := dEndLatInRad - dStartLatInRad
	dSinHalfLatitude := math.Sin(dLatitude * 0.5)
	dSinHalfLongitude := math.Sin(dLongitude * 0.5)
	a := dSinHalfLatitude*dSinHalfLatitude + math.Cos(dStartLatInRad)*math.Cos(dEndLatInRad)*dSinHalfLongitude*dSinHalfLongitude
	c := math.Atan2(math.Sqrt(a), math.Sqrt(1.0-a))
	return earthRadiusM * (c + c)
}

func DistanceInPeriod(distance float64) time.Duration {
	return time.Duration(distance * secondsPerMetre * 1000.0)
}

func LatitudeDistance(metres float64) float64 {
	return (metres / earthRadiusM) * convert2Deg
}

func LongitudeDistance(metres float64, lat float64) float64 {
	return (metres / (earthRadiusM * math.Cos(lat*convert2Rad))) * convert2Deg
}
