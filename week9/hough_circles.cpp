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
    Mat src = cv::imread(IMAGE_PATH("coins.png"), IMREAD_GRAYSCALE);

    if (src.empty())
    {
        std::cerr << "Image load failed" << std::endl;
        return -1;
    }

    Mat blurred;
    blur(src, blurred, Size(3, 3));

    vector<Vec3f> circles;
    HoughCircles(blurred, circles, HOUGH_GRADIENT, 1, 50, 150, 30);

    Mat dst;
    cvtColor(src, dst, COLOR_GRAY2RGB);

    for (Vec3f c : circles)
    {
        Point center(cvRound(c[0]), cvRound(c[1]));
        int radius = cvRound(c[2]);
        circle(dst, center, radius, Scalar(0, 0, 255), 2, LINE_AA);
    }

    imshow("src", src);
    imshow("dst", dst);
    waitKey();
    destroyAllWindows();
}