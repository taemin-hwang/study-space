extern crate rand;

use std::io; // input, output library
use std::cmp::Ordering; // comparison library
use rand::Rng; // random number generator

fn main() {
    println!("Guess the number!");

    let secret_number = rand::thread_rng().gen_range(1, 101);

    // println!("The secret number is: {}", secret_number);

    loop {
        println!("Please input your guess.");

        let mut guess = String::new(); // mutable variable
        //let foo = 5; // immutable variable

        io::stdin().read_line(&mut guess)
            .expect("Failed to read line");

        // read_line은 guess에 입력을 저장할 뿐만 아니라 io::Result를 반환한다.
        // Result 타입은 열거형이다. Ok와 Err 두 가지의 값이 존재한다.
        // io::Result 인스턴스는 expect 메소드를 가지고 있다.
        // expect 메소드는 Result가 Err일 경우 프로그램을 종료하고 메시지를 출력한다.
        // Ok일 경우 Ok 안에 있는 값을 반환한다.
        // 만약 expect를 사용하지 않는다면 경고가 발생한다***

        // expect 메소드 호출을 match 표현식으로 바꾸는 것은 에러 발생ㅇ르 처리하는 더 좋은 방법이다.
        let guess: u32 = match guess.trim().parse() {
            Ok(num) => num,
            Err(_)  => continue,
        };
        // trim 메소드를 통해 guess의 앞뒤 공백을 제거한다. (/n 제거)
        // parse 메소드를 통해 문자열을 숫자로 변환한다.
        // guess 뒤의 :은 타입을 명시하는 것이다.

        println!("You guessed: {}", guess);

        match guess.cmp(&secret_number) {
            Ordering::Less    => println!("Too small!"),
            Ordering::Greater => println!("Too big!"),
            Ordering::Equal   => {
                println!("You win!");
                break; // loop를 종료한다.
            }
        }
    } // loop
}
