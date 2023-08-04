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

// Function to calculate Intersection over Union (IoU) between two rectangles
double FaceDetector::calculate_iou(const cv::Rect& rect1, const cv::Rect& rect2) {
    int x1 = std::max(rect1.x, rect2.x);
    int y1 = std::max(rect1.y, rect2.y);
    int x2 = std::min(rect1.x + rect1.width, rect2.x + rect2.width);
    int y2 = std::min(rect1.y + rect1.height, rect2.y + rect2.height);

    if (x1 >= x2 || y1 >= y2) {
        return 0.0; // No overlap
    }

    double intersectionArea = (x2 - x1) * (y2 - y1);
    double unionArea = rect1.area() + rect2.area() - intersectionArea;
    return intersectionArea / unionArea;
}

// Function to update tracked objects with new bounding boxes
void FaceDetector::get_tracked_objects(std::vector<TrackedObject>& trackedObjects, const std::vector<cv::Rect>& newBoundingBoxes, int N) {
    std::vector<bool> isTracked(trackedObjects.size(), false);

    for (const auto& newBox : newBoundingBoxes) {
        int bestMatchIndex = -1;
        double bestIoU = 0.0;

        for (size_t i = 0; i < trackedObjects.size(); ++i) {
            double iou = calculate_iou(trackedObjects[i].rect, newBox);
            if (iou > bestIoU) {
                bestIoU = iou;
                bestMatchIndex = i;
            }
        }

        if (bestMatchIndex != -1 && bestIoU > 0.2) {
            // Update the existing tracked object with the new bounding box
            trackedObjects[bestMatchIndex].rect = newBox;
            trackedObjects[bestMatchIndex].counter = 0;
            isTracked[bestMatchIndex] = true;
        } else {
            // Add the new bounding box as a new tracked object with a new ID
            int newId = trackedObjects.empty() ? 1 : (trackedObjects.back().id + 1);
            trackedObjects.emplace_back(newBox, newId);
        }
    }

    // Increment the tracking counter for all tracked objects
    for (size_t i = 0; i < isTracked.size(); ++i) {
        if (!isTracked[i]) {
            // Increment the counter for unmatched objects
            trackedObjects[i].counter++;
        }
    }

    // Remove objects that haven't been seen for more than N frames
    trackedObjects.erase(std::remove_if(trackedObjects.begin(), trackedObjects.end(),
                        [N](const TrackedObject& obj) { return obj.counter >= N; }),trackedObjects.end());
}