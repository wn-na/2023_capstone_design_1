#include <iostream>
#include "opencv2/opencv.hpp"

#ifndef BASE_IMAGE_PATH
#define BASE_IMAGE_PATH "./"
#endif
#define IMAGE_PATH(PATH) BASE_IMAGE_PATH PATH
using namespace cv;
using namespace std;

#define HEIGHT 512
#define WIDTH 512

int main()
{
    Mat src = cv::imread(IMAGE_PATH("pepper.bmp"));

    if (src.empty())
    {
        std::cerr << "Image not found" << std::endl;
        return -1;
    }

    Mat dst, dst2, result;
    cvtColor(src, dst, COLOR_BGR2HSV);

    vector<Mat> hsvVector;
    split(dst, hsvVector);

    for (int j = 0; j < src.rows; j++)
    {
        for (int i = 0; i < src.cols; i++)
        {
            auto &hue = hsvVector[0].at<uchar>(j, i);
            if (hue >= 5 && hue < 174) // red range
            {
                hsvVector[1].at<uchar>(j, i) = 0;
            }
        }
    }

    merge(hsvVector, dst2);

    cvtColor(dst2, result, COLOR_HSV2BGR);

    imshow("src", src);
    imshow("result", result);

    waitKey();
    destroyAllWindows();
}