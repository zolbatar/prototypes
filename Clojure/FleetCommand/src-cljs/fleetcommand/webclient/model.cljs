(ns fleetcommand.webclient.model
  (:require [fleetcommand.webclient.renderer :as renderer]))

(deftype Section [id points])
(deftype Model [sections])

(def models (atom {}))

(defn ^:export get-all-models-callback 
  [reply]
  (doseq [model (.-models reply)]
    (let [id (.-id model)
          geos (.-geo model)
          sections (doall (map #(Section. (.-id %) (.-points %)) geos))]
      (swap! models assoc id (Model. sections))))
  (fleetcommand.webclient.start/init-battle))

(defn get-all-models
  []
  (let [jsonp (goog.net.Jsonp. (str "/models"))]
    (.send jsonp nil nil nil)))

(defn render
  [id x y rot]
  (let [model (get @models id)]
    (doseq [section (.-sections model)]
      (renderer/render-points (.-points section) x y rot))))
