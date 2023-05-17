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
    Mat src = cv::imread(IMAGE_PATH("milkdrop.bmp"), IMREAD_GRAYSCALE);

    Mat bin;

    int th = (int)threshold(src, bin, 0, 255, THRESH_BINARY | THRESH_OTSU);

    Mat dst1, dst2;
    morphologyEx(bin, dst1, MORPH_OPEN, Mat());
    morphologyEx(bin, dst2, MORPH_CLOSE, Mat());

    imshow("src", src);
    imshow("bin", bin);
    imshow("erode", dst1);
    imshow("dilate", dst2);

    waitKey();
    destroyAllWindows();
}