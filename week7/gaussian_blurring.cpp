#include <iostream>
#include "opencv2/opencv.hpp"

#ifndef BASE_IMAGE_PATH
#define BASE_IMAGE_PATH "./"
#endif
#define IMAGE_PATH(PATH) BASE_IMAGE_PATH PATH
using namespace cv;

int main()
{
    Mat src = cv::imread(IMAGE_PATH("rose.bmp"), IMREAD_GRAYSCALE);

    if (src.empty())
    {
        std::cerr << "Image load failed" << std::endl;
        return -1;
    }
    imshow("src", src);

    Mat dst;
    for (int sigma = 1; sigma <= 5; sigma++)
    {
        GaussianBlur(src, dst, Size(), (double)sigma);

        String desc = format("sigma = %d", sigma);
        putText(dst, desc, Point(10, 30), FONT_HERSHEY_SIMPLEX, 1.0, Scalar(255), 1, LINE_AA);
        imshow("dst", dst);
        waitKey();
    }

    destroyAllWindows();
}