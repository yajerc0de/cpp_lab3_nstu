use std::io;

fn best_move(a: &[i32], pos: usize, n: usize, m: usize, last_take: i32) -> usize {
    let limit = std::cmp::min(m, n - pos);
    let mut best_sum = i32::MIN;
    let mut best_k = 1;
    let mut cur_sum = 0;

    for k in 1..=limit {
        cur_sum += a[pos + k - 1];
        // Нельзя повторять размер предыдущего хода соперника
        if k as i32 == last_take {
            continue;
        }
        if cur_sum > best_sum || (cur_sum == best_sum && k < best_k) {
            best_sum = cur_sum;
            best_k = k;
        }
    }
    best_k
}

fn main() {
    let mut input = String::new();
    io::stdin().read_line(&mut input).expect("Failed to read n, m");
    let mut iter = input.split_whitespace();
    let n: usize = iter.next().unwrap().parse().expect("Invalid n");
    let m: usize = iter.next().unwrap().parse().expect("Invalid m");

    let mut input = String::new();
    io::stdin().read_line(&mut input).expect("Failed to read array");
    let a: Vec<i32> = input
        .split_whitespace()
        .map(|x| x.parse().expect("Invalid number"))
        .collect();
    assert_eq!(a.len(), n, "Array size does not match n");

    let mut pavel = 0;
    let mut vika = 0;
    let mut last_pavel = 0;
    let mut last_vika = 0;
    let mut pos = 0;
    let mut turn = 0; // 0 – Павел, 1 – Вика

    while pos < n {
        let take = if turn == 0 {
            best_move(&a, pos, n, m, last_pavel)
        } else {
            best_move(&a, pos, n, m, last_vika)
        };

        let sum: i32 = a[pos..pos + take].iter().sum();

        if turn == 0 {
            pavel += sum;
            last_pavel = take as i32;
        } else {
            vika += sum;
            last_vika = take as i32;
        }

        pos += take;
        turn ^= 1; // смена игрока
    }

    println!("{}", if pavel > vika { 1 } else { 0 });
}