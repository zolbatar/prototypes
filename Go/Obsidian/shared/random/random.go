package random

import (
	"math/rand"
	"time"
)

func GetRandom() *rand.Rand {
	return rand.New(rand.NewSource(time.Now().UnixNano()))
}
