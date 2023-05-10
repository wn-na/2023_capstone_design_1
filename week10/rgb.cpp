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

    Mat dst(src.rows, src.cols, src.type());

    for (int j = 0; j < src.rows; j++)
    {
        for (int i = 0; i < src.cols; i++)
        {
            Vec3b &p1 = src.at<Vec3b>(j, i);
            Vec3b &p2 = dst.at<Vec3b>(j, i);

            p2[0] = 255 - p1[0];
            p2[1] = 255 - p1[1];
            p2[2] = 255 - p1[2];
        }
    }
    imshow("src", src);
    imshow("dst", dst);

    waitKey();
    destroyAllWindows();
}