#ifndef _FACE_DETECTOR_COMMON_H_
#define _FACE_DETECTOR_COMMON_H_

#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

// Custom struct to hold a bounding box and its tracking counter
struct TrackedObject {
    cv::Rect rect;
    int counter; // Number of frames object hasn't been seen
    int id; // Unique ID for the object
    TrackedObject(const cv::Rect& r, int objectId) : rect(r), counter(0), id(objectId) {}
};

#endif