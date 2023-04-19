#include <iostream>
#include "opencv2/opencv.hpp"

#ifndef BASE_IMAGE_PATH
#define BASE_IMAGE_PATH "./"
#endif
#define IMAGE_PATH(PATH) BASE_IMAGE_PATH PATH
using namespace cv;

int main()
{
    Mat src1 = cv::imread(IMAGE_PATH("lenna256.bmp"), IMREAD_GRAYSCALE);
    Mat src2 = cv::imread(IMAGE_PATH("square.bmp"), IMREAD_GRAYSCALE);

    if (src1.empty() || src2.empty())
    {
        return -1;
    }

    imshow("src1", src1);
    imshow("src2", src2);

    Mat dst1, dst2, dst3, dst4;

    add(src1, src2, dst1);
    addWeighted(src1, 0.5, src2, 0.5, 0, dst2);
    subtract(src1, src2, dst3);
    absdiff(src1, src2, dst4);

    imshow("dst1", dst1);
    imshow("dst2", dst2);
    imshow("dst3", dst3);
    imshow("dst4", dst4);

    waitKey();
    destroyAllWindows();
    return 0;
}