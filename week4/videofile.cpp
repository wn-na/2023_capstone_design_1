#include <iostream>
#include "opencv2/opencv.hpp"

#ifndef BASE_IMAGE_PATH
#define BASE_IMAGE_PATH "./"
#endif
#define IMAGE_PATH(PATH) BASE_IMAGE_PATH PATH

using namespace cv;

int main()
{
    VideoCapture cap(IMAGE_PATH("stopwatch.avi"));

    if (!cap.isOpened())
    {
        std::cerr << "Video open failed!" << std::endl;
        return -1;
    }

    std::cout << "Frame width: " << cvRound(cap.get(CAP_PROP_FRAME_WIDTH)) << std::endl;
    std::cout << "Frame height: " << cvRound(cap.get(CAP_PROP_FRAME_HEIGHT)) << std::endl;
    std::cout << "Frame count: " << cvRound(cap.get(CAP_PROP_FRAME_COUNT)) << std::endl;

    double fps = cap.get(CAP_PROP_FPS);
    std::cout << "FPS: " << fps << std::endl;

    int delay = cvRound(1000 / fps);

    Mat frame,
        inversed;
    while (true)
    {
        cap >> frame;
        if (frame.empty())
        {
            break;
        }

        inversed = ~frame;

        imshow("frame", frame);
        imshow("inversed", inversed);
        if (waitKey(delay) == 27)
        {
            break;
        }
    }

    destroyAllWindows();
}