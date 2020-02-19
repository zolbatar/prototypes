(ns startup.controller.facebook
  (:use [clojure.contrib.string :only [split]]
        [org.danlarkin.json :as json]
        [hiccup.core]
        [startup.controller utils]
        [startup.utils Facebook WS])
  (:require [sandbar.stateful-session :as session]
            [ring.util.response :as response]))

(defn form []
  (response/redirect(str
                      "https://www.facebook.com/dialog/oauth?client_id="
                      *APP_ID*
                      "&redirect_uri="
                      *APP_URL*
                      "/facebook&scope=email")))

(defn create [params]
  (if (nil? (:error params))
    (let [code (:code params)
          phase2-response (fetch-url (str
                                       "https://graph.facebook.com/oauth/access_token?client_id="
                                       *APP_ID*
                                       "&redirect_uri="
                                       *APP_URL*
                                       "/facebook&client_secret="
                                       *APP_SECRET*
                                       "&code="
                                       code))
         access-token (first (split #"&" phase2-response))
         me (fetch-url (str "https://graph.facebook.com/me?" access-token))
         mejson (json/decode me)
         user (fb-authenticate mejson)]
      (if (not (nil? user))
        (do
          (println "Successfully authenticated with Facebook")
          (startup.model.user/set-oauth-token user access-token)
          (session/session-put! "user_id" (:_id user))
          (response/redirect "/"))
        (do
          (session/session-delete-key! "user_id")
          (flash-error "Failed to authenticate with Facebook" "/login/new"))))
    (flash-error "Failed to authenticate with Facebook" "/login/new")))



