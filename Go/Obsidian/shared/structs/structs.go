package structs

import (
	"time"
)

type Location struct {
	Latitude  float64
	Longitude float64
}

type IDLocation struct {
	ID        string
	Latitude  float64
	Longitude float64
}

type ResourceState struct {
	ID        string
	Time      time.Time
	Latitude  float64
	Longitude float64
}
