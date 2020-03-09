/*
 * ConnectionManager.cpp
 *
 *  Created on: 2020. 2. 21.
 *      Author: taemin.hwang
 */

#include "ConnectionManager.h"

namespace transport {

ConnectionManager::ConnectionManager(std::string s = "../etc/Config.json") {
    config_parser_ = std::make_unique<parser::ConfigParser>(s);
    Config cfg_ = config_parser_->getCfg();
    connection_ = std::make_unique<Connection>(cfg_);
}

ConnectionManager::~ConnectionManager() {

}

void ConnectionManager::Initialize() {
    connection_->Initialize();
}

void ConnectionManager::Run() {
    connection_->Run();
}

void ConnectionManager::Shutdown() {
    connection_->Shutdown();
}

void ConnectionManager::SendMessageStream(std::vector<std::pair<std::string, std::string>> testcase) {
    connection_->SendMessageStream(testcase);
}

} /* namespace transport */
