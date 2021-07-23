#include "MyLibraries/my_library_a.hpp"
#include "SomeLibraries/some_library_a.hpp"
#include "SomeLibraries/some_library_b.hpp"

int main() {
    MyLibrary::print();
    LibraryA::print();
    // LibraryB::print(); // undefined reference to `LibraryB::print()
}
