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
    Mat src = cv::imread(IMAGE_PATH("keyboard.bmp"), IMREAD_GRAYSCALE);

    if (src.empty())
    {
        cerr << "Error reading" << endl;
        return -1;
    }

    Mat bin;
    morphologyEx(src, bin, MORPH_OPEN, Mat()); // ?
    threshold(bin, bin, 0, 255, THRESH_BINARY | THRESH_OTSU);

    Mat labels, stats, centroids;
    int cnt = connectedComponentsWithStats(bin, labels, stats, centroids);

    Mat dst;
    cvtColor(src, dst, COLOR_GRAY2BGR);

    for (int i = 1; i < cnt; i++)
    {
        int *p = stats.ptr<int>(i);

        if (p[4] < 20)
            continue;

        rectangle(dst, Rect(p[0], p[1], p[2], p[3]), Scalar(0, 255, 255), 2);
        String name = format("%d", i);
        putText(dst, name, Point(cvRound(p[0] + (p[2]) / 2), cvRound(p[1] + (p[3]) / 2)), FONT_HERSHEY_PLAIN, 1.2, Scalar(0, 0, 255), 1, LINE_AA);
    }

    imshow("src", src);
    imshow("dst", dst);

    waitKey();
    destroyAllWindows();
}