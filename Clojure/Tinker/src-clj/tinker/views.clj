(ns tinker.views
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
      [:title "Tinker"]
      (include-css "/css/main.css")
      (include-js "/js/three.min.js")
      (include-js "/js/kinetic-v4.0.2.js")]
    [:body {:onload "tinker.start.app_loop();"}
      (include-clojurescript "/js/main-debug.js")
      [:div {:id "container"}]]))
