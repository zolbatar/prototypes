(ns fleetcommand.server.routes
  (:use compojure.core
        [fleetcommand.server.views]
        [hiccup.middleware :only (wrap-base-url)])
  (:require [fleetcommand.server.entity :as entity]
            [fleetcommand.server.models.model :as model]
            [compojure.route :as route]
            [compojure.handler :as handler]
            [compojure.response :as response]))

(defroutes main-routes
  (GET "/" [] (index-page))
  (GET "/models" [] (model/get-models))
  (GET "/init/:battle-id" [battle-id] (entity/build-battle battle-id))
  (GET "/get/:battle-id" [battle-id] (entity/get-battle battle-id))
  (route/resources "/")
  (route/not-found "Page not found"))

(def app
  (-> (handler/site main-routes)
      (wrap-base-url)))