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
    return false;
}

FaceInfo FaceIdentifier::who(cv::Mat const & m)
{
    FaceInfo dst;
    return dst;
}
