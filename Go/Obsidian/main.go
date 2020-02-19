package main

import (
	"./generator"
	"./scheduler"
	"./svgoutput"
)

func main() {
	s := generator.GenerateSchedule(52.954783, -1.158109, 10000.0, 5, 50, "English")
	scheduler.Schedule(s)
	scheduler.Schedule(s)
	svgoutput.OutputPlanSVG(s, 52.954783, -1.158109)
}
