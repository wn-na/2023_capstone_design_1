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

    cv::namedWindow("image");
    cv::imshow("image", img);
    cv::waitKey(0);
    return 0;
}