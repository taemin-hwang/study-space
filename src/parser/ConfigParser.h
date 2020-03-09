/*
 * ConfigParser.h
 *
 *  Created on: 2020. 2. 26.
 *      Author: taemin.hwang
 */

#ifndef SRC_PARSER_CONFIGPARSER_H_
#define SRC_PARSER_CONFIGPARSER_H_
#include <string>
#include "parser/Config.h"
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/filereadstream.h"

namespace parser {

class ConfigParser {
public:
    ConfigParser(std::string s);
    virtual ~ConfigParser();
    Config getCfg();

private:
    Config cfg_;
};

} /* namespace parser */

#endif /* SRC_PARSER_CONFIGPARSER_H_ */
