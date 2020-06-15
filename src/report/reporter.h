#ifndef SRC_REPORT_REPORTER_H_
#define SRC_REPORT_REPORTER_H_
#include <iostream>
#include <vector>
#include <map>
#include <string>
#include "report/test_result.h"

namespace report{

class Reporter {
using RESULT = std::vector<std::pair<std::pair<std::string, std::string>, bool>>;
public:
    Reporter();
    ~Reporter(){}
    bool WriteReport(const TestResult&);

private:
    const std::string GetDateTime();
    bool WriteData(std::ofstream& wf, const RESULT);

private:
    std::string file_name;
};

} /* namespace reporter */
#endif
