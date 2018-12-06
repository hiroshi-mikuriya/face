#include "face_identifier.h"

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
    cv::Mat gray;
    cv::cvtColor(m, gray, CV_BGR2GRAY);
    FaceInfo dst;
    dst.id = "mikuriya";
    return dst;
}
