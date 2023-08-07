#ifndef _SEETA_VIDEO_MANAGER_H_
#define _SEETA_VIDEO_MANAGER_H_

#include <string>
#include <iostream>

#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

class VideoManager {
public:
    VideoManager(const bool& camera_option, const int& width, const int& height, std::string video_path);
    virtual ~VideoManager();
    void save_video(const cv::Mat& frame);

private:
    cv::VideoWriter videoWriter;
    bool camera_option_;
};

#endif