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

    Point2f cp(src.cols / 2.f, src.rows / 2.f);
    Mat M = getRotationMatrix2D(cp, 20, 1);

    double a = 1 * cos(20.0f / 180 * CV_PI); // 0.9396926207859084
    double b = 1 * sin(20.0f / 180 * CV_PI); // 0.3420201433256687
    Mat M2 = Mat_<double>({2, 3}, {a, b, ((1 - a) * cp.x - b * cp.y),
                                   -b, a, (b * cp.x + (1 - a) * cp.y)});

    cout << M << "/" << M2 << endl;

    Mat dst, dst1;
    warpAffine(src, dst, M, Size());
    warpAffine(src, dst1, M2, Size());

    imshow("src", src);
    imshow("dst", dst);
    imshow("dst1", dst1);
    waitKey();
    destroyAllWindows();
}