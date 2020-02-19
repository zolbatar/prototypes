(ns startup.view.error
  (:use [hiccup.core]
        [hiccup.form-helpers]
        [hiccup.page-helpers])
  (:require [startup.view layout]))

(defn serious []
  (html
    (doctype :html5)
    (startup.view.layout/include-all-js)
    (xhtml-tag "en"
      [:head
       [:meta {:http-equiv "Content-type" :content "text/html; charset=utf-8"}]
       [:title "Startup"]]
      [:link {:rel "stylesheet" :type "text/css" :href "http://fonts.googleapis.com/css?family=Cuprum&v1"}]
      [:link {:rel "stylesheet" :media "screen" :href "/stylesheets/main.css"}]
      [:link {:rel "shortcut icon" :type "image/png" :href "/images/favicon.png"}]
      [:body {:id "body"} "Something serious has occured"])))
