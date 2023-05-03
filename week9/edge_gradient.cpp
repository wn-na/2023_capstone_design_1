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

    float data[] = {-1, 0, 1};

    Mat x(1, 3, CV_32FC1, data);
    Mat y(3, 1, CV_32FC1, data);

    Mat dstx, dsty;
    filter2D(src, dstx, CV_32FC1, x, Point(-1, -1), 0);
    filter2D(src, dsty, CV_32FC1, y, Point(-1, -1), 0);

    imshow("src", src);
    Mat edge(src.rows, src.cols, src.type());
    float fx, fy, grident;
    int threshold = 50;

    for (int i = 0; i < src.rows; i++)
    {
        for (int j = 0; j < src.cols; j++)
        {
            fx = dstx.at<float>(i, j);
            fy = dsty.at<float>(i, j);

            grident = sqrt(fx * fx + fy * fy);

            if (grident > threshold)
            {
                edge.at<uchar>(i, j) = 255;
            }
            else
            {
                edge.at<uchar>(i, j) = 0;
            }
        }
    }
    dstx.convertTo(dstx, CV_8UC1, 1.0, 0);
    dsty.convertTo(dsty, CV_8UC1, 1.0, 0);
    imshow("dstx", dstx + 128);
    imshow("dsty", dsty + 128);

    imshow("edge", edge);

    waitKey();
    destroyAllWindows();
}