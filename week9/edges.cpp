#include <iostream>
#include "opencv2/opencv.hpp"

#ifndef BASE_IMAGE_PATH
#define BASE_IMAGE_PATH "./"
#endif
#define IMAGE_PATH(PATH) BASE_IMAGE_PATH PATH
using namespace cv;

int main()
{
    Mat src = cv::imread(IMAGE_PATH("lenna.bmp"), IMREAD_GRAYSCALE);

    if (src.empty())
    {
        std::cerr << "Image load failed" << std::endl;
        return -1;
    }

    Mat dx, dy;
    Sobel(src, dx, CV_32FC1, 1, 0, FILTER_SCHARR);
    Sobel(src, dy, CV_32FC1, 0, 1, FILTER_SCHARR);

    Mat fmag, mag;
    magnitude(dx, dy, fmag);

    fmag.convertTo(mag, CV_8UC1);
    Mat edge = mag > 150;

    Mat angle;
    phase(dx, dy, angle);
    normalize(angle, angle, 0, 255, NORM_MINMAX);

    imshow("src", src);
    imshow("mag", mag);
    imshow("edge", edge);
    imshow("angle", angle);

    waitKey();
    destroyAllWindows();
}