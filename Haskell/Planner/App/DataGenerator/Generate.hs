module App.DataGenerator.Generate where

import App.Schema.Schedule
import App.Shared.Geocoder

generateData :: String -> Int -> Int -> IO (Maybe Schedule)
generateData loc _ _ = do
  geocodeResult <- geocode loc
  case geocodeResult of
    Just (lat, lng) -> 
      let s = emptySchedule
          l = LocationLatLng { latitude = lat, longitude = lng }
      in do
          snew <- addLocation s "10" l
          l2 <- getLocation s "1"
          return $ Just snew
    Nothing -> return Nothing
