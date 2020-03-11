/*
 * DoipSimulator.cpp
 *
 *  Created on: 2020. 2. 21.
 *      Author: taemin.hwang
 */

#include "DoipSimulator.h"

DoipSimulator::DoipSimulator(std::string s = "../etc/config.json") {
    connection_manager_ = std::make_shared<transport::ConnectionManager>(s);
    preset_parser_ = std::make_unique<parser::PresetParser>("../etc/preset.json");
}

DoipSimulator::~DoipSimulator() {

}

void DoipSimulator::Initialize() {
    std::cout << __func__ << std::endl;
    connection_manager_->Initialize();

    base_ = std::make_shared<PopupMenu>("MENU");
    PopupMenuPtr test = std::make_shared<PopupMenu>("TEST");
    PopupMenuPtr setting = std::make_shared<PopupMenu>("SETTING");
    MenuItemPtr preset = std::make_shared<MenuItem>("PRESET", 1);
    MenuItemPtr user = std::make_shared<MenuItem>("USER DEFINED", 2);
    MenuItemPtr create_preset = std::make_shared<MenuItem>("CREATE PRESET", 3);
    MenuItemPtr delete_preset = std::make_shared<MenuItem>("DELETE PRESET", 4);

    user->setFunction([=](){ connection_manager_->Run(); });
    create_preset->setFunction([=]() { preset_parser_->CreatePreset();});
    preset->setFunction([=]() {
        std::vector<std::pair<std::string, std::string>> testcase = preset_parser_->SelectPreset();
        if(testcase.size() > 0) {
            connection_manager_->SendMessageStream(testcase);
        }
    });
    delete_preset->setFunction([=]() {
        preset_parser_->DeletePreset();
    });

    base_->addMenu(test);
    base_->addMenu(setting);

    test->addMenu(preset);
    test->addMenu(user);

    setting->addMenu(create_preset);
    setting->addMenu(delete_preset);
}

void DoipSimulator::Run() {
    std::cout << __func__ << std::endl;
    base_->command();
    //connection_manager_->Run();
}

void DoipSimulator::Shutdown() {
    std::cout << __func__ << std::endl;
    connection_manager_->Shutdown();
}

