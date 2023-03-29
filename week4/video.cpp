#include <iostream>
#include "opencv2/opencv.hpp"

using namespace cv;

int main()
{
    int FPS = 24;
    VideoCapture cap(0);

    if (!cap.isOpened())
    {
        std::cerr << "Camera open failed!" << std::endl;
        return -1;
    }

    std::cout << "Frame width: " << cvRound(cap.get(CAP_PROP_FRAME_WIDTH)) << std::endl;
    std::cout << "Frame height: " << cvRound(cap.get(CAP_PROP_FRAME_HEIGHT)) << std::endl;
    Mat frame, inversed;
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
        if (waitKey(cvRound(1000 / FPS)) == 27)
        {
            break;
        }
    }

    destroyAllWindows();
}