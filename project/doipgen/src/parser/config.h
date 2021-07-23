#ifndef __CONFIG__
#define __CONFIG__
#include <string>

struct Config {
    std::string ipaddr = "127.0.0.1";
    int ipversion = 4;
    int port = 13400;
};

#endif
