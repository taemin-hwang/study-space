fn main() {
    let number = 3;

    if number < 5 {
        println!("condition was true");
    } else {
        println!("condition was false");
    }

    let number = 6;

    if number % 4 == 0 {
        println!("number is divisible by 4");
    } else if number % 3 == 0 {
        println!("number is divisible by 3");
    } else {
        println!("number is not divisible by 4 or 3");
    }

    // if-else
    let condition = true;
    let number = if condition {
        5
    } else {
        6
    };

    println!("number: {}", number);

    // while
    let mut number = 3;

    while number != 0 {
        println!("{}!", number);

        number -= 1;
    }

    // for
    let a = [10, 20, 30, 40, 50];
    let mut index = 0;

    while index < 5 {
        println!("the value is: {}", a[index]);
        index = index + 1;
    }

    // iterator
    for element in a.iter() {
        println!("the value is: {}", element);
    }

    // range
    for number in (1..4) {
        println!("{}!", number);
    }

    for number in (1..4).rev() { // reverse
        println!("{}!", number);
    }
}
