#include <iostream>
#include <map>
#include <optional>

using namespace std;

std::map<string, int> options;

// std::optional<T>
// return value or std::nullopt;
std::optional<int> get_option(const char* name) {
    auto match = options.find(name);
    if(match != options.end()) {
        return match->second;
    } else {
        return std::nullopt; // return {};
    }
}

int main() {
    options.insert({"hello", 1});
    options.insert({"world", 2});

    auto val = get_option("zello");
    if(val) {
        std::cout << *val << std::endl;
    } else {
        std::cout << "not exist" << std::endl;
    }

    // has_value
    val = get_option("hello");
    if(val.has_value()) {
        std::cout << *val << std::endl;
    } else {
        std::cout << "not exist" << std::endl;
    }

    // value_or
    std::cout << get_option("world").value_or(0) << std::endl;
    std::cout << get_option("yorld").value_or(0) << std::endl;
}
