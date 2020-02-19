(ns startup.view.user
  (:use [hiccup.core]
        [hiccup.form-helpers])
  (:require [startup.view layout]))

(defn form []
  (startup.view.layout/main
    (form-to [:post "/user"]
      (startup.view.layout/box 550 "Register"
        nil
        [:fieldset
         (startup.view.layout/flash)
         [:ol
          [:li
           (label "firstname-label" "First Name:")
           (text-field "first-name")]
          [:li
           (label "surname-label" "Surname:")
           (text-field "surname")]
          [:li
           (label "email-label" "Email:")
           (text-field "email")]
          [:li
           (label "password-label" "Password:")
           (password-field "password")]
          [:li
           (label "password-confirm-label" "Confirm Password:")
           (password-field "confirm-password")]]]
        [:div
         [:input {:type "submit" :value "Register" :class "button175 green"}]
         [:input {:type "button" :value "Cancel" :class "button175 red"
                  :onclick "location.href='/login/new'"}]]))))
