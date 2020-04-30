// https://docs.microsoft.com/ko-kr/cpp/cpp/move-constructors-and-move-assignment-operators-cpp
#include <iostream>
#include <vector>
#include <cstring>
#include <functional>

using namespace std;

class String {
public:
    String() { str = nullptr; }

    String(const char* str_) {
        cout << "constructor" << endl;
        str = new char[strlen(str_) + 1];
        strcpy(str, str_);
    }

    ~String() {
        cout << __func__ << endl;
        delete[] str;
    }

    String(const String& a) {
        cout << "copy constructor" << endl;
        str = new char[strlen(a.str) + 1];
        strcpy(str, a.str);
    }

    String& operator=(const String& a) {
        cout << "copy assignment operator" << endl;
        if(this != &a) {
            delete[] str;
            str = new char[strlen(a.str) + 1];
            strcpy(str, a.str);
        }
        return *this;
    }

    String(String && a) {
        cout << "move constructor" << endl;
        str = a.str;
        a.str = nullptr;
        // *this = std::move(a); // move assignment operator
    }

    String& operator=(String&& a) {
        cout << "move assignement operator" << endl;
        if(this != &a) {
            delete[] str;
            str = a.str;
            a.str = nullptr;
        }
        return *this;
    }

    void ShowString() {
        if(str == nullptr) {
            //throw std::runtime_error("nullptr exception");
            cerr << "function ignored, nullptr called" << endl;
            return;
        }
        cout << str << endl;
    }

private:
    char* str;
};

// std::move takes an object and allows you to treat it as a temporary (an rvalue)
int main() {
    String s1("hello");
    String s2(s1);
    String s3 = std::move(String("world")); // type casting to rvalue

    s1.ShowString();
    s2.ShowString();
    s3.ShowString();
}
