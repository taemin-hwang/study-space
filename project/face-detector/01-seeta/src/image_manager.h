#ifndef _IMAGE_MANAGER_H_
#define _IMAGE_MANAGER_H_

#include <iostream>
#include <cstdint>
#include <fstream>
#include <string>
#include <memory>

#include "common.h"
#include "face_detection.h"

#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"


class ImageManager {
public:
    ImageManager(bool camera_option, std::string video_path);
    virtual ~ImageManager() = default;

    cv::Mat get_frame_from_camera();
    cv::Mat resize_image(const cv::Mat& image, float scale);
    cv::Mat change_image_gray(const cv::Mat& image);
    cv::Mat get_blurred_face_image(const cv::Mat& image, const std::vector<TrackedObject>& faces, double sigma);

private:
    bool camera_option_;
    cv::VideoCapture cap;
    // a set of predefined colors
    std::vector<cv::Scalar> colors = {
        cv::Scalar(255, 0, 0),    // Red
        cv::Scalar(0, 255, 0),    // Green
        cv::Scalar(0, 0, 255),    // Blue
        cv::Scalar(255, 255, 0),  // Yellow
        cv::Scalar(0, 255, 255),  // Cyan
        cv::Scalar(255, 0, 255),  // Magenta
        cv::Scalar(128, 128, 128),// Gray
        cv::Scalar(255, 128, 0),  // Orange
        cv::Scalar(0, 128, 255),  // Light Blue
        cv::Scalar(128, 0, 255)   // Purple
    };
};

#endif