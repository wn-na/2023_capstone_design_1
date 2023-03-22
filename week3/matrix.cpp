#include <iostream>
#include "opencv2/opencv.hpp"

using namespace cv;

int main()
{
    Mat img1;

    Mat img2(480, 640, CV_8UC1);
    Mat img3(480, 640, CV_8UC3);
    Mat img4(Size(640, 480), CV_8UC3);

    Mat img5(480, 640, CV_8UC1, Scalar(128));
    Mat img6(480, 640, CV_8UC3, Scalar(0, 0, 255));

    Mat mat1 = Mat::zeros(3, 3, CV_32SC1);
    Mat mat2 = Mat::ones(3, 3, CV_32FC1);
    Mat mat3 = Mat::eye(3, 3, CV_32FC1);

    float data[] = {1, 2, 3, 4, 5, 6};
    Mat mat4(2, 3, CV_32FC1, data);

    Mat mat5 = (Mat_<float>(2, 3) << 1, 2, 3, 4, 5, 6);
    Mat mat6 = Mat_<uchar>({2, 3}, {1, 2, 3, 4, 5, 6});

    mat4.create(256, 256, CV_8UC3);
    mat5.create(4, 4, CV_32FC1);

    mat4 = Scalar(255, 0, 0);
    mat5.setTo(1.f);

    std::cout << img1 << std::endl;
    std::cout << img2 << std::endl;
    std::cout << img3 << std::endl;
    std::cout << img4 << std::endl;
    std::cout << img5 << std::endl;
    std::cout << img6 << std::endl;
    std::cout << mat1 << std::endl;
    std::cout << mat2 << std::endl;
    std::cout << mat3 << std::endl;
    std::cout << mat4 << std::endl;
    std::cout << mat5 << std::endl;
}