package svgoutput

import (
	"../schema"
	"fmt"
	"io"
	"math"
	"os"
	"strings"
)

func OutputPlanSVG(s *schema.Schedule, latitude float64, longitude float64) {
	X, Y, minLat, minLon := Bounds(s)
	fmt.Printf("%f %f\n", X, Y)

	svg := []string{
		"<?xml version=\"1.0\" standalone=\"no\"?>",
		"<!DOCTYPE svg PUBLIC \"-//W3C//DTD SVG 1.1//EN\" \"http://www.w3.org/Graphics/SVG/1.1/DTD/svg11.dtd\">",
		"<svg xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\">",
	}

	// Create all routes
	for _, r := range s.Allocation {
		l := schema.FindLocationForActivity(s, r.ActivityID)

		x := (l.Longitude - minLon) * X
		y := (l.Latitude - minLat) * Y

		// Draw location
		s := fmt.Sprintf("<circle cx=\"%f\" cy=\"%f\" r=\"5\" stroke=\"black\" stroke-width=\"1\" fill=\"red\" />", x, y)
		svg = append(svg, s)

		//		svg = append(svg, "<polygon points=\"200,10 250,190 160,210\"")
		//		svg = append(svg, "style=\"fill:lime;stroke:purple;stroke-width:1\"/>")
	}
	svg = append(svg, "</svg>")
	writeLines(svg, "Plan.svg")
}

func Bounds(s *schema.Schedule) (float64, float64, float64, float64) {
	minLat := math.Inf(0)
	maxLat := math.Inf(-1)
	minLon := math.Inf(0)
	maxLon := math.Inf(-1)

	// Work out range of points
	for _, r := range s.Allocation {
		l := schema.FindLocationForActivity(s, r.ActivityID)

		minLat = math.Min(minLat, l.Latitude)
		maxLat = math.Max(maxLat, l.Latitude)
		minLon = math.Min(minLon, l.Longitude)
		maxLon = math.Max(maxLon, l.Longitude)
	}
	minLat -= 0.01
	minLon -= 0.01
	maxLat += 0.01
	maxLon += 0.01
	Y := maxLat - minLat
	X := maxLon - minLon

	return 1000.0 / X, 1000.0 / Y, minLat, minLon
}

func writeLines(lines []string, path string) {
	f, err := os.Create(path)
	if err != nil {
		fmt.Println(err)
	}
	content := strings.Join(lines, "\n")
	n, err := io.WriteString(f, content)
	if err != nil {
		fmt.Println(n, err)
	}
	f.Close()
}
