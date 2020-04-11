pub fn get_primes_up_to_number(max: u64) -> Vec<u64> {
    let mut primes: Vec<u64> = Vec::new();
    primes.push(2);

    // Rough cut, get possible primes
    for x in (3..=max).step_by(2) {
        let mut found = false;
        for prime in &primes {
            if x % prime == 0 {
                found = true;
                break;
            }
        }
        if !found {
            primes.push(x);
        }
    }
    println!("Number of primes: {}", primes.len());
    primes
}

pub fn get_number_of_primes(num: usize) -> Vec<u64> {
    let mut primes: Vec<u64> = Vec::new();
    primes.push(2);

    // Rough cut, get possible primes
    let mut x = 3;
    while primes.len() < num {
        let mut found = false;
        for prime in &primes {
            if x % prime == 0 {
                found = true;
                break;
            }
        }
        if !found {
            primes.push(x);
        }
        x += 1;
    }
    println!("Number of primes: {}", primes.len());
    primes
}
