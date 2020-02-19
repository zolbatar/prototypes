package greedy

import (
	"../../../schema"
	"../../../shared/structs"
	"../../../travel"
	"fmt"
	"math"
	"time"
)

func Construct(s *schema.Schedule) int {
	dt := time.Now()
	allocations := 0

	// Build an array of positions of all resources
	rpos := []structs.ResourceState{}
	for rid, _ := range s.Resource {
		l := *schema.FindLocationForResource(s, rid)
		rpos = append(rpos, structs.ResourceState{Time: time.Date(2013, 10, 1, 9, 0, 0, 0, time.Local), Latitude: l.Latitude, Longitude: l.Longitude})
	}

	// Loop through each activity in turn, find the nearest resource and add to their route.
	for aid, a := range s.Activity {

		// Already scheduled?
		ls := schema.FindLatestStatusForActivity(s, aid)
		if ls.Status == 0 {
			al := *schema.FindLocationForActivity(s, aid)

			// Loop through all resources
			lowest := math.Inf(0)
			lowestidx := 0
			var lowestr structs.ResourceState
			for idx, r := range rpos {

				// Calculate distance
				d := straightline.DistanceBetweenPointsLatLong(al.Latitude, al.Longitude, r.Latitude, r.Longitude)

				// Nearer?
				if d < lowest {
					lowest = d
					lowestr = r
					lowestidx = idx
				}
			}

			// Update status
			schema.NewActivityStatus(&a, 10, dt, ls.Duration)

			// Add allocation
			end := lowestr.Time.Add(ls.Duration)
			schema.NewAllocation(s, aid, lowestr.ID, lowestr.Time, end)

			// Move time forward on resource
			lowestr.Time = end
			rpos[lowestidx] = lowestr

			// Save
			s.Activity[aid] = a

			allocations++
		}
	}

	fmt.Printf("%d activities allocated\n", allocations)
	return allocations
}
