#include <iostream>
#include <string>
#include <vector>
#include <fstream>

// include rapidjson, for just reading json file
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/filereadstream.h"

using namespace std;
using namespace rapidjson;

class JsonParser {
public:
    JsonParser(string path);
    virtual ~JsonParser() = default;
    inline string get_company() { return company_; }
    inline int get_founding_year() { return founding_year_; }
    inline vector<string> get_employees() { return employees_; }
    void append_employee(string name);

private:
    Document document_;

    string company_ = "";
    int founding_year_ = 0;
    vector<string> employees_;
};

JsonParser::JsonParser(string path) {
    // read json file
    FILE* fp = fopen(path.c_str(), "rb");
    if(fp == 0) {
        std::cout << "file not exist : default param will be used" << std::endl;
        return;
    }
    char readbuffer[65536];
    FileReadStream is(fp, readbuffer, sizeof(readbuffer));

    document_.ParseStream(is);

    // parse company
    if(document_.HasMember("company")) {
        company_ = document_["company"].GetString();
    }

    // parse founding year
    if(document_.HasMember("founding year")) {
        founding_year_ = document_["founding year"].GetInt();
    }

    // parse employees
    if(document_.HasMember("employees")) {
        const Value& employees = document_["employees"];
        for(SizeType i = 0; i < employees.Size(); i++) {
            const Value& employee = employees[i];
            if(employee.HasMember("name")) {
                employees_.push_back(employee["name"].GetString());
            }
        }
    }
}

void JsonParser::append_employee(string name) {
    Value employee(kObjectType);
    Value name_value(kStringType);
    name_value.SetString(name.c_str(), name.size());
    employee.AddMember("name", name_value, document_.GetAllocator());

    // append employee
    document_["employees"].PushBack(employee, document_.GetAllocator());

    // update employees
    employees_.clear();
    const Value& employees = document_["employees"];
    for(SizeType i = 0; i < employees.Size(); i++) {
        const Value& employee = employees[i];
        if(employee.HasMember("name")) {
            employees_.push_back(employee["name"].GetString());
        }
    }

    // write to file
    StringBuffer buffer;
    Writer<StringBuffer> writer(buffer);
    document_.Accept(writer);

    std::ofstream output_file("../etc/config.json");
    if (output_file.is_open()) {
        output_file << buffer.GetString();
        output_file.close();
    }
}


int main () {
    // read json file
    JsonParser parser("../etc/config.json");
    cout << "company : " << parser.get_company() << endl;
    cout << "founding year : " << parser.get_founding_year() << endl;
    cout << "employees : ";
    for(auto& employee : parser.get_employees()) {
        cout << employee << " ";
    }
    cout << endl;

    // append employee
    parser.append_employee("steve");
    cout << "employees : ";
    for(auto& employee : parser.get_employees()) {
        cout << employee << " ";
    }
    cout << endl;

    return 0;
}