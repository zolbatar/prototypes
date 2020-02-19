(ns startup.view.material
  (:use [hiccup.core]
        [hiccup.form-helpers])
  (:require [startup.view layout]
            [startup.model material]))

(defn index []
  (startup.view.layout/main
    (startup.view.layout/box 740 "Materials"
      (startup.view.layout/logout-button)
      [:table
       [:th "Type"]
       [:th "Description"]
       [:th "Produces"]
       [:th "Required By"]
       (for [x (startup.model.material/all)]
         [:tr
          [:td (:type x)]
          [:td (:description x)]
          [:td
           (for [in (startup.model.material/find-all-material-transition "Out" (:_id x))]
             (let [in-object (startup.model.material/find-one-material-by :_id (:destination in))]
               (str (:description in-object) "&nbsp;")))]
          [:td
           (for [in (startup.model.material/find-all-material-transition "In" (:_id x))]
             (let [in-object (startup.model.material/find-one-material-by :_id (:destination in))]
               (str (:description in-object) "&nbsp;")))]])]
      [:div
       [:input {:type "button" :value "Back" :class "button175 red"
                :onclick "location.href='/'"}]])))
