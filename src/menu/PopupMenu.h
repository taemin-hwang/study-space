#ifndef _POPUPMENU_H_
#define _POPUPMENU_H_

#include <vector>
#include "menu/BaseMenu.h"

using BaseMenuPtr = std::shared_ptr<BaseMenu>;

class PopupMenu : public BaseMenu {
public:
    PopupMenu(std::string s) : BaseMenu(s){}
    virtual ~PopupMenu(){};
    void addMenu(BaseMenuPtr p) {menus.push_back(p);}
    void command() {
        while(1) {
            std::cout << "=====================================================================" << std::endl;
            int cmd;
            int sz = menus.size();
            for(int i = 0 ; i < sz; i++) {
                std::cout << "[" << i+1 << "] " << menus[i]->getTitle() << std::endl;
                //connection_manager_->Run();
            }
            std::cout << "[" << sz+1 << "] " << "BACK" << std::endl;
            std::cout << "Select Menu : ";
            std::cin >> cmd;

            if(cmd < 1 || cmd > sz+1) continue;
            else if(cmd == sz + 1) break;
            else {
                menus[cmd-1]->command();
            }
        }
    }
    BaseMenuPtr getSubMenu(int idx) {
        return menus[idx];
    }
private:
    std::vector<BaseMenuPtr> menus;
};

#endif
