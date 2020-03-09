/*
 * main.cc
 *
 *  Created on: 2020. 2. 21.
 *      Author: taemin.hwang
 */

#include <iostream>
#include <memory>
#include <string>
#include "DoipSimulator.h"

std::string path = "../etc/config.json";

int main() {
    std::unique_ptr<DoipSimulator> doip_sim_ = std::make_unique<DoipSimulator>(path);

    doip_sim_->Initialize();
    doip_sim_->Run();
    doip_sim_->Shutdown();

}
