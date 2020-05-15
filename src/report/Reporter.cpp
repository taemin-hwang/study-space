#include <ctime>
#include <fstream>
#include "report/Reporter.h"

namespace report{
Reporter::Reporter() {
    file_name = "../var/" + GetDateTime() + ".csv";
    std::cout << __func__ << ": " << file_name << std::endl;
}

const std::string Reporter::GetDateTime() {
    time_t     now = time(NULL);
    struct tm  tstruct;
    char       buf[80];
    tstruct = *localtime(&now);

    strftime(buf, sizeof(buf), "%Y-%m-%d-%H-%M", &tstruct);
    return buf;
}

bool Reporter::WriteReport(std::string test_name, const std::vector<report::TestReport>& test_report) {
    std::ofstream wf;
    wf.open(file_name.c_str(), std::ios_base::app);
    wf << file_name+"\n";
    wf << test_name+"\n";
    WriteData(wf, test_report);
    wf.close();
    return true;
}

bool Reporter::WriteData(std::ofstream& wf, const std::vector<report::TestReport>& test_report) {
    if(!wf.is_open()) return false;
    std::string result;

    wf << "no, request, response, result, comment \n";

    int i = 0;
    for(const auto &p : test_report) {
        wf << std::to_string(++i)+",";
        wf << p.request + ",";
        wf << p.response + ",";
        if(p.result == Result::PASS) {
            result = "PASS";
        } else {
            result = "FAIL";
        }
        wf << result + ",";
        wf << p.comment + "\n";
    }

    return true;
}

}
