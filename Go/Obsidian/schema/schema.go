package schema

import (
	"time"
)

type Activity struct {
	ID         string
	LocationID string
	Status     []ActivityStatus
}

type ActivityStatus struct {
	Status   int
	Time     time.Time
	Duration time.Duration
}

type Allocation struct {
	ActivityID string
	ResourceID string
	RouteID    string
	Start      time.Time
	End        time.Time
}

type Location struct {
	ID        string
	Latitude  float64
	Longitude float64
}

type Resource struct {
	ID         string
	FirstName  string
	LastName   string
	LocationID string
}

type Route struct {
	ID         string
	ResourceID string
	ShiftID    string
	Start      time.Time
}

type Schedule struct {
	Activity   map[string]Activity
	Allocation map[string]Allocation
	Location   map[string]Location
	Resource   map[string]Resource
}

type Shift struct {
	ID         string
	ResourceID string
	Start      time.Time
	End        time.Time
}

const (
	Status_Unallocated = 0
	Status_Allocated   = 10
)

func NewSchedule() *Schedule {
	return &Schedule{
		Activity:   map[string]Activity{},
		Allocation: map[string]Allocation{},
		Location:   map[string]Location{},
		Resource:   map[string]Resource{},
	}
}

func NewActivity(s *Schedule, id string, time time.Time, duration time.Duration) *Activity {
	as := ActivityStatus{Status: 0, Time: time, Duration: duration}
	a := Activity{
		Status: []ActivityStatus{as},
	}
	if s != nil {
		s.Activity[id] = a
	}
	return &a
}

func NewActivityStatus(a *Activity, status int, time time.Time, duration time.Duration) *ActivityStatus {
	as := ActivityStatus{Status: status, Time: time, Duration: duration}
	if a != nil {
		a.Status = append(a.Status, as)
	}
	return &as
}

func NewAllocation(s *Schedule, aid string, rid string, start time.Time, end time.Time) *Allocation {
	a := Allocation{ActivityID: aid, ResourceID: rid, Start: start, End: end}
	if s != nil {
		s.Allocation[aid] = a
	}
	return &a
}

func NewLocation(s *Schedule, id string, latitude float64, longitude float64) *Location {
	l := Location{ID: id, Latitude: latitude, Longitude: longitude}
	if s != nil {
		s.Location[id] = l
	}
	return &l
}

func NewResource(s *Schedule, id string) *Resource {
	r := Resource{ID: id}
	if s != nil {
		s.Resource[id] = r
	}
	return &r
}

func FindLocationForActivity(s *Schedule, id string) *Location {
	x := s.Location[s.Activity[id].LocationID]
	return &x
}

func FindLocationForResource(s *Schedule, id string) *Location {
	x := s.Location[s.Resource[id].LocationID]
	return &x
}

func AllStatusForActivity(s *Schedule, id string) *[]ActivityStatus {
	x := s.Activity[id].Status
	return &x
}

func FindLatestStatusForActivity(s *Schedule, id string) *ActivityStatus {
	x := *AllStatusForActivity(s, id)
	if len(x) == 0 {
		return nil
	}
	latesttime := time.Unix(0, 0)
	var latest ActivityStatus
	for _, as := range x {
		if as.Time.After(latesttime) {
			latest = as
		}
	}
	return &latest
}
