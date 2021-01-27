#include "my_libraries/my_library_a.hpp"
#include "SomeLibraries/some_library_a.hpp"

void MyLibrary::print() {
    LibraryA la;
    std::cout << "MyLibrary" << std::endl;
    la.print();
}