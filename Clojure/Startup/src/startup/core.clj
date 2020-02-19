(ns startup.core
  (:use [compojure.core]
        [ring.adapter.jetty]
        [ring.middleware params file file-info]
        [sandbar core stateful-session auth form-authentication validation])
  (:require [startup.controller facebook facebookapp landing login material user system]
            [startup.utils secure]
            [startup.view error]
            [compojure.route :as route]
            [compojure.handler :as handler]
            [ring.util.response :as response]))

(defn lock [fn]
  (if (startup.utils.secure/is-logged-in)
    fn
    (response/redirect "/login/new")))

(defroutes main-routes
  (GET "/" [] (lock (startup.controller.landing/index)))
  (GET "/error" [] (startup.view.error/serious))

  ;; Facebook authentication (OAuth2.0)
  (GET "/facebook" {params :params} (startup.controller.facebook/create params))
  (GET "/facebook/new" [] (startup.controller.facebook/form))

  ;; Facebook app
  (POST "/facebookapp/" {params :params} (startup.controller.facebookapp/index-post params))
  (GET  "/facebookapp/redirect" [] (startup.controller.facebookapp/redirect))

  ;; Login
  (POST "/login" {params :params} (startup.controller.login/create params))
  (POST "/login/delete" {params :params} (lock (startup.controller.login/destroy params)))
  (GET "/login/new" [] (startup.controller.login/form))

  ;; Materials
  (GET "/material" [] (startup.controller.material/index))

  ;; User
  (POST "/user" {params :params} (startup.controller.user/create params))
  (GET "/user/new" [] (startup.controller.user/form))

  ;; System (i.e. the underlying model of the game)
  (POST "/system" {params :params} (startup.controller.system/create params))
  (GET "/system/new" [] (startup.controller.system/form))

  (route/resources "/")
  (route/not-found "Page not found"))

(def handler
  (->
    main-routes
    wrap-stateful-session
    wrap-params
    handler/site))

(defn -main []
  (let [port (Integer/parseInt (get (System/getenv) "PORT" "8080"))]
    (run-jetty handler {:port port})))

