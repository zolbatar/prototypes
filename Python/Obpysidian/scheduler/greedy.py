#!/usr/bin/python
# -*- coding: utf-8 -*-

import datetime
import sys
import schema.schema
import travel.straightline


class SchedulingBlock:

    def __init__(self):
        self.resource_id = ""
        self.route_id = ""
        self.start = datetime.datetime.min
        self.end = datetime.datetime.min
        self.latitude = 0.0
        self.longitude = 0.0


class Greedy:

    def schedule(self, s):
        allocations = 0

        # Build an array of possible blocks
        blocks = []
        for sh in s.shift():
            sho = s.get_shift(sh)
            ro = s.get_resource(sho.resource_id)
            l = s.get_location(ro.location_id)

            # Do we have a route? If not, build one
            rte = s.get_route(sh)
            if rte == None:
                rte = schema.schema.Route()
                rte.id = sh
                rte.resource_id = sho.resource_id
                rte.start = sho.start
                rte.end = sho.end
                rte.shift_id = sh
                s.add_route(rte)
            sb = SchedulingBlock()
            sb.resource_id = ro.id
            sb.start = sho.start
            sb.end = sho.end
            sb.latitude = l.latitude
            sb.longitude = l.longitude
            sb.route_id = sho.id
            blocks.append(sb)

        # Loop through each block in turn, finding each closest activity in turn and scheduling, once block is full, move to next
        for sb in blocks:

            scheduled = True
            while scheduled:
                lowest_distance = sys.float_info.max
                lowest_duration = datetime.timedelta.min
                lowest = None
                for a in s.activity():

                    # Already scheduled?
                    ls = s.get_activity_status_latest(a)
                    if ls == None or ls.status == 10:
                        continue
                    ao = s.get_activity(a)
                    al = s.get_location(ao.location_id)

                    # Calculate distance
                    distance = travel.straightline.distance_between_points(al.latitude, al.longitude, sb.latitude, sb.longitude)
                    duration = travel.straightline.distance_in_time(distance)

                    # Will it fit in the block?
                    remaining = sb.end - sb.start
                    if (ls.duration + duration) > remaining:
                        continue

                    # Nearer?
                    if distance < lowest_distance:
                        lowest_distance = distance
                        lowest_duration = duration
                        lowest = ao

                # Scheduled?
                if lowest != None:

                    start = sb.start + lowest_duration
                    end = start + ls.duration
                    aid = lowest.id
                    rid = sb.resource_id

                    # Update status
                    self.update_status(s, aid, sb.resource_id, 10, datetime.datetime.now(), ls.duration)

                    # Add travel
                    self.add_travel(s, aid, rid, start, start + lowest_duration,
                                    lowest_duration, lowest_distance, sb.route_id)
                    start += duration
                    end += duration

                    # Add allocation
                    self.add_allocation(s, aid, rid, start, end, sb.route_id)

                    # Move time forward on resource
                    sb.start = end

                    # Change location of block
                    sb.latitude = al.latitude
                    sb.longitude = al.longitude
                    allocations += 1
                else:
                    scheduled = False

        print "%d activities allocated" % allocations
        return allocations

    def update_status(self, s, id, resource_id, status, dt, duration):
        sa = schema.schema.ActivityStatus()
        sa.id = id
        sa.resource_id = resource_id
        sa.status = status
        sa.time = dt
        sa.duration = duration
        s.add_activity_status(sa)

    def add_allocation(self, s, activity_id, resource_id, start, end, route_id):
        a = schema.schema.Allocation()
        a.activity_id = activity_id
        a.resource_id = resource_id
        a.start = start
        a.end = end
        a.route_id = route_id
        s.add_allocation(a)

    def add_travel(self, s, activity_id, resource_id, start, end, duration, distance, route_id):
        t = schema.schema.Travel()
        t.activity_id = activity_id
        t.resource_id = resource_id
        t.start = start
        t.end = end
        t.duration = duration
        t.distance = distance
        t.route_id = route_id
        s.add_travel(t)


    # def schedule(self, s):
    #     dt = datetime.datetime.now()
    #     allocations = 0

    # Build an array of possible blocks
    #     blocks = []
    #     for sh in s.shift():
    #         sho = s.get_shift(sh)
    #         ro = s.get_resource(sho.resource_id)
    #         l = s.get_location(ro.location_id)

    # Do we have a route? If not, build one
    #         rte = s.get_route(sh)
    #         if rte == None:
    #             rte = schema.schema.Route()
    #             rte.id = sh
    #             rte.resource_id = sho.resource_id
    #             rte.start = sho.start
    #             rte.end = sho.end
    #             rte.shift_id = sh
    #             s.add_route(rte)
    #         sb = SchedulingBlock()
    #         sb.resource_id = ro.id
    #         sb.start = sho.start
    #         sb.end = sho.end
    #         sb.latitude = l.latitude
    #         sb.longitude = l.longitude
    #         sb.route_id = sho.id
    #         blocks.append(sb)

    # Loop through each activity in turn, find the nearest resource and add to their route.
    #     for a in s.activity():

    # Already scheduled?
    #         ls = s.get_activity_status_latest(a)
    #         if ls == None:
    #             continue
    #         if ls.status == 0:
    #             ao = s.get_activity(a)
    #             al = s.get_location(ao.location_id)

    # Loop through all blocks
    #             lowest_distance = sys.float_info.max
    #             lowest_duration = datetime.timedelta.min
    #             lowest = None
    #             for sb in blocks:

    # Calculate distance
    #                 distance = travel.straightline.distance_between_points(al.latitude, al.longitude, sb.latitude, sb.longitude)
    #                 duration = travel.straightline.distance_in_time(distance)

    # Will it fit in the block?
    #                 remaining = sb.end - sb.start
    #                 if (ls.duration + duration) > remaining:
    #                     continue

    # Nearer?
    #                 if distance < lowest_distance:
    #                     lowest_distance = distance
    #                     lowest_duration = duration
    #                     lowest = sb

    # Scheduled?
    #             if lowest != None:

    #                 start = lowest.start
    #                 end = start + ls.duration
    #                 rid = lowest.resource_id

    # Update status
    #                 self.update_status(s, a, 10, dt, ls.duration)

    # Add travel
    #                 self.add_travel(s, a, rid, start, start + lowest_duration, lowest_duration, lowest_distance, lowest.route_id)
    #                 start += duration
    #                 end += duration

    # Add allocation
    #                 self.add_allocation(s, a, rid, start, end, lowest.route_id)

    # Move time forward on resource
    #                 lowest.start = end

    # Change location of block
    #                 lowest.latitude = al.latitude
    #                 lowest.longitude = al.longitude
    #                 allocations += 1

    #     print "%d activities allocated" % allocations
    #     return allocations
