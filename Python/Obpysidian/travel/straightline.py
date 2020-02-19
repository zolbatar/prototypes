#!/usr/bin/python
# -*- coding: utf-8 -*-

import datetime
import math

EARTH_RADIUS_M = 6367450.0
CONVERT_2_RAD = math.pi / 180.0
CONVERT_2_DEG = 180.0 / math.pi
SECONDS_PER_METRE = 0.0559234073


def distance_between_points(latitude1, longitude1, latitude2, longitude2):
    start_lat_in_rad = latitude1 * CONVERT_2_RAD
    start_lon_in_rad = longitude1 * CONVERT_2_RAD
    end_lat_in_rad = latitude2 * CONVERT_2_RAD
    end_lon_in_rad = longitude2 * CONVERT_2_RAD
    longitude = end_lon_in_rad - start_lon_in_rad
    latitude = end_lat_in_rad - start_lat_in_rad
    sin_half_latitude = math.sin(latitude * 0.5)
    sin_half_longitude = math.sin(longitude * 0.5)
    a = sin_half_latitude ** 2 + math.cos(start_lat_in_rad) * math.cos(end_lat_in_rad) * sin_half_longitude ** 2
    c = math.atan2(math.sqrt(a), math.sqrt(1.0 - a))
    return EARTH_RADIUS_M * (c + c)


def distance_in_time(distance):
    return datetime.timedelta(seconds=distance * SECONDS_PER_METRE)


def latitude_distance(metres):
    return metres / EARTH_RADIUS_M * CONVERT_2_DEG


def longitude_distance(metres, latitude):
    return metres / (EARTH_RADIUS_M * math.cos(latitude * CONVERT_2_RAD)) * CONVERT_2_DEG
