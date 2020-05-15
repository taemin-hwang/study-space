#ifndef SRC_REPORT_REPORTER_H_
#define SRC_REPORT_REPORTER_H_
#include <iostream>
#include <vector>
#include <map>
#include <string>

namespace report{

enum class Result { PASS = 1, FAIL = 0 };

struct TestReport {
    std::string request;
    std::string response;
    report::Result result;
    std::string comment;
};

class Reporter {
public:
    Reporter();
    ~Reporter(){}
    bool WriteReport(std::string test_name, const std::vector<report::TestReport>& test_report);

private:
    const std::string GetDateTime();
    bool WriteData(std::ofstream& wf, const std::vector<report::TestReport>& test_report);

private:
    std::string file_name;
};

} /* namespace reporter */
#endif
