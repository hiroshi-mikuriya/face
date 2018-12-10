#include <opencv2/opencv.hpp>

struct FaceInfo
{
    std::string id;
};

struct Feature
{
    std::vector<cv::KeyPoint> points;
    cv::Mat desc;
    Feature(cv::Mat m);
};

class FaceIdentifier
{
public:
    FaceIdentifier();

    FaceIdentifier(std::string const & db);

    void load(std::string const & db);

    bool loaded()const;

    FaceInfo who(cv::Mat const & m);
};
