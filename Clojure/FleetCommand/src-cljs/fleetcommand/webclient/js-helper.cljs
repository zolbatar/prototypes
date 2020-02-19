(ns fleetcommand.webclient.js-helper)

(defn get-time
  []
  (.getTime (js/Date.)))
