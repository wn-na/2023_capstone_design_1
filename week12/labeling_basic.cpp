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
    uchar data[] = {
        0, 0, 1, 1, 0, 0, 0, 0,
        1, 1, 1, 1, 0, 0, 1, 0,
        1, 1, 1, 1, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 1, 1, 0,
        0, 0, 0, 1, 1, 1, 1, 0,
        0, 0, 0, 1, 0, 0, 1, 0,
        0, 0, 1, 1, 1, 1, 1, 0,
        0, 0, 0, 0, 0, 0, 0, 0};

    Mat src = Mat(8, 8, CV_8UC1, data) * 255;

    Mat labels;
    int cnt = connectedComponents(src, labels);

    cout << "src\n"
         << src << endl;
    cout << "labels\n"
         << labels << endl;
    cout << "number of labels\n"
         << cnt << endl;
}