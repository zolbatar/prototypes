(ns fleetcommand.webclient.start
  (:require [fleetcommand.webclient.renderer :as renderer]
            [fleetcommand.webclient.model :as model]
            [fleetcommand.webclient.entity :as entity]
            [goog.dom :as dom]
            [goog.events :as events]
            [goog.events.KeyHandler :as key-handler]
            [goog.events.KeyCodes :as key-codes]
            [goog.net.XhrIo :as gxhr]
            [goog.net.Jsonp :as gjsonp]))

(defn keypress
  [event]
  (let [key (.-keyCode event)]
    (.log js/console key)
;    (entity/render-all)))
))

(defn ^:export start
  []
  (model/get-all-models))

(defn init-battle
  []
  (let [jsonp (goog.net.Jsonp. (str "/init/0"))]
    (.send jsonp nil nil nil)))

(defn ^:export render
  []
  (let [jsonp (goog.net.Jsonp. (str "/get/0"))]
    (.send jsonp nil nil nil)))

(defn ^:export get-battle-callback
  [reply]
  (entity/render-all (.-entities reply))
  (js/setTimeout render 1000))

(defn ^:export game-loop
  []
  (let [document (dom/getDocument)
        handler (events/KeyHandler. document true)]

    ;; Event handlers
    (events/listen handler "key" (fn [e] (keypress e)))

    ;; Init renderer
    (renderer/init)

    ;; Rendering start
    (render)

    (.log js/console "End of game-loop")))

(defn ^:export init-battle-callback
  [reply]
  (game-loop))