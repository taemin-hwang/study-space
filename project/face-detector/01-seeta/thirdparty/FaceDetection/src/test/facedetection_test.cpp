/*
 *
 * This file is part of the open-source SeetaFace engine, which includes three modules:
 * SeetaFace Detection, cd  Alignment, and SeetaFace Identification.
 *
 * This file is an example of how to use SeetaFace engine for face detection, the
 * face detection method described in the following paper:
 *
 *
 *   Funnel-structured cascade for multi-view face detection with alignment awareness,
 *   Shuzhe Wu, Meina Kan, Zhenliang He, Shiguang Shan, Xilin Chen.
 *   In Neurocomputing (under review)
 *
 *
 * Copyright (C) 2016, Visual Information Processing and Learning (VIPL) group,
 * Institute of Computing Technology, Chinese Academy of Sciences, Beijing, China.
 *
 * The codes are mainly developed by Shuzhe Wu (a Ph.D supervised by Prof. Shiguang Shan)
 *
 * As an open-source face recognition engine: you can redistribute SeetaFace source codes
 * and/or modify it under the terms of the BSD 2-Clause License.
 *
 * You should have received a copy of the BSD 2-Clause License along with the software.
 * If not, see < https://opensource.org/licenses/BSD-2-Clause>.
 *
 * Contact Info: you can send an email to SeetaFace@vipl.ict.ac.cn for any problems.
 *
 * Note: the above information must be kept whenever or wherever the codes are used.
 *
 */

#include <cstdint>
#include <fstream>
#include <iostream>
#include <string>

#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include "face_detection.h"

using namespace std;

int main(int argc, char** argv) {
  if (argc < 2) {
      cout << "Usage: " << argv[0]
          << " model_path"
          << endl;
      return -1;
  }

  // const char* img_path = argv[1];
  seeta::FaceDetection detector(argv[1]);
  detector.SetMinFaceSize(40);
  detector.SetScoreThresh(2.f);
  detector.SetImagePyramidScaleFactor(0.8f);
  detector.SetWindowStep(4, 4);

  cv::VideoCapture cap(0);

  // Check if the camera is opened successfully
  if (!cap.isOpened()) {
      std::cout << "Camera could not be opened." << std::endl;
      return -1;
  }

  while (true) {
      // Read a frame from the camera
      cv::Mat frame;
      cap >> frame;

      // Check if the frame is valid
      if (frame.empty()) {
          std::cout << "Frame is empty." << std::endl;
          break;
      }

      // Resize the frame to half its original size
      cv::Mat resized_frame;
      cv::resize(frame, resized_frame, cv::Size(), 0.5, 0.5);

      // cv::Mat img = cv::imread(img_path, cv::IMREAD_UNCHANGED);
      cv::Mat img_gray;

      if (resized_frame.channels() != 1)
        cv::cvtColor(resized_frame, img_gray, cv::COLOR_BGR2GRAY);
      else
        img_gray = resized_frame;

      seeta::ImageData img_data;
      img_data.data = img_gray.data;
      img_data.width = img_gray.cols;
      img_data.height = img_gray.rows;
      img_data.num_channels = 1;

      long t0 = cv::getTickCount();
      std::vector<seeta::FaceInfo> faces = detector.Detect(img_data);
      long t1 = cv::getTickCount();
      double secs = (t1 - t0)/cv::getTickFrequency();

      cout << "Detections takes " << secs << " seconds " << endl;
    #ifdef USE_OPENMP
      cout << "OpenMP is used." << endl;
    #else
      cout << "OpenMP is not used. " << endl;
    #endif

    #ifdef USE_SSE
      cout << "SSE is used." << endl;
    #else
      cout << "SSE is not used." << endl;
    #endif

      cout << "Image size (wxh): " << img_data.width << "x"
          << img_data.height << endl;

      cv::Rect face_rect, roi_rect;
      int32_t num_face = static_cast<int32_t>(faces.size());

      // Create a copy of the original image to preserve it
      // cv::Mat blurredImage = resized_frame.clone();

      for (int32_t i = 0; i < num_face; i++) {
        face_rect.x = faces[i].bbox.x;
        face_rect.y = faces[i].bbox.y;
        face_rect.width = faces[i].bbox.width;
        face_rect.height = faces[i].bbox.height;

        cv::rectangle(resized_frame, face_rect, CV_RGB(0, 0, 255), 4, 8, 0);

        int kernel_size = 15;
        roi_rect.x = std::max(face_rect.x, 0);
        roi_rect.y = std::max(face_rect.y, 0);
        roi_rect.width = std::min(face_rect.width, img_data.width - face_rect.x);
        roi_rect.height = std::min(face_rect.height, img_data.height - face_rect.y);

        // Define the region of interest (ROI) for the area to be blurred
        cv::Rect blur_roi(roi_rect.x, roi_rect.y, roi_rect.width, roi_rect.height); // x, y, width, height
        // Apply Gaussian blur to the ROI
        cv::Mat roi = resized_frame(blur_roi);
        cv::GaussianBlur(roi, roi, cv::Size(kernel_size, kernel_size), 0, 0);
      }

      // Show the frame in a window
      cv::imshow("Camera Feed", resized_frame);

      // Wait for a key press and exit the loop if 'q' is pressed
      if (cv::waitKey(1) == 'q') {
          break;
      }
  }
}
