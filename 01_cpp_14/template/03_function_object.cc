// Functors are objects that can be treated as though they are a function or function pointer.
// Functors are most commonly used along with STL.
// * operator() overloading

// Functor (Function Object) vs. Function Pointer
// Function Pointer is a legacy of C language
// Functor is encapsulation of function. i.e. Functor is a generic of function pointer
// Functor could be parameter of template
// Functor supports inlining, reducing the overhead of jumping to a new function and returning

#include <iostream>
#include <algorithm>

using namespace std;

// how to pass information to a function which take only one argument?

class increment {
 public:
    increment(int n) : num(n) {}
    int operator() (int arr_num) const {
        return num + arr_num;
    }
 private:
    int num;
};

int main() {
    int arr[] = {1, 2, 3, 4, 5};
    int n = sizeof(arr)/sizeof(arr[0]);

    transform(arr, arr+n, arr, increment(1));
    for(auto p : arr) {
        cout << p << " ";
    }
    cout << endl;

    transform(arr, arr+n, arr, increment(5));
    for(auto p : arr) {
        cout << p << " ";
    }
    cout << endl;
}


#if function_pointer

int increment_1(int x) { return (x + 1); }
int increment_5(int x) { return (x + 5); }

int main() {
    int arr[] = {1, 2, 3, 4, 5};
    int n = sizeof(arr)/sizeof(arr[0]);

    // transform(inputit first, inputit last, outputit d, operation op)
    // transform inputit to outputit with operation
    transform(arr, arr+n, arr, increment_1);

    for(int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;

}

#endif
