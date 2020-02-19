(ns startup.model.material
  (:use [startup.model db]
        [somnium.congomongo]))

(defn all []
  (with-mongo db
    (fetch :Materials)))

(defn find-all-material-transition [route id]
  (with-mongo db
    (fetch :Materials-Transition :where {:route route :source id})))


(defn find-one-material-by [key value]
  (with-mongo db
    (fetch-one :Materials :where {key value})))

(defn create-ore [title description]
  (with-mongo db
    (insert! :Materials {:type "Ore"
                         :title title
                         :description description})))

(defn create-material [title description]
  (with-mongo db
    (insert! :Materials {:type "Material"
                         :title title
                         :description description})))

(defn create-product [title description]
  (with-mongo db
    (insert! :Materials {:type "Product"
                         :title title
                         :description description})))

(defn create-material-transition [route source destination quantity]
  (with-mongo db
    (insert! :Materials-Transition {:route route
                                    :source (:_id (find-one-material-by :title source))
                                    :destination (:_id (find-one-material-by :title destination))
                                    :quantity quantity})))

(defn drop-coll []
  (with-mongo db
     (drop-coll! :Materials)
     (drop-coll! :Materials-Transition)))

(defn build-indexes []
  (with-mongo db
    (add-index! :Materials-Transition [:source])
    (add-index! :Materials-Transition [:destination])))
