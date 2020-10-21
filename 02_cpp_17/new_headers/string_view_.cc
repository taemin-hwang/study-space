#include <iostream>
#include <string_view>
#include <string>

// std::string_view doesn’t create a copy of the string

using namespace std;

void print_string(const string& s) {
    std::cout << s << std::endl;
}

void print_string_view(const string_view& s) {
    std::cout << s << std::endl;
}

int main() {
    std::string s = "hello world";
    print_string(s);
    print_string("hello world"); // string(const* char)

    print_string_view(s);
    print_string_view("hello world");
}
