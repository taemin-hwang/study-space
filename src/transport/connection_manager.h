/*
 * ConnectionManager.h
 *
 *  Created on: 2020. 2. 21.
 *      Author: taemin.hwang
 */

#ifndef SRC_TRANSPORT_CONNECTIONMANAGER_H_
#define SRC_TRANSPORT_CONNECTIONMANAGER_H_

#include <memory>
#include <string>
#include "parser/config_parser.h"
#include "parser/config.h"
#include "transport/connection.h"
#include "report/reporter.h"
#include "report/test_result.h"

namespace transport {

class ConnectionManager {
public:
    ConnectionManager(std::string s);
    virtual ~ConnectionManager();

    void Initialize();
    void Run();
    void Shutdown();
    void SendMessageStream(std::string, std::vector<std::pair<std::string, std::string>>);
private:
    std::unique_ptr<Connection> connection_;
    std::unique_ptr<parser::ConfigParser> config_parser_;
    std::unique_ptr<report::Reporter> reporter_;
    std::string address_;
    int port_;
};

} /* namespace transport */

#endif /* SRC_TRANSPORT_CONNECTIONMANAGER_H_ */
