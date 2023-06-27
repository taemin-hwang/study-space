use std::cmp::Ordering;

fn main() {
    const MAX_POINTS: u32 = 100_000;

    let mut x = 5;
    println!("The value of x is: {}", x);
    x = 6;
    println!("The value of x is: {}", x);

    let x = x + 1;
    println!("The value of x is: {}", x);

    let x = x * 2;
    println!("The value of x is: {}", x);

    match x.cmp(&MAX_POINTS) {
        Ordering::Less => println!("x is less than MAX_POINTS"),
        Ordering::Greater => println!("x is greater than MAX_POINTS"),
        Ordering::Equal => println!("x is equal to MAX_POINTS"),
    }

}
