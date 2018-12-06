#include <opencv2/opencv.hpp>
#include <boost/program_options.hpp>
#include <exception>
#include "face_detect.h"

namespace
{
    void detect_faces_mode()
    {
        cv::VideoCapture cap(0);
        FaceDetector detector("haarcascade_frontalface_default.xml");
        if(!cap.isOpened()){
            throw std::runtime_error("failed to open camera.");
        }
        for(;;){
            cv::Mat m;
            cap >> m;
            if(m.empty()){
                std::cerr << "image is empty." << std::endl;
                continue;
            }
            auto faces = detector.detect(m);
            for(auto rc : faces){
                cv::rectangle(m, rc, cv::Scalar(0xFF, 0, 0), 2);
            }
            cv::imshow("camera", m);
            cv::waitKey(1);
        }
    }

    void identify_faces_mode(std::string const & db)
    {

    }

    void create_database_mode(std::string const & dir)
    {

    }
}

int main(int argc, const char * argv[]) {
    using namespace boost::program_options;
    options_description description("Face options");
    description.add_options()
    ("mode,m", value<int>(), "Executing mode.\n*** YOU MUST SELECT EXEC MODE. ***\n0: Detect faces without identify.\n1: Identify faces.\n2: Create face database.")
    ("sample,s", "Face sample's directory. All face samples will be inspected. It is required to create face database.")
    ("db,d", "Face database file path. It is required to identify faces.")
    ("help,h", "Show helps")
    ("version,v", "Show version.")
    ;
    try{
        variables_map vm;
        store(parse_command_line(argc, argv, description), vm);
        notify(vm);
        if(vm.count("help")){
            std::cerr << description << std::endl;
            return 1;
        }
        if(vm.count("version")){
            std::cerr << "v.0.0.1" << std::endl;
            return 1;
        }
        try{
            switch(vm["mode"].as<int>()){
            default:
                throw std::runtime_error("Undefined mode.");
            case 0:
                detect_faces_mode();
                return 0;
            case 1:
                identify_faces_mode(vm["db"].as<std::string>());
                return 0;
            case 2:
                create_database_mode(vm["samples"].as<std::string>());
                return 0;
            }
        }catch(std::exception const & e){
            std::cerr << e.what() << std::endl;
            return 1;
        }
    }catch(std::exception const & e){
        std::cerr << e.what() << std::endl << description << std::endl;
        return 1;
    }
}
