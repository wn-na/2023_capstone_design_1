#include <iostream>
#include "opencv2/opencv.hpp"

#ifndef BASE_IMAGE_PATH
#define BASE_IMAGE_PATH "./"
#endif
#define IMAGE_PATH(PATH) BASE_IMAGE_PATH PATH
using namespace cv;

void brightness1();
int main()
{
    brightness1();
    return 0;
}

void brightness1()
{
    Mat src = cv::imread(IMAGE_PATH("lenna.bmp"), IMREAD_GRAYSCALE);

    if (src.empty())
    {
        std::cout << "Image load failed!" << std::endl;
        return;
    }

    Mat dst(src.rows, src.cols, src.type());

    for (int i = 0; i < src.rows; i++)
    {
        for (int j = 0; j < src.cols; j++)
        {
            dst.at<uchar>(i, j) = saturate_cast<uchar>(src.at<uchar>(i, j) + 100);
        }
    }

    imshow("src", src);
    imshow("dst", dst);

    waitKey();
    destroyAllWindows();
}