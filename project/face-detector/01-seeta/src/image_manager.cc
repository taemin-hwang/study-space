#include "image_manager.h"

ImageManager::ImageManager() : cap(0){
    std::cout << "Create Opencv Manager" << std::endl;
    // Check if the camera is opened successfully
    if (!cap.isOpened()) {
        std::cout << "Camera could not be opened." << std::endl;
    }
}

cv::Mat ImageManager::get_frame_from_camera() {
    cv::Mat frame;
    cap >> frame;
    return frame;
}

cv::Mat ImageManager::resize_image(const cv::Mat& image, float scale) {
    // Resize the frame to half its original size
    cv::Mat resized_frame;
    cv::resize(image, resized_frame, cv::Size(), scale, scale);
    return resized_frame;
}

cv::Mat ImageManager::change_image_gray(const cv::Mat& image) {
    cv::Mat img_gray;

    if (image.channels() != 1)
        cv::cvtColor(image, img_gray, cv::COLOR_BGR2GRAY);
    else
        img_gray = image;

    return img_gray;
}

cv::Mat ImageManager::get_blurred_face_image(const cv::Mat& image, const std::vector<cv::Rect>& faces, double sigma) {
    cv::Rect face_rect, roi_rect;
    int32_t num_face = static_cast<int32_t>(faces.size());

    // Create a copy of the original image to preserve it
    for (int32_t i = 0; i < num_face; i++) {
        face_rect.x = faces[i].x;
        face_rect.y = faces[i].y;
        face_rect.width = faces[i].width;
        face_rect.height = faces[i].height;

        cv::rectangle(image, face_rect, CV_RGB(0, 0, 255), 4, 8, 0);

        int kernel_size = 15;
        // double sigma = 100.0; // Standard deviation in X direction
        roi_rect.x = std::max(face_rect.x, 0);
        roi_rect.y = std::max(face_rect.y, 0);
        roi_rect.width = std::min(face_rect.width, image.cols - face_rect.x);
        roi_rect.height = std::min(face_rect.height, image.rows - face_rect.y);

        // Define the region of interest (ROI) for the area to be blurred
        cv::Rect blur_roi(roi_rect.x, roi_rect.y, roi_rect.width, roi_rect.height); // x, y, width, height

        // Apply Gaussian blur to the ROI
        cv::Mat roi = image(blur_roi);
        cv::GaussianBlur(roi, roi, cv::Size(kernel_size, kernel_size), sigma, sigma);
    }

    return image;
}