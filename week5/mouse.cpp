#include <iostream>
#include "opencv2/opencv.hpp"

#ifndef BASE_IMAGE_PATH
#define BASE_IMAGE_PATH "./"
#endif
#define IMAGE_PATH(PATH) BASE_IMAGE_PATH PATH
using namespace cv;

Mat img;
Point ptOld;
void onMouse(int event, int x, int y, int flags, void *);
int main()
{
    img = cv::imread(IMAGE_PATH("lenna.bmp"));

    if (img.empty())
    {
        std::cerr << "Image load failed" << std::endl;
        return -1;
    }

    namedWindow("img");
    setMouseCallback("img", onMouse);

    imshow("img", img);

    waitKey(0);

    return 0;
}

void onMouse(int event, int x, int y, int flags, void *)
{
    switch (event)
    {
    case EVENT_LBUTTONUP:
        ptOld = Point(x, y);
        std::cout << "EVENT_LBUTTONUP: " << x << "," << y << std::endl;
        break;
    case EVENT_LBUTTONDOWN:
        ptOld = Point(x, y);
        std::cout << "EVENT_LBUTTONDOWN: " << x << "," << y << std::endl;
        break;
    case EVENT_MOUSEMOVE:
        if (flags & EVENT_FLAG_LBUTTON)
        {
            line(img, ptOld, Point(x, y), Scalar(0, 0, 255), 2);
            imshow("img", img);
            ptOld = Point(x, y);
        }
        break;
    default:
        break;
    }
}