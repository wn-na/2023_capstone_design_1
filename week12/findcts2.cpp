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
    srand(time(NULL));
    Mat src = cv::imread(IMAGE_PATH("contours.bmp"), IMREAD_GRAYSCALE);

    if (src.empty())
    {
        cerr << "Error reading" << endl;
        return -1;
    }

    vector<vector<Point>> contours;
    vector<Vec4i> hierarchy;
    findContours(src, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE);

    Mat dst;
    cvtColor(src, dst, COLOR_GRAY2BGR);

    for (int i = 0; i < contours.size(); i++)
    {
        Scalar c(rand() & 255, rand() & 255, rand() & 255);
        drawContours(dst, contours, i, c, -1, LINE_8, hierarchy);
    }

    imshow("src", src);
    imshow("dst", dst);

    waitKey();
    destroyAllWindows();
}