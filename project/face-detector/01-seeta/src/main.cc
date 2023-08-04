#include "face_detector.h"
#include "image_manager.h"

using namespace std;

int main(int argc, char** argv) {
  unique_ptr<FaceDetector> detector = make_unique<FaceDetector>("../model/seeta_fd_frontal_v1.0.bin");
  unique_ptr<ImageManager> manager = make_unique<ImageManager>();

  while (true) {
      // Read the frame from default cap(0)
      auto frame = manager->get_frame_from_camera();

      // Check if the frame is valid
      if (frame.empty()) {
          std::cout << "Frame is empty." << std::endl;
          break;
      }

      // Resize the frame to half its original size
      frame = manager->resize_image(frame, 0.3);
      // Make RGB image to Gray
      auto img_gray = manager->change_image_gray(frame);
      auto img_data = detector->convert_cv_to_seeta(img_gray);
      auto faces = detector->detect_faces(img_data);
      frame = manager->get_blurred_face_image(frame, faces, 100.0); // sigma (0 ~ 100)
      
      // Show the frame in a window
      cv::imshow("Camera Feed", frame);

      // Wait for a key press and exit the loop if 'q' is pressed
      if (cv::waitKey(1) == 'q') {
          break;
      }
  }
}
