#include "face_detect.h"

namespace
{
    cv::Rect operator*(cv::Rect const & rc, double r)
    {
        return cv::Rect(static_cast<int>(r * rc.x), static_cast<int>(r * rc.y), static_cast<int>(r * rc.width), static_cast<int>(r * rc.height));
    }
    cv::Rect operator/(cv::Rect const & rc, double r)
    {
        return rc * (1 / r);
    }
    cv::Size operator*(cv::Size const & sz, double r)
    {
        return cv::Size(static_cast<int>(r * sz.width), static_cast<int>(r * sz.height));
    }
    cv::Mat gamma(cv::Mat const & src, double g)
    {
        uchar lut[256] = { 0 };
        for(size_t i = 0; i < sizeof(lut); ++i){
            lut[i] = static_cast<int>(std::pow(i / 255.0, 1 / g) * 255);
        }
        cv::Mat dst;
        cv::LUT(src, cv::Mat(cv::Size(256, 1), CV_8U, lut), dst);
        return dst;
    }
}

FaceDetector::FaceDetector(std::string const & xml)
    : m_cascade(xml)
{
}

std::vector<cv::Rect> FaceDetector::detect(cv::Mat const & m)
{
    auto img = gamma(m, 2.0);
    double r = 0.25;
    std::vector<cv::Rect> rects;
    cv::Mat rimg;
    cv::resize(img, rimg, cv::Size(), r, r);
    m_cascade.detectMultiScale(rimg, rects, 1.1, 5, 0, cv::Size(100, 100) * r);
    std::vector<cv::Rect> faces;
    for(auto rc : rects){
        faces.push_back(rc / r);
    }
    return faces;
}
