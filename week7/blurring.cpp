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
    for (int ksize = 3; ksize <= 7; ksize += 2)
    {
        blur(src, dst, Size(ksize, ksize - 1));

        String desc = format("mean %d x %d", ksize, ksize - 1);
        putText(dst, desc, Point(10, 30), FONT_HERSHEY_SIMPLEX, 1.0, Scalar(255), 1, LINE_AA);
        imshow("dst", dst);
        waitKey();
    }

    destroyAllWindows();
}