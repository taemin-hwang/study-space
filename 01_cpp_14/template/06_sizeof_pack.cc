#include <iostream>

using namespace std;

// base function for recursive call
int sum_all() { return 0; }

template <typename... Ints>
int sum_all(int num, Ints... nums) {
    return num + sum_all(nums...);
}

template <typename... Ints>
double average(Ints... nums) {
    return static_cast<double>(sum_all(nums...)) / sizeof...(nums);
}

int main() {
    cout << average(1, 4, 2, 3, 10) << endl;
    // double average(1, 4, 2, 3, 10)
    // sum_all(1, 4, 2, 3, 10) / sizeof...(nums)
    // 1 + sum_all(4, 2, 3, 10) / 5
    // 1 + 4 + sum_all(2, 3, 10) / 5
    // ...
    // 1 + 4 + 2 + 3 + 10 / 5 = 4
}
