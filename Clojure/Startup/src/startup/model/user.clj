(ns startup.model.user
  (:use [startup.model db]
        [somnium.congomongo]
        [startup.utils MD5]))

(defn all []
  (with-mongo db
    (fetch :Users)))

(defn find-one-by [key value]
  (with-mongo db
    (fetch-one :Users :where {key value})))

(defn find-all-by [key value]
  (with-mongo db
    (fetch :Users :where {key value})))

(defn create [first-name surname email password]
  (with-mongo db
    (insert! :Users {:first-name first-name
                     :surname surname
                     :email email
                     :password (md5-sum password)})))

(defn login [email password]
  (with-mongo db
    (let [user
          (fetch-one :Users
            :where {:email email
                    :password (md5-sum password)})]
      (println "Logged in user")
      (println user)
      user)))

(defn associate-with-facebook [user id]
  (let [updated-user (merge user {:facebook-id id})]
    (with-mongo db
      (update! :Users user updated-user)
      updated-user)))

(defn set-oauth-token [user token]
  (let [updated-user (merge user {:oauth-token token})]
    (with-mongo db
      (update! :Users user updated-user)
      updated-user)))