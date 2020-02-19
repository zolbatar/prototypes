(defproject startup "0.0.1"
  :description "Clojure based Startup game"
  :dependencies [[org.clojure/clojure "1.2.1"]
                 [org.clojure/clojure-contrib "1.2.0"]
                 [compojure "0.6.5"]
                 [hiccup "0.3.6"]
                 [ring/ring-core "0.3.9"]
                 [ring/ring-jetty-adapter "0.3.9"]
                 [congomongo "0.1.7-SNAPSHOT"]
                 [sandbar/sandbar "0.4.0-SNAPSHOT"]
                 [org.danlarkin/clojure-json "1.2-SNAPSHOT"]
                 [commons-codec/commons-codec "1.4"]]
  :dev-dependencies [[lein-ring "0.4.5"]]
  :ring {:handler startup.core/handler})