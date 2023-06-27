fn main() {
    println!("Hello, world!");

    another_function(5);

    let x = 5;

    let y = {
        let x = 3;
        x + 1 // no semicolon
    };

    println!("The value of x is: {}", x);
    println!("The value of y is: {}", y);

    let x = five();
    println!("The value of x is: {}", x);

    let x = plus_one(5);
    println!("The value of x is: {}", x);
}

fn another_function(x: i32) {
    println!("The value of x is: {}", x);
}

fn five() -> i32 {
    5 // no semicolon
}

fn plus_one(x: i32) -> i32 {
    x + 1 // no semicolon
}