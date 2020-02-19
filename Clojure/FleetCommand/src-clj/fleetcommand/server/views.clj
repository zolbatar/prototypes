(ns fleetcommand.server.views
  (:require
    [hiccup
      [page :refer [html5]]
      [element :refer [javascript-tag]]
      [page :refer [include-js include-css]]]))

(defn- include-clojurescript [path]
  (list
    (javascript-tag "var CLOSURE_NO_DEPS = true;")
    (include-js path)))

(defn index-page []
  (html5
    [:head
      [:title "Fleet Command"]
      (include-css "/css/main.css")]
    [:body {:onload "fleetcommand.webclient.start.start();"}
      (include-clojurescript "/js/main-debug.js")
      [:div {:id "container"}]]))
