/*
 * ConnectionManager.cpp
 *
 *  Created on: 2020. 2. 21.
 *      Author: taemin.hwang
 */

#include "connection_manager.h"

namespace transport {

ConnectionManager::ConnectionManager(std::string s = "../etc/Config.json") {
    config_parser_ = std::make_unique<parser::ConfigParser>(s);
    Config cfg_ = config_parser_->getCfg();

    connection_ = std::make_unique<Connection>(cfg_);
    reporter_ = std::make_unique<report::Reporter>();
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

void ConnectionManager::SendMessageStream(std::string testname, std::vector<std::pair<std::string, std::string>> testcase) {
    reporter_->WriteReport(testname, connection_->SendMessageStream(testcase));
}

} /* namespace transport */
