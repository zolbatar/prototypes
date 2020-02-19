(ns App.geocoder
  (:require [geocoder.core :as geo]))

(use 'geocoder.core)

(defn geocode [location]
  (println location)  
  (let [l (geocode-address "Senefelderstraße 24, 10437 Berlin")]
    (println (:location l))))