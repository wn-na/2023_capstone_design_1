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
    Mat src = cv::imread(IMAGE_PATH("Cameraman256.bmp"), IMREAD_GRAYSCALE);

    Mat dst;

    int th = (int)threshold(src, dst, 0, 255, THRESH_BINARY | THRESH_OTSU);
    cout << th << endl;
    imshow("src", src);
    imshow("dst", dst);

    waitKey();
    destroyAllWindows();
}