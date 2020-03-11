/*
 * DoipConnection.cpp
 *
 *  Created on: 2020. 2. 26.
 *      Author: taemin.hwang
 */
#include <iostream>
#include <iomanip>
#include <sstream>
#include <algorithm>
#include <cstring>
#include <iomanip>
#include <cstring>
#include "DoipConnection.h"


namespace transport {


DoipConnection::DoipConnection() {
    InitializeTable();
}

DoipConnection::~DoipConnection() {


}

std::string DoipConnection::GetRouteActivationMsg() {
    std::string route_msg = "";

    route_msg += protocol_version;
    route_msg += inverse_version;
    route_msg += routing_activate;
    route_msg += "0000000B";
    route_msg += sa;
    route_msg += ta;
    route_msg += "00000000";
    route_msg += "ffffff";

    return route_msg;
}

void DoipConnection::ParseUDS(std::string msg) {
    std::transform(msg.begin(), msg.end(), msg.begin(), ::toupper);

    if(msg.size() < 2) return;
    std::string req = msg.substr(0, 2);
    if(req_sid_table.find(req) != req_sid_table.end()) {
        std::cout << "[SID] " << "0x" << req_sid_table.find(req)->first << " : " << req_sid_table.find(req)->second << std::endl;
        msg = msg.substr(2);
    } else if(res_sid_table.find(req) != res_sid_table.end()) {
        std::cout << "[SID] " << "0x" << res_sid_table.find(req)->first << " : " << res_sid_table.find(req)->second << std::endl;
        msg = msg.substr(2);
    }

    if(msg.size() < 4) return;
    if(req == "22" || req == "2E") {
        std::cout << "[DID] " << "0x" << msg.substr(0, 4) << std::endl;
        msg = msg.substr(4);
    } else if(req == "31") {
        std::cout << "[RID] " << "0x" << msg.substr(0, 4) << std::endl;
        msg = msg.substr(4);
    } else if(req == "7F") {
        req = msg.substr(0, 2);
        if(req_sid_table.find(req) != req_sid_table.end()) {
            std::cout << "[SID] " << "0x" << req_sid_table.find(req)->first << " : " << req_sid_table.find(req)->second << std::endl;;
            req = msg.substr(2, 2);
            if(nrc_table.find(req) != nrc_table.end()) {
                std::cout << "\033[1;31m" << "[NRC] " << "0x" << nrc_table.find(req)->first << " : " << nrc_table.find(req)->second << " \033[0m" << std::endl;
            }
        }
    }

    if(msg.size() < 1) return;
    std::cout<< "[PAYLOAD] " << "0x" << msg << std::endl;

}

std::string DoipConnection::AddDoIpHeader(std::string msg) {
    std::string added_msg;

    added_msg += protocol_version;
    added_msg += inverse_version;
    added_msg += diagnostic_event;

    std::string length = int2hex<int>(msg.size()/2 + 4);
    int pad = 8 - length.size();
    for(int i = 0 ; i < pad; i++) {
        added_msg += "0";
    }

    added_msg += length;
    added_msg += sa;
    added_msg += ta;
    added_msg += msg;


    return added_msg;
}

std::string DoipConnection::ParseDoIpHeader(char* msg, int size) {
    std::string msg_str_;

    for(int i = 0; i < size; i++) {
        msg_str_ += int2hex((int)msg[i]);
    }
    if(msg_str_.size() < 24) return "";
    std::string protocol_version_ = msg_str_.substr(0, 2);
    std::string inverse_version_  = msg_str_.substr(2, 2);
    std::string message_type_     = msg_str_.substr(4, 4);
    std::string length_           = msg_str_.substr(8, 8);
    std::string sa_               = msg_str_.substr(16, 4);
    std::string ta_               = msg_str_.substr(20, 4);
    std::string parsed_msg        = msg_str_.substr(24);

    if(message_type_ == "0006") {
        //std::cout << "| Set Target Address : " << ta_ << std::endl;
        SetTargetAddress(ta_);
    }

    return parsed_msg;
}

unsigned long DoipConnection::hex2dec(std::string hex)
{
    unsigned long result = 0;
    for (int i=0; i<hex.length(); i++) {
        if (hex[i]>=48 && hex[i]<=57)
        {
            result += (hex[i]-48)*pow(16,hex.length()-i-1);
        } else if (hex[i]>=65 && hex[i]<=70) {
            result += (hex[i]-55)*pow(16,hex.length( )-i-1);
        } else if (hex[i]>=97 && hex[i]<=102) {
            result += (hex[i]-87)*pow(16,hex.length()-i-1);
        }
    }
    return result;
}

template< typename T >
std::string DoipConnection::int2hex( T i )
{
    std::string ret;
    std::stringstream stream;
    stream << std::setfill ('0') << std::setw(sizeof(T)*2) << std::right << std::hex << i;
    stream >> ret;
    return ret.substr(ret.size() - 2);
}

int DoipConnection::HexStr2Arr(char* message, int sz, std::string s) {
    if(sz < s.size()) {
        std::cout << "buffer size is smaller than hex stream" << std::endl;
        message[0] = '\0';
        return 0;
    }

    int idx = 0;
    for(int i = 0; i < s.size(); i += 2) {
        //std::cout << "message[" << idx << "] : " << " (0x" << s.substr(i,2) << ")" << std::endl;
        message[idx] = hex2dec(s.substr(i, 2));
        idx++;
    }
    message[idx] = '\0';
    return idx;
}

void DoipConnection::InitializeTable() {
    req_sid_table.insert({"10", "Diagnostic Session Control"});
    req_sid_table.insert({"11", "ECU Reset"});
    req_sid_table.insert({"14", "Clear Diagnostic Information"});
    req_sid_table.insert({"19", "Read DTC Information"});
    req_sid_table.insert({"27", "Security Access"});
    req_sid_table.insert({"28", "Communication Control"});
    req_sid_table.insert({"3E", "Tester Present"});
    req_sid_table.insert({"85", "Control DTC Settings"});
    req_sid_table.insert({"22", "Read Data By Identifier"});
    req_sid_table.insert({"2E", "Write Data By Identifier"});
    req_sid_table.insert({"31", "Routine Control"});
    req_sid_table.insert({"34", "Request Download"});
    req_sid_table.insert({"36", "Transfer Data"});
    req_sid_table.insert({"37", "Request Transfer Exit"});

    res_sid_table.insert({"50", "Diagnostic Session Control"});
    res_sid_table.insert({"51", "ECU Reset"});
    req_sid_table.insert({"54", "Clear Diagnostic Information"});
    res_sid_table.insert({"59", "Read DTC Information"});
    res_sid_table.insert({"67", "Security Access"});
    res_sid_table.insert({"68", "Communication Control"});
    res_sid_table.insert({"7E", "Tester Present"});
    res_sid_table.insert({"C5", "Control DTC Settings"});
    res_sid_table.insert({"62", "Read Data By Identifier"});
    res_sid_table.insert({"6E", "Write Data By Identifier"});
    res_sid_table.insert({"71", "Routine Control"});
    res_sid_table.insert({"74", "Request Download"});
    res_sid_table.insert({"76", "Transfer Data"});
    res_sid_table.insert({"77", "Request Transfer Exit"});
    res_sid_table.insert({"7F", "Negative Response"});

    nrc_table.insert({"10", "General Reject"});
    nrc_table.insert({"11", "Service Not Supported"});
    nrc_table.insert({"12", "Subfunction Not Supported"});
    nrc_table.insert({"13", "Incorrect Message Length or Invalid Format"});
    nrc_table.insert({"22", "Condition Not Correct"});
    nrc_table.insert({"31", "Request Out of Range"});
    nrc_table.insert({"33", "Security Access Denied"});
    nrc_table.insert({"35", "Invalid Key"});
    nrc_table.insert({"36", "Exceed Number of Attempts"});
    nrc_table.insert({"78", "Response Pending"});
    nrc_table.insert({"7E", "Subfunction Not Supported in Active Session"});
    nrc_table.insert({"7F", "Service Not Supported in Active Session"});
}

} /* namespace transport */
