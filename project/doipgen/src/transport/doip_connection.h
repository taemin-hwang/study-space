/*
 * DoipConnection.h
 *
 *  Created on: 2020. 2. 26.
 *      Author: taemin.hwang
 */

#ifndef SRC_TRANSPORT_DOIPCONNECTION_H_
#define SRC_TRANSPORT_DOIPCONNECTION_H_

#include <string>
#include <map>

namespace transport {

class DoipConnection {
public:
    DoipConnection();
    virtual ~DoipConnection();
    std::string AddDoIpHeader(std::string msg);
    std::string ParseDoIpHeader(char* msg, int size);
    std::string GetRouteActivationMsg();
    int HexStr2Arr(char* message, int sz, std::string s);
    std::string ParseUDS(std::string msg);

private:
    template <typename T>
    std::string int2hex(T i);
    unsigned long hex2dec(std::string hex);
    inline void SetTargetAddress(std::string ta_) {this->ta = ta_;}
    void InitializeTable();

private:
    std::string protocol_version = "02";
    std::string inverse_version = "fd";
    std::string diagnostic_event = "8001";
    std::string routing_activate = "0005";
    std::string sa = "1212";
    std::string ta = "0000";
    std::map<std::string, std::string> req_sid_table;
    std::map<std::string, std::string> res_sid_table;
    std::map<std::string, std::string> nrc_table;

};
} /* namespace transport */

#endif /* SRC_TRANSPORT_DOIPCONNECTION_H_ */
