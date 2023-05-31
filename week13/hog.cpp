#include <iostream>
#include "opencv2/opencv.hpp"

#ifndef BASE_IMAGE_PATH
#define BASE_IMAGE_PATH "./"
#endif
#define IMAGE_PATH(PATH) BASE_IMAGE_PATH PATH
using namespace cv;
using namespace std;

#define HEIGHT 512
#define WIDTH 512

int main()
{
    VideoCapture cap(IMAGE_PATH("vtest.avi"));

    if (!cap.isOpened())
    {
        cerr << "Video open failed" << endl;
        return -1;
    }

    HOGDescriptor hog;
    hog.setSVMDetector(HOGDescriptor::getDefaultPeopleDetector());

    Mat frame;
    while (true)
    {
        cap >> frame;
        if (frame.empty())
            break;

        vector<Rect> detected;
        hog.detectMultiScale(frame, detected);

        for (Rect r : detected)
        {
            Scalar c = Scalar(rand() % 256, rand() % 256, rand() % 256);
            rectangle(frame, r, c, 3);
        }

        imshow("frame", frame);
        if (waitKey(10) == 27)
            break;
    }
    return 0;
}