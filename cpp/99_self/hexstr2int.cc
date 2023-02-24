#include <sstream>
#include <iostream>

using namespace std;

int main() {
    unsigned int x;
    unsigned char y;
    int z;
    std::stringstream ss;
    ss << std::hex << "a1";
    ss >> x;

    ss << std::hex << "a1";
    ss >> z;


    y = (unsigned char)x;
    std::cout << static_cast<unsigned int>(x) << std::endl;
    std::cout << static_cast<unsigned char>(y) << std::endl;
    std::cout << static_cast<unsigned int>(y) << std::endl;
    std::cout << (int)strtol("a1", NULL, 16) << std::endl;

}
