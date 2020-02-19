(ns startup.utils.secure
  (:require [startup.model user]
            [sandbar.stateful-session :as session]))

(defn is-logged-in []
  (not (nil? (session/session-get "user_id"))))

(defn current-user []
  (startup.model.user/find-one-by :_id (session/session-get "user_id")))
