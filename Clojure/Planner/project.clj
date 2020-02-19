(defproject Planner "0.0.1-SNAPSHOT"
  :description "Planner: Scheduling Engine"
  :dependencies [[org.clojure/clojure "1.4.0"]
                 [geocoder-clj "0.0.6-SNAPSHOT"]]
  :geocoder-config
    {:bing {:key "AtdVCBmBxcm8r5ZcVLR9sdAejsYPMH_zzqXLVKZNFdI5IiD5HRxyXpMI2YEhdqpL"}
     :geonames {:key "GEONAMES-API-KEY"}
      :yahoo {:key "YAHOO-API-KEY"}}
  :main App.core)
