(ns fleetcommand.server.models.model
  (:use cheshire.core)
  (:require [fleetcommand.server.models.ships vyper]))

(defn get-models
  []
  (str "fleetcommand.webclient.model.get_all_models_callback(" 
    (generate-string 
      {:models
        (list
          {:id "Vyper" :geo (fleetcommand.server.models.ships.vyper/create)})}
      {:pretty true }) ")"))