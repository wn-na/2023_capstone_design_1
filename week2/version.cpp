#include "opencv2/opencv.hpp"
#include <iostream>

#ifndef BASE_IMAGE_PATH
#define BASE_IMAGE_PATH "./"
#endif
#define IMAGE_PATH(PATH) BASE_IMAGE_PATH PATH

int main(void)
{
    std::cout << "Hello OpenCV" << CV_VERSION << std::endl;

    cv::Mat img;
    img = cv::imread(IMAGE_PATH("lenna.bmp"));

    if (img.empty())
    {
        std::cerr << "Image load failed!" << std::endl;
        return -1;
    }

    cv::namedWindow("image", cv::WINDOW_NORMAL);
    cv::moveWindow("image", 400, 400);
    cv::imshow("image", img);
    cv::resizeWindow("image", 200, 200);
    cv::waitKey(10);
    return 0;
}