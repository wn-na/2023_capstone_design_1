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
    Mat src = cv::imread(IMAGE_PATH("tekapo.bmp"), IMREAD_COLOR);

    if (src.empty())
    {
        std::cerr << "Image not found" << std::endl;
        return -1;
    }
    Mat dst, dst2, result;
    cvtColor(src, dst, COLOR_BGR2HSV);

    vector<Mat> hsvVector;
    split(dst, hsvVector);

    equalizeHist(hsvVector[1], hsvVector[1]);

    merge(hsvVector, dst2);

    cvtColor(dst2, result, COLOR_HSV2BGR);

    imshow("src", src);
    imshow("result", result);

    waitKey();
    destroyAllWindows();
    return 0;
}