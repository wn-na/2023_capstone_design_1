#include <iostream>
#include "opencv2/opencv.hpp"

#ifndef BASE_IMAGE_PATH
#define BASE_IMAGE_PATH "./"
#endif
#define IMAGE_PATH(PATH) BASE_IMAGE_PATH PATH

using namespace cv;
using namespace std;

int delay = cvRound(1000 / 24);

void mask_setTo();
int main()
{
    mask_setTo();
}

void mask_setTo()
{
    VideoCapture cap(0);
    cap.set(CAP_PROP_FRAME_WIDTH, 512);
    cap.set(CAP_PROP_FRAME_HEIGHT, 512);

    if (!cap.isOpened())
    {
        std::cerr << "Camera open failed!" << std::endl;
        return;
    }

    Mat frame;
    Mat mask = cv::imread(IMAGE_PATH("mask_smile.bmp"), IMREAD_GRAYSCALE);

    if (mask.empty())
    {
        cerr << "Image load failed!" << endl;
        return;
    }

    while (true)
    {
        cap >> frame;
        if (frame.empty())
        {
            break;
        }
        imshow("src", frame);
        if (waitKey(delay) == 27)
        {
            break;
        }
    }

    resize(frame, frame, Size(512, 512), 0, 0, INTER_LINEAR);

    frame.setTo(Scalar(0, 255, 255), mask);

    imshow("src", frame);
    imshow("mask", mask);

    imwrite("result.bmp", frame);

    waitKey(0);
    destroyAllWindows();
}