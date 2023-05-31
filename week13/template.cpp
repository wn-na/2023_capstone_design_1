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
    Mat img = cv::imread(IMAGE_PATH("circuit.bmp"), IMREAD_COLOR);
    Mat templ = cv::imread(IMAGE_PATH("crystal.bmp"), IMREAD_COLOR);

    if (img.empty() || templ.empty())
    {
        cerr << "Image load failed!" << endl;
        return -1;
    }

    img = img + Scalar(50, 50, 50);

    Mat noise(img.size(), CV_32SC3);
    randn(noise, 0, 10);
    add(img, noise, img, Mat(), CV_8UC3);

    Mat res, res_norm;
    matchTemplate(img, templ, res, TM_CCOEFF_NORMED);
    normalize(res, res_norm, 0, 255, NORM_MINMAX, CV_8U);

    double maxv;
    Point maxloc;
    minMaxLoc(res, 0, &maxv, 0, &maxloc);

    cout << "maxv: " << maxv << endl;

    rectangle(img, Rect(maxloc.x, maxloc.y, templ.cols, templ.rows), Scalar(0, 0, 255), 2);

    imshow("templ", templ);
    imshow("res_norm", res_norm);
    imshow("img", img);

    waitKey();
    destroyAllWindows();
    return 0;
}