(ns tinker.start
  (:require [goog.dom :as dom]
            [goog.events :as events]
            [goog.events.KeyHandler :as key-handler]
            [goog.events.KeyCodes :as key-codes]
            [goog.net.XhrIo :as gxhr]
            [goog.net.Jsonp :as gjsonp]))

(def cave (atom []))
(def cave-width (atom 0))
(def cave-height (atom 0))
(def cave-x (atom 0))
(def cave-y (atom 0))

(defn build-cave
  []
  (tinker.cave-threed/build-cave @cave @cave-width @cave-height))

(defn render-cave
  []
  (tinker.cave-threed/render-cave @cave-x @cave-y))

(defn cave-callback 
  [reply]
  (reset! cave (.-cave reply))
  (reset! cave-width (.-width reply))
  (reset! cave-height (.-height reply))
  (build-cave)
  (render-cave))

(defn get-cave
  []
  (let [jsonp (goog.net.Jsonp. "/cave/0")]
    (.send jsonp nil cave-callback nil)))

(defn keypress
  [event]
  (let [key (.-keyCode event)]
    (.log js/console key)
    (swap! cave-x inc)
    (render-cave)))

(defn ^:export app-loop
  []
  (let [document (dom/getDocument)
        handler (events/KeyHandler. document true)]
    (tinker.cave-threed/init-renderer)
    (events/listen handler "key" (fn [e] (keypress e)))
    (get-cave)))
