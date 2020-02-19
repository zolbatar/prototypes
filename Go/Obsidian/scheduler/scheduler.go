package scheduler

import (
	"../schema"
	"./algorithm/greedy"
)

func Schedule(s *schema.Schedule) {
	greedy.Construct(s)
}
