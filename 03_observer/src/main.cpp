#include <iostream>
#include <vector>
#include <memory>

using namespace std;

class Observer {
public:
    virtual void notify(int data) = 0;
};

class ConcreteObserverA : public Observer {
public:
    void notify(int data) {
        cout << "A notified : " << data << endl;
    }
};

class ConcreteObserverB : public Observer {
public:
    void notify(int data) {
        cout << "B notified : " << data << endl;
    }
};

class Subject {
private:
    std::vector<Observer*> observers;
public:
    void addObserver(Observer* observer);
    void removeObserver(Observer* observer);
    void notifyObservers(int data);
};

void Subject::addObserver(Observer* observer) {
    observers.push_back(observer);
}

void Subject::removeObserver(Observer* observer) {
    for(auto it = observers.begin(); it != observers.end(); ++it) {
        if(*it == observer) {
            observers.erase(it);
            break;
        }
    }
}

void Subject::notifyObservers(int data) {
    for(auto p : observers) {
        if(p != nullptr) {
            p->notify(data);
        }
    }
}

int main() {
    Subject subject;
    ConcreteObserverA a;
    ConcreteObserverB b;

    // attache subscriber
    subject.addObserver(&a);
    subject.addObserver(&b);

    // broadcast data to subscribers
    subject.notifyObservers(10);
}
