(ns startup.controller.utils
  (:use [compojure.core]
        [ring.adapter.jetty]
        [somnium.congomongo])
  (:require [sandbar.stateful-session :as session]
            [ring.util.response :as response]))

(defn flash-fn [type]
  (fn [msg url]
    (session/flash-put! type msg)
    (response/redirect url)))

(def flash-error (flash-fn :error))
(def flash-msg (flash-fn :message))