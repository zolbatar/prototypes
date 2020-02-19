(ns startup.view.system
  (:use [hiccup.core]
        [hiccup.form-helpers])
  (:require [startup.view layout]))

(defn form []
  (startup.view.layout/main
    (form-to [:post "/system"]
      (startup.view.layout/box 550 "Reset Model"
        nil
        [:input {:type "submit" :value "Reset" :class "button175 green"}]
         [:input {:type "button" :value "Cancel" :class "button175 red"
                  :onclick "location.href='/'"}]))))
