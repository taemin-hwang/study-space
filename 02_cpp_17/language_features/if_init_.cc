#include <iostream>
#include <map>

using namespace std;

int main() {
    std::map<std::string, int> map;
    map["hello"] = 1;
    map["world"] = 2;

    if(auto ret = map.insert({"hello", 3}); ret.second != true) {
        std::cout << "hello already exists with value " << ret.first->second << endl;
    }
}
