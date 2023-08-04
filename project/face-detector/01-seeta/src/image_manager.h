#include <iostream>
#include <cstdint>
#include <fstream>
#include <string>
#include <memory>

#include "face_detection.h"

#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

class ImageManager {
public:
    ImageManager();
    virtual ~ImageManager() = default;

    cv::Mat get_frame_from_camera();
    cv::Mat resize_image(const cv::Mat& image, float scale);
    cv::Mat change_image_gray(const cv::Mat& image);
    cv::Mat get_blurred_face_image(const cv::Mat& image, const std::vector<cv::Rect>& faces, double sigma);

private:
    cv::VideoCapture cap;
};