#include <iostream>
#include "opencv2/opencv.hpp"

#ifndef BASE_IMAGE_PATH
#define BASE_IMAGE_PATH "./"
#endif
#define IMAGE_PATH(PATH) BASE_IMAGE_PATH PATH
using namespace cv;
using namespace std;

int main()
{
    Mat src = cv::imread(IMAGE_PATH("lenna.bmp"), IMREAD_GRAYSCALE);

    if (src.empty())
    {
        std::cerr << "Image load failed" << std::endl;
        return -1;
    }

    Mat noise(src.size(), CV_32SC1);
    randn(noise, 0, 5);
    add(src, noise, src, Mat(), CV_8U);

    Mat dst1;
    GaussianBlur(src, dst1, Size(), 5);

    Mat dst2;
    bilateralFilter(src, dst2, -1, 10, 5);

    imshow("src", src);
    imshow("dst1", dst1);
    imshow("dst2", dst2);

    waitKey();
    destroyAllWindows();
}
