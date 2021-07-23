#include <iostream>

// fold expression
// (E op ...)       | (e1 + (e2 + (e3 + (e4 ... ))))
// (... op E)       | ((((e1 + e2) + e3) + e4) ... )
// (E op ... op I)  | (I + (e1 + (e2 + (e3 + (e4 ... )))))
// (I op ... op E)  | ((((e1 + e2) + e3) + e4) ... + I )


using namespace std;

// left fold is more easier to understand

template <typename... Ints>
int sum_all(Ints... nums) {
    return (... + nums);
}

template <typename... doubles>
double sub(doubles... args) {
    return (10 - ... - args);
    // 10 - 1 - 2 - 3 - 4
}

int main() {
    cout << sum_all(1, 4, 2, 3, 10) << endl;
    cout << sub(1, 2, 3, 4) << endl;
}
