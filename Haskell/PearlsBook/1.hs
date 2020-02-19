import Data.List

minfree :: [Int] -> Int
minfree xs = minfrom 0 (length xs, xs)

minfrom :: Int -> (Int, [Int]) -> Int
minfrom a (n, xs) | n == 0       = a
                  | m == b - a   = minfrom b (n - m, vs)
                  | otherwise    = minfrom a (m, us)
                    where (us,vs) = partition (< b) xs
                          b       = a + 1 + n `div` 2
                          m       = length us

main :: IO ()
main = 
  print $ minfree [0,2,3,7,10]