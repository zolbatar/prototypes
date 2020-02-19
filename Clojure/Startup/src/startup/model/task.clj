(ns startup.model.task
  (:use [startup.model db]
        [somnium.congomongo]))

(defn create-learning [title description required-skills time]
  (with-mongo db
    (insert! :Tasks {:type "Learning"
                     :title title
                     :description description
                     :required-skills required-skills
                     :time time})))


