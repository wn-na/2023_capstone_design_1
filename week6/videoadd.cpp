#include <iostream>
#include "opencv2/opencv.hpp"

#ifndef BASE_IMAGE_PATH
#define BASE_IMAGE_PATH "./"
#endif
#define IMAGE_PATH(PATH) BASE_IMAGE_PATH PATH
using namespace cv;

int main()
{
    Mat img1 = cv::imread(IMAGE_PATH("lenna256.bmp"), IMREAD_GRAYSCALE);
    Mat img2 = cv::imread(IMAGE_PATH("cameraman256.bmp"), IMREAD_GRAYSCALE);

    Mat addimg;

    addimg = img1 + img2;

    imshow("img1", img1);
    imshow("img2", img2);
    imshow("addimg", addimg);

    waitKey();
    destroyAllWindows();
    return 0;
}