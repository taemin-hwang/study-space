#include <iostream>

template <typename T>
class Vector {
  T* data;
  int capacity;
  int length;

 public:
  typedef T value_type;

  Vector(int n = 1) : data(new T[n]), capacity(n), length(0) {}

  void push_back(int s) {
    if (capacity <= length) {
      int* temp = new T[capacity * 2];
      for (int i = 0; i < length; i++) {
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
    for (int i = x + 1; i < length; i++) {
      data[i - 1] = data[i];
    }
    length--;
  }

  int size() { return length; }

  void swap(int i, int j) {
    T temp = data[i];
    data[i] = data[j];
    data[j] = temp;
  }

  ~Vector() {
    if (data) {
      delete[] data;
    }
  }
};

template <typename Cont>
void bubble_sort(Cont& cont) {
    for(int i = 0 ; i < cont.size(); i++) {
        for(int j = i + 1; j < cont.size(); j++) {
            if(cont[i] > cont[j]) {
                cont.swap(i, j);
            }
        }
    }
}

// NOTE: Comp is a instance, not function
template <typename Cont, typename Comp>
void bubble_sort(Cont& cont, Comp& comp) {
    for(int i = 0; i < cont.size(); i++) {
        for(int j = i + 1; j < cont.size(); j++) {
            if(!comp(cont[i], cont[j])) cont.swap(i, j);
        }
    }
}

class Comp1 {
public:
    bool operator() (int a, int b) { return a > b; }
};

class Comp2 {
public:
    bool operator() (int a, int b) { return a < b; }
};

int main() {
    Comp1 comp1;
    Comp2 comp2;

    Vector<int> int_vec;
    int_vec.push_back(1);
    int_vec.push_back(5);
    int_vec.push_back(2);
    int_vec.push_back(7);

    bubble_sort(int_vec, comp1);

    for(int i = 0 ; i < int_vec.size(); i++) {
        std::cout << int_vec[i] << std::endl;
    }

    bubble_sort(int_vec, comp2);

    for(int i = 0 ; i < int_vec.size(); i++) {
        std::cout << int_vec[i] << std::endl;
    }
}

