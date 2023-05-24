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
    Mat src = cv::imread(IMAGE_PATH("beta.png"), IMREAD_GRAYSCALE);

    if (src.empty())
    {
        cerr << "Image load failed" << endl;
        return -1;
    }

    Mat bin;
    vector<vector<Point>> contours;
    vector<Vec4i> hierarchy;

    threshold(src, bin, 128, 255, THRESH_BINARY | THRESH_OTSU);
    morphologyEx(bin, bin, MORPH_OPEN, Mat(), Point(-1, -1), 1);

    findContours(bin, contours, hierarchy, RETR_TREE, CHAIN_APPROX_NONE);

    Mat dst;
    cvtColor(src, dst, COLOR_GRAY2BGR);

    for (int idx = 0; idx >= 0; idx = hierarchy[idx][0])
    {
        Scalar c(rand() & 255, rand() & 255, rand() & 255);
        drawContours(dst, contours, idx, c, 2, LINE_AA, hierarchy, 2, Point(0, 0));

        Rect rect = boundingRect(contours[idx]);
        rectangle(dst, rect, Scalar(0, 0, 255), 2, LINE_AA, 0);

        RotatedRect rrect = minAreaRect(contours[idx]);
        Point2f vertices[4];
        rrect.points(vertices);
        for (int i = 0; i < 4; i++)
        {
            line(dst, vertices[i], vertices[(i + 1) % 4], Scalar(255, 0, 0), 2, LINE_AA, 0);
        }

        float angle = rrect.angle;
        cout << "\nrotated angle : " << cvRound(angle) << endl;

        Point2f center;
        float radius;
        minEnclosingCircle(contours[idx], center, radius);
        circle(dst, center, radius, Scalar(0, 255, 255), 2, LINE_AA, 0);

        double len = arcLength(contours[idx], true);
        cout << "\nlength of contours: " << cvRound(len) << endl;

        double area = contourArea(contours[idx], false);
        cout << "\narea of contours: " << cvRound(area) << endl;
    }

    imshow("src", src);
    imshow("dst", dst);

    waitKey();
    destroyAllWindows();
}