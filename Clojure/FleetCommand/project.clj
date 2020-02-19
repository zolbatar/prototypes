(defproject FleetCommand "1.0.0-SNAPSHOT"
  :description "Fleet command - a JS/HTML5 Fleet command game"
    :source-path "src-clj"
    :source-paths ["src-clj"]
    :dependencies [[org.clojure/clojure "1.4.0"]
                    [compojure "1.0.4"]
                    [hiccup "1.0.0"]
                    [cheshire "4.0.3"]]
    :dev-dependencies [[lein-ring "0.7.0"]]
    :plugins [[lein-cljsbuild "0.2.7"]]  
    :hooks [leiningen.cljsbuild]
    :cljsbuild {
      :builds [{
        :source-path "src-cljs"
        :jar true
        :compiler {
          :output-to "resources/public/js/main-debug.js"
          :optimizations :whitespace ;:advanced
          :pretty-print true }}]}
    :ring {:handler fleetcommand.server.routes/app :auto-reload? true :auto-refresh? true}) 
