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

int lower_hue = 40, upper_hue = 80;
Mat src, src_hsv, mask;

void on_hue_changed(int, void *);

int main()
{
    src = cv::imread(IMAGE_PATH("candies.png"), IMREAD_COLOR);

    if (src.empty())
    {
        std::cerr << "Image not found" << std::endl;
        return -1;
    }

    cvtColor(src, src_hsv, COLOR_BGR2HSV);

    imshow("src", src);

    namedWindow("mask");
    createTrackbar("LOWER", "mask", &lower_hue, 179, on_hue_changed);
    createTrackbar("UPPER", "mask", &upper_hue, 179, on_hue_changed);

    on_hue_changed(0, 0);
    waitKey();
    destroyAllWindows();
    return 0;
}

void on_hue_changed(int, void *)
{
    Scalar lowerb(lower_hue, 100, 0);
    Scalar upperb(upper_hue, 255, 255);

    inRange(src_hsv, lowerb, upperb, mask);

    imshow("mask", mask);
}