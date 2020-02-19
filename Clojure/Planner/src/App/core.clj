(ns App.core
  (:gen-class)
  (:use [App datagenerate schema]))

(set! *warn-on-reflection* true)

(defn -main []
  (let [data (generate "NG4 2DG, UK")]
    (println "Done")))
