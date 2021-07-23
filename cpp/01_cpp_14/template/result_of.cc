#include <iostream>
#include <type_traits>

int fn(int) {return int();}
typedef int(&fn_ref)(int);
typedef int(*fn_ptr)(int);
struct fn_class { int operator()(int i) {return i;}};

// template parameters
/*
template<class Fn, class...ArgTypes>
struct result_of<Fn(ArgTypes...)>;
*/
// Fn: A callable type or a reference to a function or a reference to a callable type
// ArgTypes: A list of types, in the same order as in the call

// member types
// type: result type of a call to Fn with arguments of the types specified in ArgTypes

int main() {
    typedef std::result_of<decltype(fn)&(int)>::type A;  // int
    typedef std::result_of<fn_ref(int)>::type B;         // int
    typedef std::result_of<fn_ptr(int)>::type C;         // int
    typedef std::result_of<fn_class(int)>::type D;       // int

    std::cout << std::boolalpha;
    std::cout << "typedefs of int:" << std::endl;

    std::cout << "A: " << std::is_same<int,A>::value << std::endl;
    std::cout << "B: " << std::is_same<int,B>::value << std::endl;
    std::cout << "C: " << std::is_same<int,C>::value << std::endl;
    std::cout << "D: " << std::is_same<int,D>::value << std::endl;
}
