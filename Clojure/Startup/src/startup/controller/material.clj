(ns startup.controller.material
  (:use [startup.controller utils])
  (:require [sandbar.stateful-session :as session]
            [ring.util.response :as response]
            [startup.view material]
            [startup.model material]))

(defn index []
  (startup.view.material/index))
