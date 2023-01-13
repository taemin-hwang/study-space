#ifndef _TRANSFER_MANAGER_H_
#define _TRANSFER_MANAGER_H_

#include <iostream>
#include <vector>
#include <string>
#include <cstring>

// rapidjson
#include <rapidjson/rapidjson.h>
#include <rapidjson/document.h>
#include <rapidjson/writer.h>
#include <rapidjson/stringbuffer.h>

#include <arpa/inet.h>
#include <sys/socket.h>

class TransferManager {
 public:
    TransferManager(std::string ip_addr, int port) : ip_addr_(ip_addr), port_(port) {}
    virtual ~TransferManager() = default;

    void Initialize();
    void SendData(const std::string& direction);
    void Shutdown();

 private:
    int sock_;
    struct sockaddr_in serv_addr_;
    std::string ip_addr_ = "";
    int port_ = 0;
};

#endif
