(ns fleetcommand.server.models.ships.vyper
  (:use cheshire.core))

(defn create
  []
  (list { :id "hull"
          :points (list (list 0.0 -5.0) (list -2.5 5.0) (list 2.5 5.0))
        }))
