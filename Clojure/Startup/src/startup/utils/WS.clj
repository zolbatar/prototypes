(ns startup.utils.WS)

(defn fetch-url[address]
  (println (str "Fetching data from: " address))
   (with-open [stream (.openStream (java.net.URL. address))]
     (let  [buf (java.io.BufferedReader.
                 (java.io.InputStreamReader. stream))]
       (apply str (line-seq buf)))))