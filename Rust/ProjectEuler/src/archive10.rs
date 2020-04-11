fn problem_1() {
    let mut result = 0;
    for x in 1..1000 {
        let divide_3 = x % 3 == 0;
        let divide_5 = x % 5 == 0;
        if divide_3 || divide_5 {
            result += x;
        }
    }
    println!("{}", result);
}

fn problem_2() {
    let mut previous = 1;
    let mut current = 2;
    let mut fib_array: Vec<u64> = Vec::new();
    fib_array.push(1);
    fib_array.push(2);

    // Loop to add to result
    loop {
        let fib = previous + current;
        previous = current;
        current = fib;
        if current > 4000000 {
            break;
        }
        if fib % 2 == 0 {
            fib_array.push(fib)
        };
    }

    let result: u64 = fib_array.iter().sum();

    println!("{:?}", fib_array);
    println!("{}", result);
}

fn problem_3() {
    let number = 600851475143;
    let primes = crate::primes::get_primes_up_to_number(f64::sqrt(number as f64) as u64);

    // Reverse primes so we start at the end
    primes.reverse();

    // Now figure out highest prime factor
    for x in primes.iter() {
        if number % x == 0 {
            println!("Answer: {}", x);
            std::process::exit(0);
        }
    }
}

fn problem_4() {
    fn problem_4_is_palindrome(n: u64) -> bool {
        // Convert to string first
        let s = n.to_string();

        let l = s.len();
        for x in 0..l / 2 {
            if s.as_bytes()[x] != s.as_bytes()[l - 1 - x] {
                return false;
            }
        }
        return true;
    }

    let mut m = 0;
    for n1 in 100..=999 {
        for n2 in 100..=999 {
            let is = problem_4_is_palindrome(n1 * n2);
            if is && n1 * n2 > m {
                m = n1 * n2;
            }
        }
    }
    println!("Palindrome: {}", m);
}

fn problem_5() {
    // Sum all together first, this is the HIGHEST possible number
    let mut result: u64 = 1;
    for x in 2..=20 {
        result *= x;
    }

    // Now loop through each number in turn and keep dividing by it until we can divide no more
    for x in 2..=20 {
        while result % x == 0 {
            let possible = result / x;
            // Valid?
            let valid = possible % 11 == 0
                && possible % 12 == 0
                && possible % 13 == 0
                && possible % 14 == 0
                && possible % 15 == 0
                && possible % 16 == 0
                && possible % 17 == 0
                && possible % 18 == 0
                && possible % 19 == 0
                && possible % 20 == 0;

            if valid {
                result = possible;
            } else {
                break;
            }
        }
    }
    println!("End: {}", result);
}

fn problem_6() {
    fn sum_of_square(n: u64) -> u64 {
        (1..=n).fold(0, |acc, &x| acc + (x * x))
    }

    fn square_of_sum(n: u64) -> u64 {
        let i = (1..=n).fold(0, |acc, &x| acc + x);
        i * i
    }

    let n = 100;
    let result = square_of_sum(n) - sum_of_square(n);
    println!("Result: {}", result);
}

fn problem_7() {
    let mut primes = crate::primes::get_number_of_primes(10001);
    println!("{:?}", primes.pop().unwrap());
}

fn problem_8() {
    const DIGITS: usize = 13;

    let i = "7316717653133062491922511967442657474235534919493496983520312774506326239578318016984801869478851843858615607891129494954595017379583319528532088055111254069874715852386305071569329096329522744304355766896648950445244523161731856403098711121722383113622298934233803081353362766142828064444866452387493035890729629049156044077239071381051585930796086670172427121883998797908792274921901699720888093776657273330010533678812202354218097512545405947522435258490771167055601360483958644670632441572215539753697817977846174064955149290862569321978468622482839722413756570560574902614079729686524145351004748216637048440319989000889524345065854122758866688116427171479924442928230863465674813919123162824586178664583591245665294765456828489128831426076900422421902267105562632111110937054421750694165896040807198403850962455444362981230987879927244284909188845801561660979191338754992005240636899125607176060588611646710940507754100225698315520005593572972571636269561882670428252483600823257530420752963450".as_bytes();

    let adjusted_length: usize = i.len() - DIGITS;
    let mut maximum = 0;
    for x in 0..=adjusted_length {
        let mut n: [u64; DIGITS] = [0; DIGITS];
        for y in 0..DIGITS {
            n[y] = i[x + y] as u64 - 48;
        }
        let tot: u64 = n.iter().product();
        if tot > maximum {
            maximum = tot;
        }
    }
    println!("Result: {}", maximum);
}

fn problem_9() {
    fn check_pythagorean_triplet(a: u64, b: u64, c: u64) -> bool {
        (a * a) + (b * b) == c * c
    }

    // So we can assume that each of the numbers MUST be less than a 1000
    const MAX_VAL: u64 = 1000;
    for a in 2..MAX_VAL {
        for b in 2..MAX_VAL {
            for c in 2..MAX_VAL {
                // Now we know it must equal 1000
                if a + b + c == 1000 {
                    if check_pythagorean_triplet(a, b, c) {
                        println!("Result: {}", a * b * c);
                        return;
                    }
                }
            }
        }
    }
}

fn problem_10() {
    let primes = crate::primes::get_primes_up_to_number(2000000);
    println!("Number of primes: {}", primes.len());
    let sum: u64 = primes.iter().sum();
    println!("{:?}", sum);
}
