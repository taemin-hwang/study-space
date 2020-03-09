#ifndef __MENUITEM_H_
#define __MENUITEM_H_

#include <iostream>
#include <string>
#include <functional>
#include "menu/BaseMenu.h"

class MenuItem : public BaseMenu {
    int id;
public:
    MenuItem(std::string s, int n) : BaseMenu(s), id(n) {}
    virtual ~MenuItem(){};
    void command() {
        if(f != nullptr)
            f();
        else
            std::cout << "Execution not exist" << std::endl;
    }
    void setFunction(std::function<void()> f_) { f = f_; }

private:
    std::function<void()> f;
};

#endif
