(ns fleetcommand.server.entity
  (:use cheshire.core))

(defrecord Entity [id modelid x y rot])

(def battles (atom {}))

(defn add
  [entities id model-id x y rot]
  (let [id-to-use (if (= id "") (str (count @entities)) id)]
    (swap! entities assoc id-to-use (Entity. id-to-use model-id x y rot))))

(defn init-battle
  [battle-id]
  (let [v (atom {})]
    (swap! battles assoc battle-id v)
    v))

(defn get-battle-hash
  [battle-id]
  (let [v (get @battles battle-id)]
    (if (nil? v)
      (init-battle battle-id)
      v)))

(defn build-battle
  [battle-id]
  (init-battle battle-id)
  (let [battle (get-battle-hash battle-id)]
    (dotimes [x 1000]
      (add battle "" "Vyper" (rand 1000.0) (rand 1000.0) 0.0)))
  (str "fleetcommand.webclient.start.init_battle_callback()"))

(defn get-battle
  [battle-id]
  (let [battle (get-battle-hash battle-id)]

    ;; Animate
    (doseq [x @battle]
      (let [k (key x)
            v (val x)
            n (Entity. (:id v) (:modelid v) (:x v) (:y v) (+ (:rot v) 0.5))]
        (swap! battle assoc k n)))

    (str "fleetcommand.webclient.start.get_battle_callback(" 
      (generate-string
        {:entities (vals @battle)}
        {:pretty true }) ")")))