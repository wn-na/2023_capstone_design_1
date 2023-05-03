#include <iostream>
#include "opencv2/opencv.hpp"

#ifndef BASE_IMAGE_PATH
#define BASE_IMAGE_PATH "./"
#endif
#define IMAGE_PATH(PATH) BASE_IMAGE_PATH PATH
using namespace cv;

int main()
{
    Mat src = cv::imread(IMAGE_PATH("lenna.bmp"), IMREAD_GRAYSCALE);

    if (src.empty())
    {
        std::cerr << "Image load failed" << std::endl;
        return -1;
    }

    Mat dst1, dst2, dst3;
    Canny(src, dst1, 50, 100);
    Canny(src, dst2, 50, 150);

    Mat dx, dy;
    Sobel(src, dx, CV_16SC1, 1, 0);
    Sobel(src, dy, CV_16SC1, 0, 1);
    Canny(dx, dy, dst3, 50, 150);

    imshow("src", src);
    imshow("dst1", dst1);
    imshow("dst2", dst2);
    imshow("dst3", dst3);

    waitKey();
    destroyAllWindows();
}