(ns startup.view.layout
  (:use [hiccup.core]
        [hiccup.form-helpers]
        [hiccup.page-helpers])
  (:require [startup.utils secure]
            [sandbar.stateful-session :as session]))

(defn include-all-js []
  (html
    ;;      (include-js "http://code.jquery.com/jquery-latest.js")
    (include-js "javascript/jquery-1.6.2.js")
    (include-js "javascript/editor.js")))

(defn logout-button []
  (when (startup.utils.secure/is-logged-in)
    (form-to [:post "/login/delete"]
      [:input {:type "submit" :value "Logout" :class "button80 orange small"}])))

(defn main [& content]
  (html
    (doctype :html5)
    (include-all-js)
    (xhtml-tag "en"
      [:head
       [:meta {:http-equiv "Content-type" :content "text/html; charset=utf-8"}]
       [:title "Startup"]]
      ;[:link {:rel "stylesheet" :type "text/css" :href "http://fonts.googleapis.com/css?family=Cuprum&v1"}]
      ;[:link {:rel "stylesheet" :type "text/css" :href "http://fonts.googleapis.com/css?family=Actor&v1"}]
      [:link {:rel "stylesheet" :type "text/css" :href "http://fonts.googleapis.com/css?family=Molengo"}]
      [:link {:rel "stylesheet" :media "screen" :href "/stylesheets/main.css"}]
      [:link {:rel "shortcut icon" :type "image/png" :href "/images/favicon.png"}]
      [:body {:id "body"} content])))

(defn flash []
  [:div
   (session/flash-get :error)
   (session/flash-get :message)])

(defn box-550 [title footer & content]
  [:div {:class "box550"}
   [:div {:class "box550title"}
    title]
   [:div {:style "height: 1px; width: 100%; background-color: #666;"}]
   [:div {:style "padding: 10px;"}
    [:div {:style ""} content]]
   [:div {:style "clear:both"}]
   (when (not (nil? footer))
    [:div {:class "box550footer"}
    footer])])

(defn box-740 [title footer & content]
  [:div {:class "box740"}
   [:div {:class "box740title"}
    title]
   [:div {:style "height: 1px; width: 100%; background-color: #666;"}]
   [:div {:style "padding: 10px;"}
    [:div {:style ""} content]]
   [:div {:style "clear:both"}]
   (when (not (nil? footer))
    [:div {:class "box740footer"}
    footer])])

(defn box [width title footer & content]
  (cond
    (= width 550) (box-550 title footer content)
    (= width 740) (box-740 title footer content)))