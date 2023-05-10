#include <iostream>
#include "opencv2/opencv.hpp"

#ifndef BASE_IMAGE_PATH
#define BASE_IMAGE_PATH "./"
#endif
#define IMAGE_PATH(PATH) BASE_IMAGE_PATH PATH
using namespace cv;

#define HEIGHT 512
#define WIDTH 512

int main()
{
    Mat src = cv::imread(IMAGE_PATH("butterfly.jpg"), IMREAD_COLOR);

    if (src.empty())
    {
        std::cerr << "Image not found" << std::endl;
        return -1;
    }

    Mat dst;
    cvtColor(src, dst, COLOR_BGR2GRAY);

    imshow("src", src);
    imshow("dst", dst);

    waitKey();
    destroyAllWindows();
}