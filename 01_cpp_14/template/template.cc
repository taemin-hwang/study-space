#include <iostream>
#include <string>

// Now, we can send "type", not "variable" to class or function
template <typename T>
class mVector {
    T* data;
    int capacity;
    int length;

public:
    mVector(int n = 1) : data(new T[n]), capacity(n), length(0) {}
    virtual ~mVector() { if(data) { delete[] data; } }

    void push_back(T s) {
        if(capacity <= length) {
            T* temp = new T[capacity * 2];
            for (int i = 0 ; i < length ; i++) {
                temp[i] = data[i];
            }
            delete[] data;
            data = temp;
            capacity *= 2;
        }

        data[length] = s;
        length++;
    }

    T operator[](int i) { return data[i]; }

    void remove(int x) {
        for(int i = x + 1; i < length; i++) {
            data[i-1] = data[i];
        }
        length--;
    }

    int size() { return length; }
};

int main() {
    // class template instantiation
    mVector<int> int_vec;
    int_vec.push_back(3);
    int_vec.push_back(2);

    for(int i = 0 ; i < int_vec.size(); i++) {
        std::cout << int_vec[i] << std::endl;
    }

    mVector<std::string> str_vec;
    str_vec.push_back("hello");
    str_vec.push_back("drawing");

    for(int i = 0 ; i < str_vec.size(); i++) {
        std::cout << str_vec[i] << std::endl;
    }
}
