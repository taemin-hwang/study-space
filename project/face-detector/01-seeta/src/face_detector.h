#ifndef _FACE_DETECTOR_H_
#define _FACE_DETECTOR_H_

#include "common.h"
#include "face_detection.h"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include <string>

class FaceDetector {
public:
    FaceDetector(std::string model_path);
    virtual ~FaceDetector() = default;

    seeta::ImageData convert_cv_to_seeta(const cv::Mat& image);
    std::vector<cv::Rect> detect_faces(const seeta::ImageData& image);
    std::vector<cv::Rect> smooth_bbox(std::vector<cv::Rect> faces, int window_size);
    double calculate_iou(const cv::Rect& rect1, const cv::Rect& rect2);
    void get_tracked_objects(std::vector<TrackedObject>& trackedObjects, const std::vector<cv::Rect>& newBoundingBoxes, int N);

private:
    seeta::FaceDetection detector;
};

#endif