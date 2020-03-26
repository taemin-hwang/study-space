#include <iostream>
#include "parser/PresetParser.h"

using namespace rapidjson;
namespace parser {

PresetParser::PresetParser(std::string s) : path_(s){
    char readbuffer[65536];
    char writeBuffer[65536];
    fp = fopen(path_.c_str(), "rb+");
    FileReadStream is(fp, readbuffer, sizeof(readbuffer));
    d.ParseStream(is);
    if(!d.IsObject()) {
        std::cout << "[DEBUG] Set Object" << std::endl;
        d.SetObject();
    }

    FileWriteStream os(fp, writeBuffer, sizeof(writeBuffer));
    writer = std::make_unique<PrettyWriter<FileWriteStream>>(os);

    fclose(fp);

    preset_name.resize(30);
    base.resize(30);
    values.resize(300);
    request.resize(300);
    response.resize(300);

    InitializePreset();
}

PresetParser::~PresetParser() {
}

void PresetParser::InitializePreset() {
    std::string name, req, res;
    for(auto itr = d.MemberBegin(); itr != d.MemberEnd(); itr++) {
        std::vector<std::pair<std::string, std::string>> tmp;
        name = itr->name.GetString();

        const Value& arr = d[name.c_str()];
        for(int i = 0; i < arr.Size(); i++) {
            const Value& msg = arr[i];
            for(auto msg_itr = msg.MemberBegin(); msg_itr != msg.MemberEnd(); msg_itr+= 2) {
                req = msg_itr->value.GetString();
                res = (msg_itr+1)->value.GetString();
                tmp.push_back({req, res});
            }
        }
        presets_.insert({name, tmp});
    }
}

void PresetParser::AddPreset(std::string new_name) {
    std::string name, req, res;
    std::vector<std::pair<std::string, std::string>> tmp;

    if(presets_.find(new_name) == presets_.end()) {

        for(auto itr = d.MemberBegin(); itr != d.MemberEnd(); itr++) {
            std::vector<std::pair<std::string, std::string>> tmp;
            name = itr->name.GetString();

            if(new_name == name) {
                const Value& arr = d[name.c_str()];
                for(int i = 0; i < arr.Size(); i++) {
                    const Value& msg = arr[i];
                    for(auto msg_itr = msg.MemberBegin(); msg_itr != msg.MemberEnd(); msg_itr+= 2) {
                        req = msg_itr->value.GetString();
                        res = (msg_itr+1)->value.GetString();
                        tmp.push_back({req, res});
                    }
                }
                presets_.insert({name, tmp});
            }
        }
    } else {
        std::cout << "[WARN] preset name was already assigned" << std::endl;
    }
}

std::vector<std::pair<std::string, std::string>> PresetParser::SelectPreset(std::string& testname) {
    int in = 0;
    int idx = 0;
    std::vector<std::string> list;
    list.resize(presets_.size());
    std::cout << "=====================================================================" << std::endl;
    std::cout << "[Preset List]" << std::endl;
    int sz = presets_.size();
    for(auto m : presets_) {
        std::cout << "[" << idx+1 << "] " << m.first << std::endl;
        list[idx] = m.first;
        idx++;
    }
    std::cout << "[" << sz+1 << "] " << "BACK" << std::endl;
    std::cout << "[Select Preset] : ";
    std::cin >> in;

    std::vector<std::pair<std::string, std::string>> ret;

    if(in < sz+1) {
        testname = list[in-1];
        return presets_[list[in-1]];
    } else if(in > sz+1) {
        SelectPreset(testname);
    }
    return ret;
}

void PresetParser::PrintPreset() {
}

void PresetParser::CreateValue(Document& d, Value& preset, std::string& request, std::string& response) {
    preset.SetObject();
    std::cout <<"[Enter Request  Message] : ";
    std::getline(std::cin, request);
    //std::cin.ignore();
    std::cout <<"[Enter Response Message] : ";
    std::getline(std::cin, response);
    //std::cin.ignore();

    preset.AddMember(StringRef("request"), StringRef(request.c_str()), d.GetAllocator());
    preset.AddMember(StringRef("response"), StringRef(response.c_str()), d.GetAllocator());

}

void PresetParser::CreatePreset() {
    std::string ans = "yes";
    char readbuffer[65536];
    char writeBuffer[65536];

    fp = fopen(path_.c_str(), "rb+");
    FileReadStream is(fp, readbuffer, sizeof(readbuffer));
    d.ParseStream(is);
    if(!d.IsObject()) {
        std::cout << "[DEBUG] Set Object" << std::endl;
        d.SetObject();
    }

    FileWriteStream os(fp, writeBuffer, sizeof(writeBuffer));
    writer = std::make_unique<PrettyWriter<FileWriteStream>>(os);

    std::cout <<"[Enter Preset   Name   ] : ";
    while(preset_name[preset_idx] == "") {
        std::getline(std::cin, preset_name[preset_idx]);
    }
    //std::cin.ignore();
    base[preset_idx].SetArray();

    while(ans == "yes" && value_idx < 300) {
        CreateValue(d, values[value_idx], request[value_idx], response[value_idx]);
        base[preset_idx].PushBack(values[value_idx], d.GetAllocator());
        std::cout <<"[Add more message? (yes/no)] : "; std::cin >> ans;
        getchar();
        value_idx++;
    }

    d.AddMember(StringRef(preset_name[preset_idx].c_str()), base[preset_idx], d.GetAllocator());
    AddPreset(preset_name[preset_idx]);
    preset_idx++;

    fp=freopen(NULL,"w",fp);
    d.Accept(*writer);

    fclose(fp);
}

void PresetParser::DeletePreset() {
    int in = 0;
    int idx = 0;
    std::vector<std::string> list;
    list.resize(presets_.size());
    std::cout << "=====================================================================" << std::endl;
    std::cout << "[Preset List]" << std::endl;
    int sz = presets_.size();
    for(auto m : presets_) {
        std::cout << "[" << idx+1 << "] " << m.first << std::endl;
        list[idx] = m.first;
        idx++;
    }
    std::cout << "[" << sz+1 << "] " << "BACK" << std::endl;
    std::cout << "[Select Preset] : ";
    std::cin >> in;

    if(in > sz+1) {
        DeletePreset();
    } else if(in == sz+1) {
        return;
    }

    char readbuffer[65536];
    char writeBuffer[65536];

    fp = fopen(path_.c_str(), "rb+");
    FileReadStream is(fp, readbuffer, sizeof(readbuffer));
    d.ParseStream(is);
    if(!d.IsObject()) {
        std::cout << "[DEBUG] Set Object" << std::endl;
        d.SetObject();
    }

    FileWriteStream os(fp, writeBuffer, sizeof(writeBuffer));
    writer = std::make_unique<PrettyWriter<FileWriteStream>>(os);

    d.RemoveMember(list[in-1].c_str());
    presets_.erase(list[in-1]);

    fp=freopen(NULL,"w",fp);
    d.Accept(*writer);

    fclose(fp);
    return;
}

} /* namespace parser */
