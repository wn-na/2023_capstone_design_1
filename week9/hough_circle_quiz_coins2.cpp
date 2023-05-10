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
    Mat src = cv::imread("coins2.jpg", IMREAD_GRAYSCALE);

    if (src.empty())
    {
        std::cerr << "Image load failed" << std::endl;
        return -1;
    }

    Mat gaussian;

    medianBlur(src, gaussian, 3);
    GaussianBlur(gaussian, gaussian, Size(), (double)7);
    imshow("sharpening2", gaussian);

    float alpha = 1.f;

    Mat blurred = ((1 + alpha) * src - alpha * gaussian);
    resize(blurred, blurred, Size(blurred.size().width, blurred.size().height * 1.15));
    imshow("sharpening", blurred);

    vector<Vec3f> circles;
    HoughCircles(blurred, circles, HOUGH_GRADIENT, 0.9, 10, 100, 45, 20, 40);

    Mat dst;
    cvtColor(src, dst, COLOR_GRAY2RGB);

    for (Vec3f c : circles)
    {
        Point center(cvRound(c[0]), cvRound(c[1] / 1.15));
        int radius = cvRound(c[2]);
        circle(dst, center, radius, Scalar(0, 0, 255), 1, LINE_AA);
    }

    imshow("dst", dst);
    imwrite("quiz_coins2.jpg", dst);
    waitKey();
    destroyAllWindows();
}