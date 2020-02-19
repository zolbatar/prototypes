#!/usr/bin/python
# -*- coding: utf-8 -*-

import math
import random
import travel.straightline


class LocationGenerator:

    def generate(self, centre_latitude, centre_longitude, radius):
        angle = random.random() * 2.0 * math.pi
        radius = random.random() * radius
        latitude = centre_latitude + travel.straightline.latitude_distance(radius * math.cos(angle))
        longitude = centre_longitude + travel.straightline.longitude_distance(radius * math.sin(angle), latitude)
        return (latitude, longitude)
