#include <opencv2/opencv.hpp>
#include "face_detect.h"

int main(int argc, const char * argv[]) {
    cv::VideoCapture cap(0);
    FaceDetector detector("haarcascade_frontalface_default.xml");
    if(!cap.isOpened()){
        std::cerr << "failed to open camera." << std::endl;
        return 1;
    }
    for(;;){
        cv::Mat m;
        cap >> m;
        if(m.empty()){
            std::cerr << "image is empty." << std::endl;
        }
        auto faces = detector.detect(m);
        for(auto rc : faces){
            cv::rectangle(m, rc, cv::Scalar(0xFF, 0, 0), 2);
        }
        cv::imshow("camera", m);
        cv::waitKey(1);
    }
    return 0;
}
