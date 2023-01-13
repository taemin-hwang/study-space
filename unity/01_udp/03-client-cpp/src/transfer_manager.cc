#include "transfer_manager.h"
#include <iostream>
#include <ctime>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <unistd.h>

void TransferManager::Initialize() {
    sock_ = socket(AF_INET, SOCK_DGRAM, 0);
    memset(&serv_addr_, 0, sizeof(serv_addr_));
    serv_addr_.sin_family=AF_INET;
    serv_addr_.sin_addr.s_addr=inet_addr(ip_addr_.c_str());
    serv_addr_.sin_port=htons(port_);
}

void TransferManager::SendData(const std::string& direction) {
    char message[65535];

    rapidjson::Document document;
    document.SetObject();
    rapidjson::Document::AllocatorType& allocator = document.GetAllocator();

    rapidjson::Value str_direction;
    str_direction.SetString(direction.c_str(), direction.length(), allocator);

    document.AddMember("direction", str_direction, allocator);
    rapidjson::StringBuffer strbuf;
    rapidjson::Writer<rapidjson::StringBuffer> writer(strbuf);
    document.Accept(writer);

    std::string ret = strbuf.GetString();

    std::cout << ret << std::endl;
    ret.copy(message, strlen(ret.c_str()));

    int perr = sendto(sock_, message, strlen(ret.c_str()), 0, (sockaddr*)&serv_addr_, sizeof(serv_addr_));
    if (perr < 0) {
        std::cout << "failed to send data to UDP server" << std::endl;
    }
}

void TransferManager::Shutdown() {

}