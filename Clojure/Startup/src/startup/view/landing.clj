(ns startup.view.landing
  (:use [hiccup.core]
        [hiccup.form-helpers])
  (:require [startup.view layout]))

(defn index [user]
  (startup.view.layout/main
    (startup.view.layout/box 740 "Welcome to Startup!"
      (startup.view.layout/logout-button)
      [:div (str "Welcome " (:first-name user) " " (:surname user))]
      [:br]
      [:div
       [:input {:type "button" :value "Materials" :class "button175 pink"
                :onclick "location.href='/material'"}]
       [:br]
       [:br]
       [:br]
       [:input {:type "button" :value "Reset Model" :class "button175 black"
                :onclick "location.href='/system/new'"}]])))
