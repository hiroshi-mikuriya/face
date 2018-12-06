#include <opencv2/opencv.hpp>

class FaceDetector
{
    cv::CascadeClassifier m_cascade;
public:
    FaceDetector(std::string const & xml);

    std::vector<cv::Rect> detect(cv::Mat const & m);
};
