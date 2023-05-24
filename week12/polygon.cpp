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

void setLabel(Mat &img, const vector<Point> &pts, const String &label)
{
    Rect rc = boundingRect(pts);
    rectangle(img, rc, Scalar(0, 0, 255), 1);
    putText(img, label, rc.tl(), FONT_HERSHEY_PLAIN, 1, Scalar(0, 0, 255));
}

int main()
{
    srand(time(NULL));
    Mat src = cv::imread(IMAGE_PATH("polygon.bmp"), IMREAD_GRAYSCALE);

    if (src.empty())
    {
        cerr << "Image load failed" << endl;
        return -1;
    }

    Mat gray;
    cvtColor(src, gray, COLOR_GRAY2BGR);

    Mat bin;
    threshold(src, bin, 128, 255, THRESH_BINARY_INV | THRESH_OTSU);

    vector<vector<Point>> contours;
    findContours(bin, contours, RETR_EXTERNAL, CHAIN_APPROX_NONE);

    for (vector<Point> &pts : contours)
    {
        if (contourArea(pts) < 400)
            continue;

        vector<Point> approx;
        approxPolyDP(pts, approx, arcLength(pts, true) * 0.02, true);

        int vtc = (int)approx.size();

        if (vtc == 3)
        {
            setLabel(src, pts, "TRI");
        }
        else if (vtc == 4)
        {
            setLabel(src, pts, "RECT");
        }
        else if (vtc > 4)
        {
            double len = arcLength(pts, true);
            double area = contourArea(pts);
            double ratio = 4. * CV_PI * area / (len * len);

            if (ratio > 0.8)
            {
                setLabel(src, pts, "CIR");
            }
        }
    }

    imshow("src", src);

    waitKey();
    destroyAllWindows();
}