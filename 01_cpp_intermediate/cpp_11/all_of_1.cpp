#include <iostream>
#include <algorithm>

int main() {
    std::string s1 = "1000*";
    std::string s2 = "1000X";


    if(!std::all_of(s1.begin(), s1.end(), [](char ch) {
        std::cout << ch << std::endl; return ::isxdigit(ch) || ch == '*'; } )) {

        std::cout << "ERROR " << std::endl;
    }

    if(!std::all_of(s2.begin(), s2.end(), [](char ch) {
        std::cout << ch << std::endl; return ::isxdigit(ch) || ch == '*'; } )) {

        std::cout << "ERROR " << std::endl;
    }

}
