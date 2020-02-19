#!/usr/bin/python
# -*- coding: utf-8 -*-

import datetime


class Activity:

    def __init__(self):
        self.id = ""
        self.location_id = ""
        self.pk_activity_status = []


class ActivityStatus:

    def __init__(self):
        self.id = ""
        self.status = 0
        self.time = datetime.datetime.now()
        self.duration = datetime.timedelta.min


class Allocation:

    def __init__(self):
        self.activity_id = ""
        self.resource_id = ""
        self.start = datetime.datetime.min
        self.end = datetime.datetime.min
        self.route_id = ""


class Location:

    def __init__(self):
        self.id = ""
        self.lat = 0.0
        self.lon = 0.0


class Resource:

    def __init__(self):
        self.id = ""


class Route:

    def __init__(self):
        self.id = ""
        self.shift_id = ""
        self.resource_id = ""
        self.start = datetime.datetime.min
        self.end = datetime.datetime.min


class Shift:

    def __init__(self):
        self.id = ""
        self.resource_id = ""
        self.start = datetime.datetime.min
        self.end = datetime.datetime.min


class Travel:

    def __init__(self):
        self.activity_id = ""
        self.resource_id = ""
        self.start = datetime.datetime.min
        self.end = datetime.datetime.min
        self.distance = 0.0
        self.duration = datetime.timedelta.min
        self.route_id = ""


class Schedule:

    def __init__(self):
        self.__activity = {}
        self.__activity_status = {}
        self.__allocation = {}
        self.__location = {}
        self.__resource = {}
        self.__route = {}
        self.__shift = {}
        self.__travel = {}

    # Get collections
    def activity(self):
        return self.__activity

    def allocation(self):
        return self.__allocation

    def location(self):
        return self.__location

    def resource(self):
        return self.__resource

    def route(self):
        return self.__route

    def shift(self):
        return self.__shift

    def travel(self):
        return self.__travel

    # Get methods

    def get_activity(self, id):
        return self.__activity.get((id))

    def get_allocation(self, id):
        return self.__allocation.get((id))

    def get_location(self, id):
        return self.__location.get((id))

    def get_resource(self, id):
        return self.__resource.get((id))

    def get_route(self, id):
        return self.__route.get((id))

    def get_shift(self, id):
        return self.__shift.get((id))

    # Add methods

    def add_activity(self, e):
        self.__activity[(e.id)] = e

    def add_activity_status(self, e):
        pk = (e.id, e.time)
        self.__activity_status[pk] = e
        self.__activity[e.id].pk_activity_status.append(pk)

    def add_allocation(self, e):
        self.__allocation[(e.activity_id, e.start)] = e

    def add_location(self, e):
        self.__location[(e.id)] = e

    def add_resource(self, e):
        self.__resource[(e.id)] = e

    def add_route(self, e):
        self.__route[(e.resource_id, e.start)] = e

    def add_shift(self, e):
        self.__shift[(e.id)] = e

    def add_travel(self, e):
        self.__travel[(e.resource_id, e.start)] = e

    # Helper methods

    def get_activity_status_latest(self, id):
        a = [self.__activity_status[i] for i in self.get_activity(id).pk_activity_status]
        if len(a) == 0:
            return None
        else:
            b = sorted(a, key=lambda x: x.time, reverse=True)
            return b[0]
