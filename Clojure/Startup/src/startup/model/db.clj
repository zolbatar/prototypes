(ns startup.model.db
  (:use [somnium.congomongo]))

(def db (make-connection
          "startup"
          {:host "staff.mongohq.com" :port 10049}))
(authenticate db "dbu" "Sh33p15h")
(println db)

(defn close []
  (close-connection db))

