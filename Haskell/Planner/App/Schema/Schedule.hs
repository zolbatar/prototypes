module App.Schema.Schedule where

import Debug.Trace
import qualified Data.HashTable.IO as H

-- Concrete type, for ease of changing hash table implementation and to enable GHC optimisations
type HashTable k v = H.BasicHashTable k v

data Entity = Activity { locationID :: String, value :: Double }
            | Resource { locationID :: String, costPH :: Double }
            deriving Show

data Location = LocationLatLng { latitude, longitude :: Double } deriving Show

data Schedule = Schedule { entities :: IO (HashTable String Entity), locations :: IO (HashTable String Location) }

emptySchedule :: Schedule
emptySchedule = Schedule { entities = H.new, locations = H.new }

addLocation :: Schedule -> String -> Location -> IO Schedule
addLocation s pk l = do
  ht <- locations s
  H.insert ht pk l
  return s

getLocation :: Schedule -> String -> IO (Maybe Location)
getLocation s pk = do
  ht <- locations s
  H.lookup ht pk
