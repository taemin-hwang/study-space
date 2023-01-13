#include <iostream>
#include <string>
#include <thread>
#include <chrono>

#include "transfer_manager.h"

using namespace std;

std::string get_direction(const int& dir) {
    std::string ret = "";
    switch(dir) {
        case 0:
            ret = "up";
            break;
        case 1:
            ret = "down";
            break;
        case 2:
            ret = "left";
            break;
        case 3:
            ret = "right";
            break;
        default:
            break;
    }
    return ret;
}

int main() {
    std::cout << "hello world" << std::endl;

    auto transfer_manager_ = std::make_unique<TransferManager>("127.0.0.1", 50002);
    transfer_manager_->Initialize();

    while(true) {
        int direction = -1;
        std::cout << "Enter direction (0:up, 1:down, 2:left, 3:right): ";
        std::cin >> direction;

        if(direction >= 0 && direction <= 3) {
            auto direction_str = get_direction(direction);
            transfer_manager_->SendData(direction_str);
        } else {
            std::cout <<"Direction must be included between 0 and 3 : " << direction << std::endl;
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}
