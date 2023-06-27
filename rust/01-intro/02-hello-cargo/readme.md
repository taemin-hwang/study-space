Cargo(카고)는 러스트의 빌드 시스템 및 패키지 매니저입니다.

압도적인 숫자의 러스트 프로젝트가 Cargo를 이용하기 때문에, 이 책의 나머지 부분에서는 여러분 또한 Cargo를 이용하고 있음을 가정합니다.

```
$ cargo --version
```

### Cargo를 사용하여 프로젝트 생성하기
여러분의 projects 디렉토리로 (혹은 여러분의 코드를 저장하기로 결정한 어느 곳이든) 이동하세요.

그 다음, 어떤 운영체제이든 상관없이 다음을 실행하세요:

```
$ cargo new hello_cargo --bin
$ cd hello_cargo
```

첫번째 커맨드는 hello_cargo라고 불리우는 새로운 실행 가능한 바이너리를 생성합니다

bin 인자가 라이브러리가 아닌 실행 가능한 애플리케이션으로 만들어줍니다

Cargo가 만든 프로젝트의 차이점
* Cargo가 코드를 src 디렉토리 안에 위치시킨다는 점
* 최상위 디렉토리에 Cargo.toml 환경 파일을 가지게 해준다는 점

### Cargo 프로젝트를 빌드하고 실행하기

```
$ cargo build
   Compiling hello_cargo v0.1.0 (file:///projects/hello_cargo)
    Finished dev [unoptimized + debuginfo] target(s) in 2.85 secs
```

```
$ cargo run
    Finished dev [unoptimized + debuginfo] target(s) in 0.0 secs
     Running `target/debug/hello_cargo`
Hello, world!
```

종종 cargo check가 cargo build에 비해 훨씬 빠른데, 그 이유는 이 커맨드가 실행파일을 생성하는 단계를 생략하기 때문입니다
```
$ cargo check
   Compiling hello_cargo v0.1.0 (file:///projects/hello_cargo)
    Finished dev [unoptimized + debuginfo] target(s) in 0.32 secs
```

### 릴리즈 빌드
여러분의 프로젝트가 마침내 배포(릴리즈)를 위한 준비가 되었다면, cargo build --release를 사용하여 최적화와 함께 이를 컴파일할 수 있습니다.

최적화는 여러분의 러스트 코드를 더 빠르게 만들어주지만, 최적화를 켜는 것은 여러분의 프로그램을 컴파일하는데 드는 시간을 길게 할 것입니다.

### 관례로서의 Cargo
여러분의 프로그램이 점점 더 복잡해질수록 Cargo는 자신의 가치를 증명할 것입니다.

여러 개의 크레이트들로 구성된 복잡한 프로젝트와 함께라면 Cargo가 빌드를 조직화하도록 하는것이 훨씬 쉽습니다.