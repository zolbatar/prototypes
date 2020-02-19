#!/usr/bin/python
# -*- coding: utf-8 -*-

import datetime
import location
import name
import schema.schema


class Schedule:

    def generate(self, date, latitude, longitude, radius, no_resources, no_activities, days, start, duration, language):
        ng = name.NameGenerator(language)
        lg = location.LocationGenerator()
        location_id = 0
        s = schema.schema.Schedule()

        # Resources
        for i in range(no_resources):
            location_ids = 'L%s' % location_id
            id = 'R%s' % (i + 1)
            (lat, lon) = lg.generate(latitude, longitude, radius)
            (first_name, last_name) = ng.generate()[:2]
            self.build_location(s, location_ids, lat, lon)
            self.build_resource(s, id, location_ids, first_name, last_name)
            self.build_shift(s, id, date, days, start, duration)
            location_id += 1

        # Activities
        for i in range(no_activities):
            location_ids = 'L%s' % location_id
            id = 'A%s' % (i + 1)
            (lat, lon) = lg.generate(latitude, longitude, radius)
            self.build_location(s, location_ids, lat, lon)
            self.build_activity(s, id, location_ids)
            location_id += 1

        return s

    def build_location(self, s, id, latitude, longitude):
        l = schema.schema.Location()
        l.id = id
        l.latitude = latitude
        l.longitude = longitude
        s.add_location(l)

    def build_resource(self, s, id, location_id, first_name, last_name):
        r = schema.schema.Resource()
        r.id = id
        r.location_id = location_id
        r.first_name = first_name
        r.last_name = last_name
        s.add_resource(r)

    def build_shift(self, s, resource_id, date, days, start, duration):
        for day in range(days):
            sh = schema.schema.Shift()
            sh.resource_id = resource_id
            sh.start = date + datetime.timedelta(days=day) + start
            sh.end = sh.start + duration
            sh.id = "%s-%s" % (resource_id, sh.start)
            s.add_shift(sh)

    def build_activity(self, s, id, location_id):
        a = schema.schema.Activity()
        a.id = id
        a.location_id = location_id
        s.add_activity(a)
        sa = schema.schema.ActivityStatus()
        sa.id = id
        sa.time = datetime.datetime.now()
        sa.duration = datetime.timedelta(minutes=30)
        s.add_activity_status(sa)
