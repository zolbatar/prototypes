(ns App.schema)

(defrecord Activity [id-location ^double value])
(defrecord Location [^double lat ^double lon])
(defrecord Resource [id-location ^double cost-ph ^double cost-ph-ot ^double cost-km])

(defn new-schedule []
  { :activity {} :location {} :resource {} })
