#include <filesystem>

#include "face_detector.h"
#include "image_manager.h"
#include "video_manager.h"
#include <csignal>

// Global flag to indicate if the interrupt signal is received
volatile sig_atomic_t signalFlag = 0;

// Signal handler function to handle the interrupt signal (Ctrl+C)
void signalHandler(int signum) {
    std::cout << "Interrupt signal (" << signum << ") received." << std::endl;
    signalFlag = 1;
}

using namespace std;

class ArgumentParser {
public:
    ArgumentParser(int argc, char* argv[]) : argc(argc), argv(argv) {}
    void parse() {
        for (int i = 1; i < argc; ++i) {
            std::string arg = argv[i];
            if (arg == "--video" && i + 1 < argc) {
                useCamera = false;
                videoPath = argv[i + 1];

                std::ifstream file_stream(videoPath);
                if (file_stream) {
                    std::cout << "File exists." << std::endl;
                } else {
                    std::cout << "No such file or directory : " << videoPath << std::endl;
                    videoPath = "";
                }
            } else if (arg == "--camera") {
                useCamera = true;
            } else if (arg == "--save") {
                saveVideo = true;
            }
        }
    }

    inline std::string getVideoPath() const { return videoPath; }
    inline bool useCameraOption() const { return useCamera;}
    inline bool saveVideoOption() const { return saveVideo; }

private:
    int argc;
    char** argv;
    std::string videoPath = "";
    bool useCamera = true;
    bool saveVideo = false;
};


int main(int argc, char** argv) {
    ArgumentParser argParser(argc, argv);
    argParser.parse();

    if (!argParser.getVideoPath().empty()) {
        std::cout << "Video Path: " << argParser.getVideoPath() << std::endl;
    } else if (argParser.useCameraOption()) {
        std::cout << "Using Camera" << std::endl;
    } else {
        std::cout << "Usage: " << argv[0] << " [options]" << std::endl;
        std::cout << "Options:" << std::endl;
        std::cout << "  --video <path>    Path to the video file" << std::endl;
        std::cout << "  --camera          Use camera as input" << std::endl;
        std::cout << "  --save            Save the output video" << std::endl;
        return 1;
    }

    // Register the signal handler for the interrupt signal (Ctrl+C)
    std::signal(SIGINT, signalHandler);

    unique_ptr<FaceDetector> detector = make_unique<FaceDetector>("../model/seeta_fd_frontal_v1.0.bin");
    unique_ptr<ImageManager> image_manager = make_unique<ImageManager>(argParser.useCameraOption(), argParser.getVideoPath());
    auto frame = image_manager->get_frame_from_camera();
    unique_ptr<VideoManager> video_manager = make_unique<VideoManager>(argParser.saveVideoOption(), frame.cols, frame.rows, "output-video.mp4");

    std::vector<TrackedObject> tracked_objects;
    std::vector<cv::Rect> detected_face, tracked_face;

    int frame_num = 0;

    while (!signalFlag) {
        // Read the frame from default cap(0)
        auto frame = image_manager->get_frame_from_camera();

        // Check if the frame is valid
        if (frame.empty()) {
            std::cout << "Frame is empty." << std::endl;
            break;
        }

        // Resize the frame to half its original size
        // frame = image_manager->resize_image(frame, 0.5);

        // Make RGB image to Gray
        auto img_gray = image_manager->change_image_gray(frame);

        // Convert opencv image to Seeta image format
        auto img_data = detector->convert_cv_to_seeta(img_gray);

        // Detect faces from Seeta image
        detected_face = detector->detect_faces(img_data);

        // Keep tracking faces by using IoU
        detector->get_tracked_objects(tracked_objects, detected_face, 5);

        // Make the face area blurred
        frame = image_manager->get_blurred_face_image(frame, tracked_objects, 100.0); // sigma (0 ~ 100)

        // Show the frame in a window
        cv::imshow("Camera Feed", frame);

        // Save the frame to the output video
        video_manager->save_video(frame);

        if (frame_num < 1000000) {
            frame_num += 1;
        } else {
            frame_num = 0;
        }


        // Wait for a key press and exit the loop if 'q' is pressed
        if (cv::waitKey(1) == 'q') {
            break;
        }
    }
}
