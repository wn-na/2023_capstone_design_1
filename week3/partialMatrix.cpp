#include <iostream>
#include "opencv2/opencv.hpp"

#ifndef BASE_IMAGE_PATH
#define BASE_IMAGE_PATH "./"
#endif
#define IMAGE_PATH(PATH) BASE_IMAGE_PATH PATH
using namespace cv;

int main()
{
    Mat img1 = cv::imread(IMAGE_PATH("cat.bmp"));

    if (img1.empty())
    {
        std::cerr << "Image load failed!" << std::endl;
        return -1;
    }
    Mat img2 = img1(Rect(220, 120, 340, 240));
    Mat img3 = img1(Rect(220, 120, 340, 240)).clone();
    img2 = ~img2;

    imshow("img1", img1);
    imshow("img2", img2);
    imshow("img3", img3);

    waitKey();
    destroyAllWindows();
}