use std::io;

fn main() {
    let mut input = String::new();

    println!("Введите Xнач:");
    io::stdin().read_line(&mut input).unwrap();
    let xn: f64 = input.trim().parse().unwrap();
    input.clear();

    println!("Введите Xкон:");
    io::stdin().read_line(&mut input).unwrap();
    let xk: f64 = input.trim().parse().unwrap();
    input.clear();

    println!("Введите шаг dx:");
    io::stdin().read_line(&mut input).unwrap();
    let dx: f64 = input.trim().parse().unwrap();

    println!("\n----------------------");
    println!("|    X    |    Y    |");
    println!("----------------------");

    let mut x = xn;
    while x <= xk {
        let y = if x < -3.0 {
            0.0
        } else if x >= -3.0 && x <= -2.0 {
            -2.0 * x - 4.0
        } else if x >= -2.0 && x < 0.0 {
            (4.0 - (x + 2.0).powi(2)).sqrt()
        } else if x > 0.0 && x <= 2.0 {
            x.log2() / 2.0
        } else {
            0.5
        };

        println!("|{:>8.2}|{:>8.2} |", x, y);
        x += dx;
    }
    println!("----------------------");
}