/*
 * Connection.cpp
 *
 *  Created on: 2020. 2. 21.
 *      Author: taemin.hwang
 */
#include "Connection.h"
#include "linux/in6.h"

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
    else if(ipversion_ == 6) {
        const int off = 0;
        setsockopt(client, IPPROTO_IPV6, IPV6_AUTOFLOWLABEL, &off, sizeof(off));
        client = socket(AF_INET6, SOCK_STREAM, 0);
    }

    if(client == -1)
        ShowError("failed to create client");

    if(is_init_ == false) {
        if(ipversion_ == 4){
            auto addr = IPv4Bind();
            if(connect(client, (sockaddr*)&addr, sizeof(addr)) == -1)
                ShowError("failed to connect");
        }else {
            auto addr = IPv6Bind();
            if(connect(client, (sockaddr*)&addr, sizeof(addr)) == -1) {
                ShowError("failed to connect");
            }
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

    if(user_message == "q" || user_message == "quit") return -1;

    RemoveBlank(user_message);
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

std::vector<bool> Connection::SendMessageStream(std::vector<std::pair<std::string, std::string>> msg_stream) {
    std::vector<bool> ret;
    char send_message[BUFSIZE];
    int step = 1;
    if(is_routed_ == false) {
        SendRouteActivate();
    }

    for(auto str : msg_stream) {
        std::cout << "\033[1;33m*** STEP " << step++ << " ***\033[0m" << std::endl;
        memset(send_message, 0, sizeof(send_message));
        RemoveBlank(str.first);
        MakeCapital(str.first);
        RemoveBlank(str.second);
        MakeCapital(str.second);

        std::string uds_message = doip_connection->AddDoIpHeader(str.first);
        int size = doip_connection->HexStr2Arr(send_message, BUFSIZE, uds_message);

        std::cout << "[Send UDS Message    ] : " << str.first << std::endl;
        send(client, send_message, size, 0);

        doip_connection->ParseUDS(str.first);
        std::cout << std::endl;
        ret.push_back(RecvMessage(str.second));
    }
    return ret;
}

int Connection::RecvMessage(std::string testcase) {
    int ret = 0;
    char recv_message[BUFSIZE];
    memset(recv_message, 0, sizeof(recv_message));

    int rcv = recv(client, recv_message, sizeof(recv_message)-1, 0);
    if(is_routed_ == true) {
        rcv = recv(client, recv_message, sizeof(recv_message)-1, 0);
    }

    if(rcv == -1) {
        ShowError("failed to receive message from DM");
    } else if(rcv == 0) {
        ShowError("disconnected to DM");
    } else {
        recv_message[rcv] = '\0';
        std::string rcv_message = doip_connection->ParseDoIpHeader(recv_message, rcv);
        std::cout << "[Received uds message] : " << rcv_message << std::endl;
        if(is_routed_) doip_connection->ParseUDS(std::string(rcv_message));

        std::string tc_response;
        auto pos = testcase.find('*');
        if(pos != std::string::npos) {
            tc_response = testcase.substr(0, pos-1);
            rcv_message = rcv_message.substr(0, pos-1);
        } else {
            tc_response = testcase;
        }

        if(rcv_message != tc_response) {
            std::cout << "\033[1;31mFAIL\033[0m" << std::endl;
            ret = 0;
        } else {
            std::cout << "\033[1;32mPASS\033[0m " << std::endl;
            ret = 1;
        }
    }
    return ret;
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
    } else if(rcv == 0) {
        ShowError("disconnected to DM");
    } else {
        recv_message[rcv] = '\0';
        std::string rcv_message = doip_connection->ParseDoIpHeader(recv_message, rcv);
        std::cout << "[Received uds message] : " << rcv_message << std::endl;
        if(is_routed_) doip_connection->ParseUDS(std::string(rcv_message));
    }
    return rcv;
}

void Connection::ShowError(std::string msg) {
    perror(msg.c_str());
    exit(1);
}

} /* namespace transport */
