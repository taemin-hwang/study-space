#ifndef SRC_REPORT_TESTRESULT_H_
#define SRC_REPORT_TESTRESULT_H_
#include <iostream>
#include <string>
#include <vector>
#include <map>

namespace report {

class TestResult {
using RESULT = std::vector<std::pair<std::pair<std::string, std::string>, bool>>;
public:
    TestResult(std::string t) : test_case(t){}
    ~TestResult(){}
    inline void SetTestCase(std::vector<std::pair<std::string, std::string>> tc_) { testcase = tc_;}
    inline void SetTestResult(std::vector<bool> tr_) { testresult = tr_;}
    inline bool IsValid() const { return testcase.size() == testresult.size(); }
    inline std::string GetName() const {return test_case;}
    RESULT GetResult() const {
        RESULT ret;
        if(!IsValid()) return ret;
        for(int i = 0 ; i < testcase.size(); i++) {
            ret.push_back({testcase[i], testresult[i]});
        }
        return ret;
    }

private:
    std::string test_case;
    std::vector<std::pair<std::string, std::string>> testcase;
    std::vector<bool> testresult;
};
}
#endif
