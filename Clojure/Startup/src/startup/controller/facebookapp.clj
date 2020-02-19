(ns startup.controller.facebookapp
  (:use [hiccup.core]
        [hiccup.form-helpers]
        [hiccup.page-helpers]
        [org.danlarkin.json :as json]
        [startup.controller utils]
        [startup.utils Facebook WS])
  (:require [startup.model user]
            [sandbar.stateful-session :as session]
            [ring.util.response :as response])
  (:import [org.apache.commons.codec.binary Base64]
           [javax.crypto Mac]
           [javax.crypto.spec SecretKeySpec]))

(defn index-post [params]
  (let [request (parse-signed-request (:signed_request params))]
    (println request)
    (if (not (or (nil? request) (nil? (:oauth_token request))))
      (let [access-token (str "access_token=" (:oauth_token request))
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

      ;; User hasn't allowed access, redirect
      (do
        (println "User hasn't allowed access, redirect")
        (session/session-delete-key! "user_id")
        (html (str "<script>window.top.location.href=\""
                (str "https://www.facebook.com/dialog/oauth?client_id="
                  *APP_ID*
                  "&redirect_uri="
                  *APP_REDIRECT*
                  "&scope=email")
                "\"</script>"))))))

(defn redirect []
  (response/redirect *APP_FB*))
