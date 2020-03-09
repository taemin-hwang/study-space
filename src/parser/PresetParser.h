#ifndef SRC_PARSER_PRESETPARSER_H_
#define SRC_PARSER_PRESETPARSER_H_
#include <string>
#include <map>
#include <vector>
#include <memory>
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/filereadstream.h"
#include "rapidjson/filewritestream.h"
#include "rapidjson/prettywriter.h"

namespace parser {
using ReqRes = std::pair<std::string, std::string>;

class PresetParser {
public:
    PresetParser(std::string s);
    virtual ~PresetParser();
    void CreatePreset();
    void DeletePreset(std::string s);
    inline std::map<std::string, std::vector<ReqRes>> GetPreset() { return presets_; }
    std::vector<ReqRes> SelectPreset();
    void PrintPreset();

private:
    void CreateValue(rapidjson::Document& d, rapidjson::Value& preset, std::string&, std::string&);
    void InitializePreset();
    void AddPreset(std::string nams);
private:
    FILE* fp = nullptr;
    rapidjson::Document d;
    std::unique_ptr<rapidjson::PrettyWriter<rapidjson::FileWriteStream>> writer;
    std::map<std::string, std::vector<ReqRes>> presets_;
    std::string path_;

    std::vector<std::string> preset_name;
    std::vector<rapidjson::Value> values;
    std::vector<std::string> request, response;

    int preset_idx = 0;
    int value_idx = 0;

    std::vector<rapidjson::Value> base;
};

} /* namespace parser */

#endif /* SRC_PARSER_PRESETPARSER_H_ */
