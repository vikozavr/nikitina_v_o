#include <iostream>
#include "object_tracker.h"

int main(int argc, char** argv)
{

    int opt;
    std::string path = "";

    if ( (argc <= 1) || (argv[argc-1] == NULL) || (argv[argc-1][0] == '-') ) {
        std::cerr << "No argument provided!" << std::endl;
        return 1;
    }
    else {

        std::cout<<"Opening "<<argv[argc-1]<<"..."<<std::endl;
        path = argv[argc-1];
    }

    cv::VideoCapture cap(path);
    cv::Mat frame;
    cap.read(frame);
    cap.release();

    cv::Rect bboxStart(287, 23, 86, 320); 
    cv::Rect bboxEnd(287, 23, 86, 320); 

    bboxStart = cv::selectROI(frame, false); 
    bboxEnd = cv::selectROI(frame, false); 
    

    ObjectTracker obj = ObjectTracker(path, bboxStart, bboxEnd);

    ResultParameters result = obj.compute(false);

    double rt = 123.0/640.0;
    std::cout << " Speed (Pixel/Sec): " << result.getPixelSpeed() <<std::endl;
    std::cout << " Speed (Cm/Sec): " << result.getRealSpeed(rt) <<std::endl;
}