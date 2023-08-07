#include "video_manager.h"


VideoManager::VideoManager(const bool& camera_option, const int& width, const int& height, std::string video_path) : camera_option_(camera_option) {
    if (camera_option_ == true) {
        int frameWidth = width;
        int frameHeight = height;

        std::string videoFileName = video_path;

        videoWriter.open(videoFileName, cv::VideoWriter::fourcc('M', 'J', 'P', 'G'), 30, cv::Size(frameWidth, frameHeight), true);

        // Check if the VideoWriter is opened successfully
        if (!videoWriter.isOpened()) {
            std::cout << "Failed to open the VideoWriter." << std::endl;
        }
    }
}

VideoManager::~VideoManager() {
    if (camera_option_ == true) {
        // Release the VideoWriter and close the output video file
        videoWriter.release();
    }
}

void VideoManager::save_video(const cv::Mat& frame) {
    if (camera_option_ == false) {
        return;
    }

    videoWriter.write(frame);
}