#include <iostream>
#include <algorithm>

using namespace std;

// template<class T>
// constexpr const T& clamp( const T& v, const T& lo, const T& hi );

int main() {
    // std::clamp(v, lo, hi)
    // If v compares less than lo, returns lo; otherwise if hi compares less than v, returns hi; otherwise returns v.
    cout << clamp(5, 10, 100) << endl;  // 10  (lo)
    cout << clamp(50, 10, 100) << endl; // 50  (v)
    cout << clamp(300, 10, 100) << endl;// 100 (hi)
}
