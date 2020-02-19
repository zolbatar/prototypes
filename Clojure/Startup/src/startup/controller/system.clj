(ns startup.controller.system
  (:use [startup.controller utils])
  (:require [startup.view system]
            [startup.model material skill task]
            [ring.util.response :as response]))

;; Build the model for the game
(defn create [params]

  ;; Ore
  (println "Creating raw materials")
  (startup.model.material/drop-coll)
  (startup.model.material/create-ore "Ore-Metal" "Metal Ore")
  (startup.model.material/create-ore "Ore-Oil" "Oil")
  (startup.model.material/create-ore "Ore-Precious" "Precious Ore")
  (startup.model.material/create-ore "Ore-Rare" "Rare Ore")
  (startup.model.material/create-ore "Ore-Sand" "Sand")
  (startup.model.material/create-ore "Ore-Trees" "Trees")

  ;; Materials
  (println "Creating materials")
  (startup.model.material/create-material "Material-Energy" "Energy")
  (startup.model.material/create-material "Material-Metal" "Metal")
  (startup.model.material/create-material "Material-Jewels" "Jewels")
  (startup.model.material/create-material "Material-Glass" "Glass")
  (startup.model.material/create-material "Material-Plastic" "Plastic")
  (startup.model.material/create-material "Material-Rare" "Rare")
  (startup.model.material/create-material "Material-Wood" "Wood")

  (startup.model.material/create-material-transition "Out" "Ore-Metal" "Metal" 3)
  (startup.model.material/create-material-transition "Out" "Ore-Oil" "Material-Energy" 5)
  (startup.model.material/create-material-transition "Out" "Ore-Oil" "Material-Plastic" 5)
  (startup.model.material/create-material-transition "Out" "Ore-Precious" "Material-Jewels" 500)
  (startup.model.material/create-material-transition "Out" "Ore-Rare" "Material-Rare" 100)
  (startup.model.material/create-material-transition "Out" "Ore-Sand" "Material-Glass" 10)
  (startup.model.material/create-material-transition "Out" "Ore-Trees" "Material-Wood" 2)

  ;; Products
  (println "Creating products")
  (startup.model.material/create-product "Product-Computer" "Computer")
  (startup.model.material/create-material-transition "In" "Material-Energy" "Product-Computer" 20)
  (startup.model.material/create-material-transition "In" "Material-Glass" "Product-Computer" 5)
  (startup.model.material/create-material-transition "In" "Material-Metal" "Product-Computer" 10)
  (startup.model.material/create-material-transition "In" "Material-Rare" "Product-Coputer" 1)
  (startup.model.material/create-material-transition "In" "Material-Plastic" "Product-Computer" 20)

  ;; Skills tree
  (println "Creating skills tree")
  (startup.model.skill/drop-coll)
  (startup.model.skill/create "Learning" "Learning learning, the art of research and study." nil)
  (startup.model.skill/create "Mining" "Mining ore which can then be processed into mineral." nil)
  (startup.model.skill/create "Refining" "Refining raw ore into mineral." nil)
  (startup.model.skill/create "Manufacturing" "Combining minerals into a finished product." nil)
  (startup.model.skill/create "Recycling" "Recycling a product back into minerals." nil)
  (startup.model.skill/create "Market Trader" "Trading in stocks and shares." nil)
  (startup.model.skill/create "Buying & Selling" "Understanding the market." nil)

  ;; Build indexes
  (println "Creating indexes")
  (startup.model.material/build-indexes)
  (startup.model.skill/build-indexes)

  (response/redirect "/"))

(defn form []
  (startup.view.system/form))