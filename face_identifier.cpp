#include "face_identifier.h"
#include <boost/filesystem.hpp>
#include <boost/foreach.hpp>

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

static std::vector<Feature> s_features;

void FaceIdentifier::load(std::string const & db)
{
    // TODO: temporary
    namespace fs = boost::filesystem;
    fs::path root(db);
    auto range = std::make_pair(fs::directory_iterator(root), fs::directory_iterator());
    BOOST_FOREACH(fs::path f, range) {
        cv::Mat m = cv::imread(f.c_str(), 0);
        if(m.empty()){
            continue;
        }
        Feature ft(m);
        ft.id = f.stem().c_str();
        ft.img = m;
        s_features.push_back(ft);
        std::cout << ft.id << std::endl;
    }
}

bool FaceIdentifier::loaded()const
{
    // TODO:
    return true;
}

FaceInfo FaceIdentifier::who(cv::Mat const & m)
{
    cv::Mat cp = m.clone();
    Feature master(cp);
    for(auto pt : master.points){
        cv::circle(cp, pt.pt, 3, 255, 1);
    }
    cv::imshow("keypoints", cp);
    cv::Ptr<cv::DescriptorMatcher> matcher = cv::DescriptorMatcher::create("BruteForce");
    for(auto const & sample : s_features){
        std::vector<cv::DMatch> match, match12, match21;
        matcher->match(master.desc, sample.desc, match12);
        //matcher->match(sample.desc, master.desc, match21);
        cv::Mat dest;
        cv::drawMatches(cp, master.points, sample.img, sample.points, match12, dest);
        cv::imshow(sample.id, dest);
    }
    FaceInfo dst;
    dst.id = s_features.front().id;
    return dst;
}
