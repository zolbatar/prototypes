(ns startup.controller.login
  (:use [startup.controller utils])
  (:require [sandbar.stateful-session :as session]
            [ring.util.response :as response]
            [startup.view login]
            [startup.model user]))

(defn create [params]
  (let [user (startup.model.user/login (:email params) (:password params))]
    (if (nil? user)
      (do
        (session/session-delete-key! "user_id")
        (flash-error "Username and/or password not valid" "/login/new"))
      (do
        (session/session-put! "user_id" (:_id user))
        (response/redirect "/")))))

(defn destroy [params]
  (session/session-delete-key! "user_id")
  (response/redirect "/"))

(defn form []
  (startup.view.login/form))


