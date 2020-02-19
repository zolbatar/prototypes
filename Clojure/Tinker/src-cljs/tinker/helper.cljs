(ns tinker.helper)

(defn vector3 
  [geometry x y z]
  (.push (.-vertices geometry) (js/THREE.Vector3. x y z)))

(defn face 
  [geometry f1 f2 f3 f4 colour] 
  (let [face (js/THREE.Face4. f1 f2 f3 f4)]
    (set! (.-color face) colour)
    (.push (.-faces geometry) face)))
