#include <iostream>
#include "opencv2/opencv.hpp"

using namespace cv;

#define LEVEL 30
void onLevelChange(int pos, void *userdata);

int main()
{
    Mat img = Mat::zeros(400, 400, CV_8UC1);

    namedWindow("image");

    createTrackbar("level", "image", 0, LEVEL, onLevelChange, (void *)&img);

    imshow("image", img);

    waitKey(0);
    return 0;
}

void onLevelChange(int pos, void *userdata)
{
    Mat img = *(Mat *)userdata;

    img.setTo(pos * (256. / LEVEL));
    imshow("image", img);
}