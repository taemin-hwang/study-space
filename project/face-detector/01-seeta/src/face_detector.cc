#include <iostream>

#include "face_detector.h"

FaceDetector::FaceDetector(std::string model_path) : detector(model_path.c_str()) {
    std::cout << "Create FaceDetector" << std::endl;
    detector.SetMinFaceSize(40);
    detector.SetScoreThresh(2.f);
    detector.SetImagePyramidScaleFactor(0.8f);
    detector.SetWindowStep(4, 4);
}

seeta::ImageData FaceDetector::convert_cv_to_seeta(const cv::Mat& image) {
    seeta::ImageData img_data;
    img_data.data = image.data;
    img_data.width = image.cols;
    img_data.height = image.rows;
    img_data.num_channels = 1;
    return img_data;
}

std::vector<cv::Rect> FaceDetector::detect_faces(const seeta::ImageData& image) {
    std::vector<cv::Rect> face_rects;
    cv::Rect face_rect;

    long t0 = cv::getTickCount();
    std::vector<seeta::FaceInfo> faces = detector.Detect(image);
    long t1 = cv::getTickCount();

    double secs = (t1 - t0)/cv::getTickFrequency();

    std::cout << "Detections takes " << secs << " seconds " << std::endl;
    std::cout << "Image size (wxh): " << image.width << "x" << image.height << std::endl;

    int32_t num_face = static_cast<int32_t>(faces.size());

    // Create a copy of the original image to preserve it
    for (int32_t i = 0; i < num_face; i++) {
        face_rect.x = faces[i].bbox.x;
        face_rect.y = faces[i].bbox.y;
        face_rect.width = faces[i].bbox.width;
        face_rect.height = faces[i].bbox.height;
        face_rects.push_back(face_rect);
    }
    return face_rects;
}
