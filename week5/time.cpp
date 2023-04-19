#include <iostream>
#include "opencv2/opencv.hpp"

#ifndef BASE_IMAGE_PATH
#define BASE_IMAGE_PATH "./"
#endif
#define IMAGE_PATH(PATH) BASE_IMAGE_PATH PATH

using namespace cv;

int main()
{
    Mat src = imread(IMAGE_PATH("lena.jpg"), IMREAD_GRAYSCALE);

    if (src.empty())
    {
        std::cout << "Can't open image" << std::endl;
        return -1;
    }

    Mat dst(src.rows, src.cols, src.type());

    TickMeter tm;
    tm.start();

    for (int j = 0; j < src.rows; j++)
    {
        for (int i = 0; i < src.cols; i++)
        {
            dst.at<uchar>(j, i) = 255 - src.at<uchar>(j, i);
        }
    }

    tm.stop();
    std::cout << "time: " << tm.getTimeMilli() << "ms" << std::endl;

    return 0;
}
