#ifndef ESTIMATOR_H_
#define ESTIMATOR_H_

#include <iostream>

class Estimator {
 public:
    Estimator() = default;
    virtual ~Estimator() = default;

    void Estimate3DPose();
    void EstimateDriverMotion();
    void EstimateDriverStatus();

 private:

};

#endif
