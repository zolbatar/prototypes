package generator

import (
	"../schema"
	"../shared/random"
	"./location"
	"./name"
	"fmt"
	"time"
)

func GenerateSchedule(latitude float64, longitude float64, radius float64, noResources int, noActivities int, language string) *schema.Schedule {
	s := schema.NewSchedule()
	r := random.GetRandom()
	ng := namegenerator.New(language, r)
	lid := 0
	dt := time.Now()

	// Resources
	for i := 0; i < noResources; i++ {
		lids := fmt.Sprintf("L%d", lid)
		id := fmt.Sprintf("R%d", i)

		// Location
		lat, lon := locationgenerator.Generate(r, latitude, longitude, radius)
		schema.NewLocation(s, lids, lat, lon)

		// Resource
		nng, first, last, _ := namegenerator.Generate(ng)
		ng = nng
		r := *schema.NewResource(nil, id)
		r.FirstName = first
		r.LastName = last
		r.LocationID = lids
		s.Resource[id] = r
		lid++
	}

	// Activities
	for i := 0; i < noActivities; i++ {
		lids := fmt.Sprintf("L%d", lid)
		id := fmt.Sprintf("A%d", i)

		// Location
		lat, lon := locationgenerator.Generate(r, latitude, longitude, radius)
		schema.NewLocation(s, lids, lat, lon)

		// Activity
		a := *schema.NewActivity(nil, id, dt, time.Duration(30*time.Minute))
		a.LocationID = lids
		s.Activity[id] = a
		lid++
	}
	return s
}
