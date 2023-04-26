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
    Mat src = cv::imread(IMAGE_PATH("tekapo.bmp"));

    if (src.empty())
    {
        cerr << "Image load failed!" << endl;
        return -1;
    }

    double mx = 0.3;
    Mat M = Mat_<double>({2, 3}, {1, mx, 0, 0, 1, 0});

    Mat dst;
    warpAffine(src, dst, M, Size(cvRound(src.cols + src.rows * mx), src.rows));

    imshow("src", src);
    imshow("dst", dst);

    waitKey();
    destroyAllWindows();
}