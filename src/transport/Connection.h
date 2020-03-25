/*
 * Connection.h
 *
 *  Created on: 2020. 2. 21.
 *      Author: taemin.hwang
 */

#ifndef SRC_TRANSPORT_CONNECTION_H_
#define SRC_TRANSPORT_CONNECTION_H_
#include <iostream>
#include <string>
#include <cstring>
#include <memory>
#include <cstdio>
#include <vector>
#include <map>
#include <algorithm>
#include <locale>
#include "unistd.h"

#include "parser/Config.h"
#include "sys/types.h"
#include "sys/socket.h"
#include "netinet/in.h"
#include "arpa/inet.h"

#include "DoipConnection.h"

#define BUFSIZE 1024

namespace transport {

class Connection {
public:
    Connection(Config cfg);
    virtual ~Connection();
    void Initialize();
    void Run();
    void Shutdown(){}
    void SendMessageStream(std::vector<std::pair<std::string, std::string>> msg_stream);

private:
    inline void RemoveBlank(std::string& msg){msg.erase(std::remove(msg.begin(), msg.end(), ' '), msg.end());};
    inline void MakeCapital(std::string& msg){std::transform(msg.begin(), msg.end(), msg.begin(), ::toupper);}
    void ShowError(std::string msg);
    void SendRouteActivate();
    int SendUDSMessage();
    int RecvMessage();
    int RecvMessage(std::string);
    sockaddr_in IPv4Bind() {
        sockaddr_in addr = {0};
        addr.sin_family = AF_INET;
        addr.sin_addr.s_addr = inet_addr(ipaddr_.c_str());
        addr.sin_port = htons(port_);
        return addr;
    }
    sockaddr_in6 IPv6Bind() {
        sockaddr_in6 addr = {0};
        addr.sin6_family = AF_INET6;
        inet_pton(AF_INET6, ipaddr_.c_str(), &(addr.sin6_addr));
        addr.sin6_port = htons(port_);
        addr.sin6_flowinfo = 0;
        return addr;
    }

private:
    int client;
    std::unique_ptr<transport::DoipConnection> doip_connection;
    std::string ipaddr_;
    int ipversion_;
    int port_;
    bool is_routed_ = false;
    bool is_init_ = false;
};

} /* namespace transport */

#endif /* SRC_TRANSPORT_CONNECTION_H_ */
