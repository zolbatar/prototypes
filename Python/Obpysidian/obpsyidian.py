#!/usr/bin/python
# -*- coding: utf-8 -*-

import datetime
import generator.schedule
import scheduler.scheduler
import output.svg
import output.textplan

sg = generator.schedule.Schedule()
s = sg.generate(datetime.datetime(2013, 10, 1, 0, 0, 0), 52.954783, -1.158109, 10000.0, 3, 15, 1,
                datetime.timedelta(hours=9), datetime.timedelta(hours=4), "English")
scheduler.scheduler.schedule(s)
# scheduler.scheduler.schedule(s)
output.textplan.output(s)
output.svg.output(s)
