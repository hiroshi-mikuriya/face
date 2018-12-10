#include "face_identifier.h"
#include "face_detector.h"
#include <boost/filesystem.hpp>
#include <boost/foreach.hpp>

Feature::Feature(cv::Mat m)
{
    auto algorithm = cv::ORB::create();
    algorithm->detect(m, points);
    algorithm->compute(m, points, desc);
}


FaceIdentifier::FaceIdentifier()
{
}

FaceIdentifier::FaceIdentifier(std::string const & db)
{
    load(db);
}

static std::vector<Feature> s_features;
static std::vector<cv::KeyPoint> s_keyPoints;
static cv::Mat s_desc;

void FaceIdentifier::load(std::string const & db)
{
    // TODO: temporary
    FaceDetector detector("haarcascade_frontalface_default.xml");
    namespace fs = boost::filesystem;
    fs::path root(db);
    auto range = std::make_pair(fs::directory_iterator(root), fs::directory_iterator());
    BOOST_FOREACH(fs::path f, range) {
        cv::Mat m = cv::imread(f.c_str(), 0);
        if(m.empty()){
            continue;
        }
        auto faces = detector.detect(m);
        if(faces.empty()){
            continue;
        }
        auto face = m(faces.front());
        Feature ft(face);
        ft.id = f.stem().c_str();
        ft.img = face;
        s_features.push_back(ft);
        std::cout << ft.id << std::endl << ft.points.size() << std::endl << ft.desc.size() << std::endl;
    }
}

bool FaceIdentifier::loaded()const
{
    // TODO:
    return true;
}

FaceInfo FaceIdentifier::who(cv::Mat const & m)
{
    Feature master(m);
    cv::Ptr<cv::DescriptorMatcher> matcher = cv::DescriptorMatcher::create("BruteForce");
    for(auto const & sample : s_features){
#if 1
        std::vector<cv::DMatch> match, match12, match21;
        matcher->match(master.desc, sample.desc, match12);
        matcher->match(sample.desc, master.desc, match21);
        for (size_t i = 0; i < match12.size(); i++){
            cv::DMatch forward = match12[i];
            cv::DMatch backward = match21[forward.trainIdx];
            if (backward.trainIdx == forward.queryIdx){
                match.push_back(forward);
            }
        }
#else
        std::vector<std::vector<cv::DMatch>> match;
        matcher->knnMatch(master.desc, sample.desc, match, 2);

#endif
        cv::Mat dest;
        cv::drawMatches(m, master.points, sample.img, sample.points, match, dest);
        cv::imshow(sample.id, dest);
    }
    FaceInfo dst;
    dst.id = s_features.front().id;
    return dst;
}
