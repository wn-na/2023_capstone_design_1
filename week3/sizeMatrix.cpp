#include <iostream>
#include "opencv2/opencv.hpp"

#ifndef BASE_IMAGE_PATH
#define BASE_IMAGE_PATH "./"
#endif
#define IMAGE_PATH(PATH) BASE_IMAGE_PATH PATH
using namespace cv;

int main()
{
    Mat img1 = cv::imread(IMAGE_PATH("lenna.bmp"), IMREAD_GRAYSCALE);

    Mat img1f;
    img1.convertTo(img1f, CV_32FC1);

    uchar data1[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
    Mat mat1(3, 4, CV_8UC1, data1);
    Mat mat2 = mat1.reshape(0, 1);

    std::cout << mat1 << std::endl;
    std::cout << mat2 << std::endl;

    Mat mat3 = Mat::ones(1, 4, CV_8UC1) * 255;
    mat1.push_back(mat3);

    std::cout << mat1 << std::endl;

    mat1.resize(6, 100);
    std::cout << mat1 << std::endl;

    waitKey();
    destroyAllWindows();
}