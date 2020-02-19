(ns startup.model.skill
  (:use [startup.model db]
        [somnium.congomongo]))

(defn create [title description required-skills]
  (with-mongo db
    (insert! :Skills {:title title
                      :description description
                      :required-skills required-skills})))

(defn drop-coll []
  (with-mongo db
     (drop-coll! :Skills)))

(defn build-indexes [])
