import Data.List

msc :: Ord a => [a] -> Int
msc xs = maximum [scount z zs | z : zs <- tails xs]

scount :: Ord a => a -> [a] -> Int
scount x xs = length (filter (x <) xs)

main :: IO ()
main = 
  print $ msc "GENERATING"