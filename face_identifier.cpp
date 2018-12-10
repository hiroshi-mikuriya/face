#include "face_identifier.h"

Feature::Feature(cv::Mat m)
{
    cv::Mat gray;
    if(m.channels() == 1){
        gray = m.clone();
    }else{
        cv::cvtColor(m, gray, CV_BGR2GRAY);
    }
    auto algorithm = cv::AKAZE::create();
    algorithm->detect(gray, points);
    algorithm->compute(gray, points, desc);
}


FaceIdentifier::FaceIdentifier()
{
}

FaceIdentifier::FaceIdentifier(std::string const & db)
{
    load(db);
}

void FaceIdentifier::load(std::string const & db)
{
    // TODO: load database
}

bool FaceIdentifier::loaded()const
{
    // TODO:
    return true;
}

FaceInfo FaceIdentifier::who(cv::Mat const & m)
{
    {
        cv::Mat cp = m.clone();
        Feature ft(cp);
        for(auto pt : ft.points){
            cv::circle(cp, pt.pt, 3, 255, 1);
        }
        cv::imshow("keypoints", cp);
    }
    FaceInfo dst;
    dst.id = "mikuriya";
    return dst;
}
