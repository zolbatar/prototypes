package locationgenerator

import (
	"../../travel"
	"math"
	"math/rand"
)

func Generate(r *rand.Rand, centreLat float64, centreLon float64, radius float64) (float64, float64) {
	angle := r.Float64() * 2.0 * math.Pi
	rad := r.Float64() * radius
	lat := centreLat + straightline.LatitudeDistance(rad*math.Cos(angle))
	lon := centreLon + straightline.LongitudeDistance(rad*math.Sin(angle), lat)
	return lat, lon
}
