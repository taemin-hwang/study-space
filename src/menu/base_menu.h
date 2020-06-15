#ifndef __BASEMENU_H_
#define __BASEMENU_H_

#include <string>
#include <memory>
#include <iostream>

class BaseMenu {
public:
    BaseMenu(std::string s) : title(s) {}
    virtual ~BaseMenu(){}
    std::string getTitle() const {return title;}
    virtual std::shared_ptr<BaseMenu> getSubMenu(int idx) { return nullptr;}
    virtual void addMenu(std::shared_ptr<BaseMenu> p) {
        std::cout << "ERROR" << std::endl;
    }
    virtual void command() = 0;
protected:
    std::string title;
};


#endif
