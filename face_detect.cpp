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
    auto img0 = gamma(m, 2.0);
    double r = 0.25;
    std::vector<cv::Rect> tmp, dst;
    cv::Mat img1;
    cv::resize(img0, img1, cv::Size(), r, r);
    m_cascade.detectMultiScale(img1, tmp, 1.1, 5, 0, cv::Size(100, 100) * r);
    std::transform(tmp.begin(), tmp.end(), std::back_inserter(dst), [r](cv::Rect const & rc){
        return rc / r;
    });
    return dst;
}

bool FaceDetector::loaded()const
{
    return !m_cascade.empty();
}

void FaceDetector::load(const std::string &xml)
{
    m_cascade.load(xml);
}
