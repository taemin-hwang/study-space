/*
 * ConfigParser.cpp
 *
 *  Created on: 2020. 2. 26.
 *      Author: taemin.hwang
 */

#include <iostream>
#include <cstdio>
#include "parser/config_parser.h"

using namespace rapidjson;

namespace parser {

ConfigParser::ConfigParser(std::string s) {
    FILE* fp = fopen(s.c_str(), "rb");
    if(fp == 0) {
        std::cout << "file not exist : default param will be used" << std::endl;
        return;
    }
    char readbuffer[65536];
    FileReadStream is(fp, readbuffer, sizeof(readbuffer));

    Document document;
    document.ParseStream(is);

    fclose(fp);

    if(document.HasMember("ipaddr") && document["ipaddr"].IsString()) {
        cfg_.ipaddr = document["ipaddr"].GetString();
    }
    if(document.HasMember("version") && document["version"].IsInt()) {
        cfg_.ipversion = document["version"].GetInt();
    }
    if(document.HasMember("port") && document["port"].IsInt()) {
        cfg_.port = document["port"].GetInt();
    }
}

ConfigParser::~ConfigParser() {

}

Config ConfigParser::getCfg() {

    return cfg_;
}

} /* namespace parser */
