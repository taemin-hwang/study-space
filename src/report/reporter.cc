#include <ctime>
#include <fstream>
#include "report/reporter.h"

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

bool Reporter::WriteReport(const TestResult& tr) {
    if(!tr.IsValid()) return false;

    std::ofstream wf;
    wf.open(file_name.c_str(), std::ios_base::app);
    wf << file_name+"\n";
    wf << tr.GetName()+"\n";
    WriteData(wf, tr.GetResult());
    wf.close();
    return true;
}

bool Reporter::WriteData(std::ofstream& wf, const RESULT res) {
    if(!wf.is_open()) return false;
    std::string result;

    wf << "no, request, response, result \n";
    for(int i = 0 ; i < res.size(); i++) {
        wf << std::to_string(i+1)+",";
        wf << res[i].first.first+",";
        wf << res[i].first.second+",";
        if(res[i].second) {
            result = "PASS";
        } else {
            result = "FAIL";
        }
        wf << result+"\n";
    }
    return true;
}

}
