(ns fleetcommand.webclient.renderer
  (:require [goog.dom :as dom]
            [goog.graphics :as graphics]))

(def width (atom 0))
(def height (atom 0))
(def canvas (atom nil))
(def g (atom nil))

(def edge-stroke (graphics/Stroke. 1 "#111"))
(def back-stroke (graphics/Stroke. 0 "#FFF"))
(def back-fill (graphics/Fill. 1 "#111"))

(defn get-size
  []
  (reset! canvas (dom/getElement "container"))
  (reset! width (.-clientWidth @canvas))
  (reset! height (.-clientHeight @canvas)))

(defn init
  []
  (.log js/console "Initialising canvas...")
  (reset! g
    (doto (graphics/createGraphics "100%" "100%")
      (.render (dom/getElement "container"))))
  (get-size)
  (.log js/console (str "Width: " @width))
  (.log js/console (str "Height: " @height)))

(defn clear
  []
  (.clear @g))
;;  (.fillRect @g 0 0 @width @height back-stroke back-fill))

(defn render-points
  [points x y rot]
  (let [path (graphics/Path.)
        t (graphics/AffineTransform.)
        f (first points)]
    (.moveTo path (first f) (second f))
    (doseq [p (rest points)]
      (.lineTo path (first p) (second p)))

    ; Close path
    (.close path)

    ; Transform
    (.translate t x y)
    (.rotate t rot 0 0)
    (.transform path t)

    ; Draw
    (.drawPath @g path edge-stroke)))
