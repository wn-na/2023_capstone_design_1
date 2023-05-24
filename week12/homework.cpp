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
    Mat src = cv::imread(IMAGE_PATH("kmap_simple.jpg"), IMREAD_GRAYSCALE);

    if (src.empty())
    {
        cerr << "Image load failed" << endl;
        return -1;
    }

    Mat bin;
    vector<vector<Point>> contours;
    vector<Vec4i> hierarchy;

    threshold(src, bin, 128, 255, THRESH_BINARY_INV | THRESH_OTSU);
    findContours(bin, contours, hierarchy, RETR_TREE, CHAIN_APPROX_NONE);

    Mat dst;
    cvtColor(src, dst, COLOR_GRAY2BGR);

    for (int idx = 0; idx >= 0; idx = hierarchy[idx][0])
    {
        Scalar c(rand() & 255, rand() & 255, rand() & 255);
        drawContours(dst, contours, idx, c, 2, LINE_AA, hierarchy, 2, Point(0, 0));

        vector<Point> approxCurve;
        approxPolyDP(contours[idx], approxCurve, arcLength(contours[idx], true) * 0.005, true);

        int no_vertex = approxCurve.size();
        cout << "the number of vertex: " << no_vertex << endl;

        for (int v = 0; v < no_vertex; v++)
        {
            circle(dst, approxCurve[v], 3, Scalar(0, 0, 255), 2);
            line(dst, approxCurve[v], approxCurve[(v + 1) % no_vertex], Scalar(255, 255, 0), 2);
        }
    }

    String title = format("%s %s", "number", "name");
    putText(dst, title, Point(10, 30), FONT_HERSHEY_PLAIN, 1, Scalar(0, 0, 255));
    imshow("src", src);
    imshow("dst", dst);

    imwrite("result.png", dst);

    waitKey();
    destroyAllWindows();
}