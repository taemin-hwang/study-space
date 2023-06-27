fn main() {
    let guess: u32 = "42".parse().expect("Not a number!");
    println!("guess: {}", guess);

    let x = 2.0; // f64
    let y: f32 = 3.0; // f32

    println!("x: {}, y: {}", x, y);

    // addition
    let sum = 5 + 10;

    // subtraction
    let difference = 95.5 - 4.3;

    // multiplication
    let product = 4 * 30;

    // division
    let quotient = 56.7 / 32.2;

    // remainder
    let remainder = 43 % 5;

    // boolean
    let t = true;
    let f: bool = false; // with explicit type annotation

    // tuple
    let tup: (i32, f64, u8) = (500, 6.4, 1);

    let tup = (500, 6.4, 1);
    let (x, y, z) = tup;

    println!("x: {}, y: {}, z: {}", x, y, z);

    let five_hundred = tup.0;
    let six_point_four = tup.1;
    let one = tup.2;
    println!("five_hundred: {}, six_point_four: {}, one: {}", five_hundred, six_point_four, one);

    // array
    let a = [1, 2, 3, 4, 5];

    let first = a[0];
    let second = a[1];

    println!("first: {}, second: {}", first, second);
}
