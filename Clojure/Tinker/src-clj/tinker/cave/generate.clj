(ns tinker.cave.generate
  (:use tinker.cave.parameters)
  (:import java.util.Random))

(defn- randomise-cave
  [cave random width height]
  (dotimes [row (- height 2)]
    (dotimes [col (- width 2)]
      (let [val (if (> (. random nextInt 100) cave-fill-factor) 1 0)]
        (aset cave (inc row) (inc col) val)))))

(defn cave-solid-borders
  [cave width height]
    (dotimes [col width]
      (aset cave 0 col 1)
      (aset cave (dec height) col 1))
    (dotimes [row (- height 1)]
      (aset cave (inc row) 0 1)
      (aset cave (inc row) (dec width) 1)))

(defn smooth-cave
  [cave random width height probability]
  (dotimes [row (- height 2)]
    (dotimes [col (- width 2)]
      (when (< (. random nextInt 100) probability)
        (let [c1 (aget cave row col)
              c2 (aget cave row (+ col 1))
              c3 (aget cave row (+ col 2))
              c4 (aget cave (+ row 1) col)
              c6 (aget cave (+ row 1) (+ col 2))
              c7 (aget cave (+ row 2) col)
              c8 (aget cave (+ row 2) (+ col 1))
              c9 (aget cave (+ row 2) (+ col 2))
              c (+ c1 c2 c3 c4 c6 c7 c8 c9)]
        (when (< c 4)
          (aset cave (inc row) (inc col) 0))
        (when (> c 5)
          (aset cave (inc row) (inc col) 1)))))))

(defn create-cave-shaft
  [cave random width height]
  (let [col (+ (. random nextInt (- width cave-shafts-padding)) (/ cave-shafts-padding 2))]
    (dotimes [row (+ (/ height 2) (. random nextInt (/ (- height 2) 2)))]
      (aset cave row col 0)
          
      ; Do we want a offshoot shaft?
      (when (> row cave-offshoot-start)
        (when (> (. random nextInt 100) cave-offshoot-factor)
          (let [horiz (- (. random nextInt 3) 1)
                vert (- (. random nextInt 3) 1)]
            (dotimes [size (. random nextInt cave-offshoot-size)]
              (let [off-row (+ row (* vert size))
                    off-col (+ col (* horiz size))]
                (when (and
                        (> off-col 0) 
                        (< off-col (- width 2)) 
                        (> off-row 0) 
                        (< off-row (- height 2)) )
                  (aset cave off-row off-col 0)
                  (aset cave (inc off-row) off-col 0))))))))))

(defn enlargen
  [cave width height scale]
  (let [new-cave (make-array Long (* height scale) (* width scale))]
    (dotimes [row height]
      (dotimes [col width]
        (let [scale-start-x (* col scale)
              scale-start-y (* row scale)
              val (aget cave row col)]
          (dotimes [scale-y scale]
            (dotimes [scale-x scale]
              (aset new-cave (+ scale-start-y scale-y) (+ scale-start-x scale-x) val))))))
    new-cave))

(defn array-to-vec
  [cave]
  (map #(into [] %) (into [] cave)))

(defn create-cave
  [width height]
  (let [random (Random.)
        cave (make-array Long height width)]
        
    ; Reset all to random values
    (randomise-cave cave random width height)
    
    ; Reset borders
    (cave-solid-borders cave width height)
    
    ; Loop through several times and smooth the cave
    (dotimes [_ cave-smooth-steps]
      (smooth-cave cave random width height 100))

    ; Add some vertical shafts
    (dotimes [shaft (+ cave-shafts-min (. random nextInt cave-shafts-variance))]
      (create-cave-shaft cave random width height))

    ; Enlargen up
    (let [new-cave (enlargen cave width height cave-enlargen)
          enlarged-width (* width cave-enlargen)
          enlarged-height (* height cave-enlargen)]

      ; Loop through several times and smooth the new enlarged cave
      (dotimes [_ cave-enlargen-smooth-steps]
        (smooth-cave new-cave random enlarged-width enlarged-height cave-enlargen-smooth-probability))

      ; Return cave
      (array-to-vec new-cave))))

