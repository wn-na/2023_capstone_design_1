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

    Mat M = Mat_<double>({2, 3}, {1, 0, 150, 0, 1, 100});

    Mat dst;
    warpAffine(src, dst, M, Size());

    imshow("src", src);
    imshow("dst", dst);

    waitKey();
    destroyAllWindows();
}