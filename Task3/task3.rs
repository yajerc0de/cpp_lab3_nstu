use std::io;

fn gcd(mut a: i128, mut b: i128) -> i128 {
    while b != 0 {
        let t = b;
        b = a % b;
        a = t;
    }
    a.abs()
}

fn main() {
    let mut input = String::new();
    io::stdin().read_line(&mut input).expect("Failed to read line");
    let mut parts = input.split_whitespace();
    let a: usize = parts.next().unwrap().parse().expect("Invalid a");
    let b_i64: i64 = parts.next().unwrap().parse().expect("Invalid b");
    let b = b_i64 as i128;

    if b == 1 {
        println!("infinity");
        return;
    }

    // Числа Стирлинга второго рода S(n, k)
    let mut S = vec![vec![0i128; a + 1]; a + 1];
    S[0][0] = 1;

    for n in 1..=a {
        for k in 1..=n {
            S[n][k] = S[n - 1][k - 1] + (k as i128) * S[n - 1][k];
        }
    }

    // Факториалы
    let mut fact = vec![1i128; a + 1];
    for i in 1..=a {
        fact[i] = fact[i - 1] * (i as i128);
    }

    // Числитель
    let mut num = 0i128;
    for k in 1..=a {
        let term1 = S[a][k] * fact[k] * b;
        let mut pw = 1i128;
        for _ in 0..(a - k) {
            pw *= (b - 1);
        }
        num += term1 * pw;
    }

    // Знаменатель
    let mut den = 1i128;
    for _ in 0..=a {
        den *= (b - 1);
    }

    let g = gcd(num, den);
    println!("{}/{}", num / g, den / g);
}