#include "object_tracker.h"

ObjectTracker::ObjectTracker(std::string path, cv::Rect start, cv::Rect stop) {
    this->path = path;

    startZone = start;
    stopZone = stop;
}

ResultParameters ObjectTracker::compute(bool useGui = false) {
    cv::VideoCapture capture = cv::VideoCapture(path);

    double framesPerSecond = capture.get(cv::CAP_PROP_FPS);
    double width = capture.get(cv::CAP_PROP_FRAME_WIDTH);
    double height = capture.get(cv::CAP_PROP_FRAME_HEIGHT);

    cv::Ptr<cv::BackgroundSubtractor> pBackSub = cv::createBackgroundSubtractorKNN();
    cv::Mat frame;

    bool s = false, e = false;

    unsigned long long frameNumber = 0;
    double tempTime, result;

    int distanceInPixels = 0;

    while (capture.read(frame)) {
        cv::Mat diff;
        pBackSub->apply(frame, diff);
       
        cv::Mat median_img;
        cv::medianBlur(diff, median_img, 9);

        cv::threshold(median_img, median_img, 250, 255, cv::THRESH_BINARY); 

        std::vector<std::vector<cv::Point>> contours;
        std::vector<cv::Vec4i> hierarchy;
        cv::findContours(median_img, contours, hierarchy, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

        for (const auto& contour : contours) {

            if (cv::contourArea(contour) > 400 * (width*height)/(640*480)) {
                std::vector<cv::Point> hull;
                cv::convexHull(contour, hull);
                cv::drawContours(frame, std::vector<std::vector<cv::Point>>{hull}, 0, cv::Scalar(0, 0, 255), 3);


                if (cv::contourArea(contour) < width * height * 0.5) {
                    for (const auto& point: contour) {
                        if (!s && point.x < startZone.x) {
                            s = true;
                            tempTime = frameNumber/framesPerSecond;

                            distanceInPixels = point.x;

                            //std::cout<< "CURRENT TIME IS: ";
                            //std::cout<< tempTime << std::endl;

                        }

                        if (!e && point.x < stopZone.x) {
                            e = true;
                            result = frameNumber/framesPerSecond - tempTime;
                            
                            distanceInPixels = distanceInPixels - point.x;

                            //std::cout<< "RESULT TIME IS: ";
                            //std::cout<< result << std::endl;

                            return ResultParameters(result, distanceInPixels);
                        }
                    }
                }
            }
        }

        if (useGui) {
            if (!s) cv::rectangle(frame, startZone, cv::Scalar( 0, 255, 0 ), 2, 1 );
            if (!e) cv::rectangle(frame, stopZone, cv::Scalar( 255, 0, 0 ), 2, 1 );
        
            cv::imshow("frame", frame);

            if (cv::waitKey(1) == 'q') {break;}
        }

        frameNumber++;
    }

    capture.release();
    return ResultParameters(result, distanceInPixels);
}