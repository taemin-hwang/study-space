#include <iostream>
#include <string>
#include <algorithm>
#include <functional>

using namespace std;

int main() {
    std::string in = "Just please take care of me. Please take me all for you";
    std::string needle = "me";

    // auto it = std::search(in.begin(), in.end(), std::default_searcher(needle.begin(), needle.end()));
    auto it = std::search(in.begin(), in.end(), std::boyer_moore_searcher(needle.begin(), needle.end()));

    if(it != in.end()) cout << in.substr(it - in.begin()) << endl; // me. Please take me all for you

}
