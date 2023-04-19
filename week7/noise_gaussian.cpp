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
    imshow("src", src);

    for (int stddev = 10; stddev <= 30; stddev += 10)
    {

        Mat noise(src.size(), CV_32SC1);
        randn(noise, 0, stddev);

        Mat dst;
        add(src, noise, dst, Mat(), CV_8U);
        Mat dst2;

        GaussianBlur(dst, dst2, Size(), (double)1);

        String desc = format("stddev = %d", stddev);
        putText(dst, desc, Point(10, 30), FONT_HERSHEY_SIMPLEX, 1.0, Scalar(255), 1, LINE_AA);

        imshow(desc, dst2);

        waitKey();
    }

    destroyAllWindows();
}