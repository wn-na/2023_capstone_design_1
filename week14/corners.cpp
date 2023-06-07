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
    Mat src = cv::imread(IMAGE_PATH("building.jpg"), IMREAD_GRAYSCALE);

    if (src.empty())
    {
        cerr << "Image load failed" << endl;
        return -1;
    }

    Mat harris;
    cornerHarris(src, harris, 3, 3, 0.04);

    Mat harris_norm;
    normalize(harris, harris_norm, 0, 255, NORM_MINMAX, CV_8U);

    Mat dst;
    cvtColor(src, dst, COLOR_GRAY2BGR);

    for (int j = 1; j < harris.rows - 1; j++)
    {
        for (int i = 1; i < harris.cols - 1; i++)
        {
            if (harris_norm.at<uchar>(j, i) > 120)
            {
                float base = harris.at<float>(j, i);

                if (
                    base > harris.at<float>(j - 1, i) &&
                    base > harris.at<float>(j + 1, i) &&
                    base > harris.at<float>(j, i - 1) &&
                    base > harris.at<float>(j, i + 1))
                {
                    circle(dst, Point(i, j), 5, Scalar(0, 0, 255), 2);
                }
            }
        }
    }

    imshow("src", src);
    imshow("harris_norm", harris_norm);
    imshow("dst", dst);

    waitKey();
    destroyAllWindows();
}