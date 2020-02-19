(ns fleetcommand.webclient.entity
  (:require [fleetcommand.webclient.model :as model]
            [fleetcommand.webclient.renderer :as renderer]
            [fleetcommand.webclient.js-helper :as js-helper]))

(def entities (atom nil))

(defn clear
  []
  (reset! entities {}))

(defn render
  [entity]
  (model/render (.-modelid entity) (.-x entity) (.-y entity) (.-rot entity)))

(defn render-all
  [entities-in]
  (renderer/clear)
  (reset! entities entities-in)
  (let [time (js-helper/get-time)]
    (dotimes [x (count entities-in)]
      (let [entity (nth entities-in x)]
        (render entity)))
    (.log js/console (str "Rendering took " (- (js-helper/get-time) time) "ms"))))
