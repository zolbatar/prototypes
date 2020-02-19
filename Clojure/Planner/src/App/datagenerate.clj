(ns App.datagenerate
  (:use [App geocoder schema]))

(defn generate [start-location]
  (geocode start-location)
  (new-schedule))