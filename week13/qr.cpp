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
    VideoCapture cap(0);

    if (!cap.isOpened())
    {
        cerr << "Video open failed" << endl;
        return -1;
    }

    QRCodeDetector detector;

    Mat frame;
    while (true)
    {
        cap >> frame;
        if (frame.empty())
            break;

        vector<Point> points;
        String info = detector.detectAndDecode(frame, points);

        if (!info.empty())
        {
            polylines(frame, points, true, Scalar(0, 0, 255), 2);
            putText(frame, info, Point(10, 30), FONT_HERSHEY_DUPLEX, 1, Scalar(0, 0, 255));
        }

        imshow("frame", frame);
        if (waitKey(1) == 27)
            break;
    }
    return 0;
}