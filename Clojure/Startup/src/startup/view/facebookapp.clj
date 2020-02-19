(ns startup.view.facebookapp
  (:use [hiccup.core]
        [hiccup.form-helpers])
  (:require [startup.view.layout main flash]))

(defn index []
  (startup.view.layout/main
    [:div "Welcome"]))

