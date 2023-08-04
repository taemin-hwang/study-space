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
    

private:
    seeta::FaceDetection detector;
};