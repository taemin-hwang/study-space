#include <iostream>
#include <type_traits>

using namespace std;

#if type_deduction
template <typename T>
void show_value(T t) {
    cout << "Not pointer : " << t  << endl;
}

template <typename T>
void show_value(T* t) {
    cout << "Pointer : " << *t << endl;
}
#endif

// if constexpr
// In a constexpr if statement, the value of condition must be a contextually converted constant expression of type bool.
// If the value is true, then statement-false is discarded (if present), otherwise, statement-true is discarded.

template <typename T>
void show_value(T t) {
    if constexpr (std::is_pointer<T>::value) {
        cout << "Pointer : " << *t << endl;
    } else {
        cout << "Not pointer : " << t << endl;
    }
}

int main() {
    int x = 3;
    int* p = &x;
    show_value(x);
    show_value(p);
}
