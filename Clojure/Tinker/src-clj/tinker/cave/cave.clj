(ns tinker.cave.cave
  (:use cheshire.core
        tinker.cave.generate
        tinker.cave.parameters))

(defn get-cave
  [id]
  (let [width 64
        height 64
        cave (create-cave width height)]
    (str "tinker.start.cave_callback(" 
      (generate-string 
        {:cave cave 
         :width (* width cave-enlargen)
         :height (* height cave-enlargen) 
        } 
        {:pretty true }) ")")))   