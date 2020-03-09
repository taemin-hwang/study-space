/*
 * Connection.cpp
 *
 *  Created on: 2020. 2. 21.
 *      Author: taemin.hwang
 */
#include <vector>
#include <algorithm>
#include <locale>
#include <cstring>
#include "Connection.h"

namespace transport {

Connection::Connection(Config cfg) {
    doip_connection = std::make_unique<DoipConnection>();
    port_ = cfg.port;
    ipaddr_= cfg.ipaddr;
    ipversion_ = cfg.ipversion;

    if(ipversion_ != 4 && ipversion_ != 6) {
        ShowError("Wrong ip version assigend");
    } else {
        if(ipversion_ == 4 && find(ipaddr_.begin(), ipaddr_.end(), ':') != ipaddr_.end())
            ShowError("IP address and version mismatched");
        else if(ipversion_ == 6 && find(ipaddr_.begin(), ipaddr_.end(), '.') != ipaddr_.end())
            ShowError("IP address and version mismatched");
    }
    std::cout << "[IP     ] " << ipaddr_ << std::endl;
    std::cout << "[VERSION] " << ipversion_ << std::endl;
    std::cout << "[PORT   ] " << port_ << std::endl;
}

Connection::~Connection() {
    close(client);
}

void Connection::Run() {
    std::cout << "Connection Running" << std::endl;

    if(is_routed_ == false) {
        std::cout << "=====================================================================" << std::endl;
        SendRouteActivate();
    }

    while(1) {
        std::cout << "=====================================================================" << std::endl;
        if(SendUDSMessage() == -1) return;
    }
}

void Connection::Initialize() {
    std::cout << "Creating Socket" << std::endl;
    if(ipversion_ == 4)
        client = socket(AF_INET, SOCK_STREAM, 0);
    else if(ipversion_ == 6)
        client = socket(AF_INET6, SOCK_STREAM, 0);

    if(client == -1)
        ShowError("failed to create client");

    if(is_init_ == false) {
        if(ipversion_ == 4){
            auto addr = IPv4Bind();
            if(connect(client, (sockaddr*)&addr, sizeof(addr)) == -1)
                ShowError("failed to connect");
        }else {
            auto addr = IPv6Bind();
            if(connect(client, (sockaddr*)&addr, sizeof(addr)) == -1)
                ShowError("failed to connect");
        }
        is_init_ = true;
    }
}

void Connection::SendRouteActivate() {
    char send_message[BUFSIZE];
    std::string route_activation = doip_connection->GetRouteActivationMsg();
    int size = doip_connection->HexStr2Arr(send_message, BUFSIZE, route_activation);

    std::cout << "[Routing Activation  ] : " << route_activation  << std::endl;
    send(client, send_message, size, 0);
    if(RecvMessage() != -1) is_routed_ = true;
}

int Connection::SendUDSMessage() {
    char send_message[BUFSIZE];
    std::string user_message;

    std::cout << "[Enter uds message   ] : ";
    while(1) {
        std::getline(std::cin, user_message);
        if(user_message != "") break;
    }
    //std::cin.ignore();

    if(user_message == "q" || user_message == "quit") return -1;

    user_message.erase(std::remove(user_message.begin(), user_message.end(), ' '), user_message.end());
    std::string uds_message = doip_connection->AddDoIpHeader(std::string(user_message));
    int size = doip_connection->HexStr2Arr(send_message, BUFSIZE, uds_message);

    if(send(client, send_message, size, 0) == -1) {
        ShowError("failed to send message");
    }
    doip_connection->ParseUDS(user_message);
    std::cout << std::endl;
    RecvMessage();

    return 0;
}

void Connection::SendMessageStream(std::vector<std::pair<std::string, std::string>> msg_stream) {
    char send_message[BUFSIZE];
    int step = 1;
    if(is_routed_ == false) {
        SendRouteActivate();
    }

    for(auto str : msg_stream) {
        std::cout << "\033[1;33m*** STEP " << step++ << " ***\033[0m" << std::endl;
        memset(send_message, 0, sizeof(send_message));
        str.first.erase(std::remove(str.first.begin(), str.first.end(), ' '), str.first.end());
        str.second.erase(std::remove(str.second.begin(), str.second.end(), ' '), str.second.end());
        std::transform(str.first.begin(), str.first.end(), str.first.begin(), ::toupper);
        std::transform(str.second.begin(), str.second.end(), str.second.begin(), ::toupper);

        std::string uds_message = doip_connection->AddDoIpHeader(str.first);
        int size = doip_connection->HexStr2Arr(send_message, BUFSIZE, uds_message);

        std::cout << "[Send UDS Message    ] : " << str.first << std::endl;
        send(client, send_message, size, 0);

        doip_connection->ParseUDS(str.first);
        std::cout << std::endl;
        RecvAndCheckMessage(str.second);
    }
}

int Connection::RecvAndCheckMessage(std::string testcase) {
    char recv_message[BUFSIZE];
    memset(recv_message, 0, sizeof(recv_message));

    int rcv = recv(client, recv_message, sizeof(recv_message)-1, 0);
    if(is_routed_ == true) {
        rcv = recv(client, recv_message, sizeof(recv_message)-1, 0);
    }

    if(rcv == -1) {
        ShowError("failed to receive message from DM");
    } else {
        recv_message[rcv] = '\0';
        std::string rcv_message = doip_connection->ParseDoIpHeader(recv_message, rcv);
        std::cout << "[Received uds message] : " << rcv_message << std::endl;
        if(is_routed_) doip_connection->ParseUDS(std::string(rcv_message));
        if(rcv_message != testcase) {
            std::cout << "\033[1;31mFAIL\033[0m" << std::endl;
        } else {
            std::cout << "\033[1;32mPASS\033[0m " << std::endl;
        }
    }
    return rcv;
}
int Connection::RecvMessage() {
    char recv_message[BUFSIZE];
    memset(recv_message, 0, sizeof(recv_message));

    int rcv = recv(client, recv_message, sizeof(recv_message)-1, 0);
    if(is_routed_ == true) {
        rcv = recv(client, recv_message, sizeof(recv_message)-1, 0);
    }

    if(rcv == -1) {
        ShowError("failed to receive message from DM");
    } else {
        recv_message[rcv] = '\0';
        std::string rcv_message = doip_connection->ParseDoIpHeader(recv_message, rcv);
        std::cout << "[Received uds message] : " << rcv_message << std::endl;
        if(is_routed_) doip_connection->ParseUDS(std::string(rcv_message));
    }
    return rcv;
}

void Connection::ShowError(std::string msg) {
    std::cout << msg << std::endl;
    exit(1);
}

} /* namespace transport */
