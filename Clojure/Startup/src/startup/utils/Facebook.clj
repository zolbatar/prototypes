(ns startup.utils.Facebook
  (:use [clojure.contrib.string :only [split replace-str]]
        [clojure.contrib.json :only [read-json]])
  (:require [startup.model user]
            [startup.utils secure]
            [sandbar.stateful-session :as session]
            [ring.util.response :as response])
  (:import [org.apache.commons.codec.binary Base64]
           [javax.crypto Mac]
           [javax.crypto.spec SecretKeySpec]
           [java.util Arrays]))

(def *APP_ID* "248847338470571")
(def *APP_SECRET* "297a3297fc1bc12f15113a16e742cf1d")
(def *APP_URL* "http://stark-snow-264.herokuapp.com")
(def *APP_REDIRECT* "http://stark-snow-264.herokuapp.com/facebookapp/redirect")
(def *APP_FB* "http://apps.facebook.com/thestartupgame")

(defn fb-authenticate [json]
  (if (nil? (:id json))
    nil

    ;; Collate some data
    (let [facebook_id (:id json)
          first_name (:first_name json)
          surname (:last_name json)
          email (:email json)]
      (println (str "Facebook returned - id: " facebook_id " name: " first_name " " surname " email: " email))

      ;; Do we have a facebook id?
      (if (not= facebook_id "")
        (do

          ;; Do we know about this facebook id?
          (let [user (startup.model.user/find-one-by :facebook_id facebook_id)]
            (if (nil? user)
              (do

                ;; Do we have a logged in user?
                (if (startup.utils.secure/is-logged-in)
                  (do
                    (println "User already logged into site, associating account with Facebook ID")
                    (startup.model.user/associate-with-facebook (startup.utils.secure/current-user) facebook_id))

                  ;; Let's try and match on email
                  (let [email-user (startup.model.user/find-one-by :email facebook_id)]
                    (if (not (nil? email-user))
                      (startup.model.user/associate-with-facebook email-user facebook_id)

                      ;; Okay, new user time
                      (let [new-user (startup.model.user/create first_name surname email, "")]
                        (println "No match on email, creating new user")
                        (if (nil? new-user)
                          (do
                            (println "Registration failed")
                            nil)
                          (startup.model.user/associate-with-facebook new-user facebook_id)))))))
              user)))
        nil))))

(defn base64-url-decode [s]
  (Base64/decodeBase64 (replace-str "_" "/" (replace-str "-" "+" s))))

(defn hash-hmac-sha256 [s]
  (let [mac (Mac/getInstance "HmacSHA256")
        secret (SecretKeySpec. (. *APP_SECRET* getBytes) "HmacSHA256")]
    (. mac init secret)
    (. mac doFinal (. s getBytes))))

(defn parse-signed-request [signed-request]
  (let [fields (split #"\." signed-request)
        encoded-sig (first fields)
        payload (last fields)
        sig (base64-url-decode encoded-sig)
        decoded-payload (String. (base64-url-decode payload) "UTF-8")
        decoded-map (read-json decoded-payload)]

    ; Check algorithm
    (if (= (:algorithm decoded-map) "HMAC-SHA256")

      ; Check signature
      (let [expected-sig (hash-hmac-sha256 payload)]
        (if (Arrays/equals sig expected-sig)
          (do
            (println "Decoded Facebook signed request")
            decoded-map)
          (do
            (println "Bad signed JSON Signature from Facebook")
            nil)))
      (do
        (println "Got invalid algorithm from Facebook")
        nil))))
