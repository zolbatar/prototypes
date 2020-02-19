(ns startup.controller.landing
  (:use [startup.controller utils])
  (:require [startup.view landing]
            [startup.utils secure]))

(defn index []
  (startup.view.landing/index (startup.utils.secure/current-user)))
