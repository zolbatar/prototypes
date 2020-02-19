#!/usr/bin/python
# -*- coding: utf-8 -*-

import datetime
import schema.schema


def output(s):

    # Loop through all routes
    for r in s.route():
        ro = s.get_route(r)
        print "Resource %s, between %s -> %s:" % (ro.resource_id, ro.start, ro.end)

        # Find all events and put in a dict
        day = {}
        for a in [x for x in s.allocation().values() if x.route_id == ro.id]:
            day[a.start] = "  Call   %5s: %s -> %s" % (a.activity_id, a.start, a.end)
        for a in [x for x in s.travel().values() if x.route_id == ro.id]:
            day[a.start] = "  Travel        %s -> %s" % (a.start, a.end)

        for d in sorted(day):
            print day[d]

        # Find all allocations for this route
#        for a in sorted([x for x in s.allocation().values() if x.route_id == ro.id], key=lambda x: x.start):
#            print "  %s: %s -> %s" % (a.activity_id, a.start, a.end)

#        for a in sorted([x for x in s.travel().values() if x.route_id == ro.id], key=lambda x: x.start):
#            print "  %s: %s -> %s" % (a.activity_id, a.start, a.end)
