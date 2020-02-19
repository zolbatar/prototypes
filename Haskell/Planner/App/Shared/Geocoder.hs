module App.Shared.Geocoder where

import Debug.Trace
import Geography.Geocoding.Google (geoEncode)

geocode :: String -> IO (Maybe (Double, Double))
geocode loc = do
  geoloc <- geoEncode loc
  case geoloc of
    Left err -> 
      trace("Error in geocoding: " ++ err)
      return Nothing
    Right x -> return $ Just x

