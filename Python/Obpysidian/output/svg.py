#!/usr/bin/python
# -*- coding: utf-8 -*-

import sys


def output(s):
    xscale, yscale, min_lat, min_lon = bounds(s)

    colours = ["crimson", "lightgreen", "brown", "blue", "orange", "purple"]

    svg = ["<?xml version=\"1.0\" standalone=\"no\"?>",
           "<!DOCTYPE svg PUBLIC \"-//W3C//DTD SVG 1.1//EN\" \"http://www.w3.org / Graphics / SVG / 1.1 / DTD / svg11.dtd\" >\n",
           "<svg xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\">\n"]

    # Create all routes
    i = 0
    for r in s.route():
        poly = ["<polyline points =\""]
        ro = s.get_route(r)
        reso = s.get_resource(ro.resource_id)
        lr = s.get_location(reso.location_id)
        x_p = (lr.longitude - min_lon) * xscale
        y_p = (lr.latitude - min_lat) * yscale
        poly.append("%s,%s " % (x_p, y_p))
        for k in [x for x in s.allocation().values() if x.route_id == ro.id]:
            a = s.get_activity(k.activity_id)
            l = s.get_location(a.location_id)
            x_p = (l.longitude - min_lon) * xscale
            y_p = (l.latitude - min_lat) * yscale
            poly.append("%s,%s " % (x_p, y_p))

            # Draw location
            svg.append("<circle cx=\"%f\" cy=\"%f\" r=\"5\" stroke=\"black\" stroke-width=\"1\" fill=\"blue\" />\n" % (x_p, y_p))

        # Go home
        x_p = (lr.longitude - min_lon) * xscale
        y_p = (lr.latitude - min_lat) * yscale
        poly.append("%s,%s " % (x_p, y_p))
        poly.append("\" style=\"fill:none;stroke:" + colours[i] + ";stroke-width:2\" />\n")
        svg += poly
        i += 1

    # Show resources
    for r in s.resource():
        ro = s.get_resource(r)
        l = s.get_location(ro.location_id)
        x_p = (l.longitude - min_lon) * xscale
        y_p = (l.latitude - min_lat) * yscale
        svg.append("<circle cx=\"%f\" cy=\"%f\" r=\"5\" stroke=\"black\" stroke-width=\"1\" fill=\"pink\" />\n" % (x_p, y_p))

    svg.append("</svg>")

    with open("Plan.svg", "w") as tf:
        tf.write("".join(svg))


def bounds(s):
    min_lat = sys.float_info.max
    max_lat = sys.float_info.min
    min_lon = sys.float_info.max
    max_lon = sys.float_info.min

    # Work out range of points
    for k in s.allocation():
        ao = s.get_allocation(k)
        a = s.get_activity(ao.activity_id)
        l = s.get_location(a.location_id)

        min_lat = min(min_lat, l.latitude)
        max_lat = max(max_lat, l.latitude)
        min_lon = min(min_lon, l.longitude)
        max_lon = max(max_lon, l.longitude)

    for k in s.resource():
        ro = s.get_resource(k)
        l = s.get_location(ro.location_id)

        min_lat = min(min_lat, l.latitude)
        max_lat = max(max_lat, l.latitude)
        min_lon = min(min_lon, l.longitude)
        max_lon = max(max_lon, l.longitude)

    min_lat -= 0.01
    max_lat += 0.01
    min_lon -= 0.025
    max_lon += 0.025
    y = max_lat - min_lat
    x = max_lon - min_lon
    return 500.0 / x * 5.0, 500.0 / y, min_lat, min_lon
