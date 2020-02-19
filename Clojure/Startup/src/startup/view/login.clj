(ns startup.view.login
  (:use [hiccup.core]
        [hiccup.form-helpers])
  (:require [startup.view layout]))

(defn form []
  (startup.view.layout/main
    (form-to [:post "/login"]
      (startup.view.layout/box 550 "Please Login"
        [:div {:style "float: none;"} "Need an account?&nbsp;"
         [:span
          [:a {:href "/user/new"} "Register"]]]
        (startup.view.layout/flash)
        [:fieldset
         [:ol
          [:li
           (label "email-label" "Email:")
           (text-field "email")]
          [:li
           (label "password-label" "Password:")
           (password-field "password")]]]
        [:div {:style "padding: 10px"}
         [:input {:type "submit" :value "Login" :class "button175 green"}]
         [:input {:type "button" :value "Login with Facebook" :class "button175 blue"
                  :onclick "location.href='/facebook/new'"}]]))))