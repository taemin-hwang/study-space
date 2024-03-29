
// 모든 프로그램은 실행하는 동안 컴퓨터의 메모리를 사용하는 방법을 관리해야 합니다.
// 몇몇 언어들은 프로그램이 실행될 때 더이상 사용하지 않는 메모리를 끊임없이 찾는 가비지 콜렉션을 갖고 있습니다. (Java)
// 다른 언어들에서는 프로그래머가 직접 명시적으로 메모리를 할당하고 해제해야 합니다. (C, C++)

// 러스트는 제 3의 접근법을 이용합니다
// 메모리는 컴파일 타임에 컴파일러가 체크할 규칙들로 구성된 소유권 시스템을 통해 관리됩니다

// 소유권이란 개념이 많은 프로그래머들에게 새로운 것이기 때문에,
// 이해하고 사용하는 데에는 약간의 시간이 걸립니다만,
// 좋은 소식은 여러분이 러스트와 소유권 시스템의 규칙에 더 많은 경험을 할수록,
// 여러분은 더 안전하고 더 효율적인 코드를 자연스럽게 개발할 수 있게될 것이라는 거죠. 견뎌내세요

// 코드의 어느 부분이 힙의 어떤 데이터를 사용하는지 추적하는 것,
// 힙의 중복된 데이터의 양을 최소화하는 것,
// 그리고 힙 내에 사용하지 않는 데이터를 제거하여 공간이 모자라지 않게 하는 것은 모두 소유권과 관계된 문제들입니다.
// 여러분이 소유권을 이해하고 나면,
// 여러분은 더이상 스택과 힙에 대한 생각이 자주 필요치 않게 될겁니다만,
// 힙 데이터를 관리하는 것이 곧 소유권의 존재 이유임을 알게 되는 것은 이것이 어떤 방식으로 작동하는지 설명하는데 도움을 줄 수 있습니다.

// Code 영역: 실행할 프로그램의 코드
// Data 영역: 전역변수, 정적변수
// Heap 영역: 사용자의 동적 할당 (런타임에 크기가 결정됨, 사용자가 직접 관리, 느린 액세스)
// Stack 영역: 지역변수, 매개변수 (컴파일 타임에 크기가 결정됨: OS 따라 스택 크기가 제한됨)

fn main() {
    println!("Hello, world!");
}
