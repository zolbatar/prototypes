(ns tinker.cave-threed
  (:require [tinker.helper :as h]
            [goog.dom :as dom]
            [goog.graphics :as graphics]))

(def block-size 2)
(def scene (atom (js/THREE.Scene.)))
(def camera (atom nil))
(def renderer (atom nil))

(defn init-renderer
  []
  (let [viewport (dom/getViewportSize)
        width (.-width viewport)    
        height (.-height viewport)]
    (reset! camera (js/THREE.OrthographicCamera. (/ width -2) (/ width 2) (/ height 2) (/ height -2) -2000 1000))
    (set! (.-z (.-position @camera)) 1000)
    (reset! renderer (js/THREE.WebGLRenderer.))
    (.setSize @renderer width height)
    (.appendChild (.-body (dom/getDocument)) (.-domElement @renderer))))

(defn build-cave
  [cave cave-width cave-height]
  (let [geometry (js/THREE.Geometry.)
        material (js/THREE.MeshBasicMaterial. (js-obj "color" 0x404040 "wireframe" false "vertexColors" js/THREE.FaceColors))
        colours [(js/THREE.Color. 0xFFFFFF)
                 (js/THREE.Color. 0xC0C0C0)]
        i (atom 0)
        line (inc cave-width)
        hb (* (/ cave-width 2) block-size)]
    (dotimes [y (inc cave-height)]
      (dotimes [x (inc cave-width)]
        (h/vector3 geometry (- (* x block-size) hb) (- (* y block-size) hb) 0)
    (doseq [row cave]
      (doseq [col row]
        (h/face geometry @i (inc @i) (+ @i line 1) (+ @i line) (nth colours col))
        (swap! i inc))
      (swap! i inc))
    (let [mesh (js/THREE.Mesh. geometry material)]
      (.add @scene mesh)
      (.log js/console mesh))))))

(defn render-cave
  []
;  (.requestAnimationFrame js/window animate)
  (.render @renderer @scene @camera))
