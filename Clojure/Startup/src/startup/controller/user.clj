(ns startup.controller.user
  (:use [startup.controller utils])
  (:require [startup.view user]
            [startup.model user]
            [ring.util.response :as response]))

(defn create [params]
  ;; Email address must be filled in
  (when (= 0 (.length (:email params)))
    (flash-error "Email address must be specified" "/user/new"))

  ;; Ensure passwords match
  (when (not= (:password params) (:confirm-password params))
    (flash-error "Passwords don't match" "/user/new"))

  ;; Blank passwords aren't allowed
  (when (<= 4 (.length (:password params)))
    (flash-error "Password must be at least 4 characters long" "/user/new"))

  (startup.model.user/create (:first-name params) (:surname params) (:email params) (:password params))
  (response/redirect "/"))

(defn form []
  (startup.view.user/form))


