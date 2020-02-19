module Main where

import App.DataGenerator.Generate

main :: IO ()
main = do 
  schedule <- generateData "DE7 8EX, UK" 0 0
  case schedule of
    Just _ -> putStrLn "Success"
    Nothing -> putStrLn "Error"
