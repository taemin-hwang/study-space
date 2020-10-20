#include <iostream>

// fold expression
// (E op ...)       | (num + ...)       |
// (... op E)       | (... + num)       |
// (E op ... op I)  | (num + ... + args)|
// (I op ... op E)


using namespace std;

template <typename... Ints>
int sum_all(Ints... nums) {
    return (... + nums);
}

int main() {
    cout << sum_all(1, 4, 2, 3, 10) << std::endl;
}
