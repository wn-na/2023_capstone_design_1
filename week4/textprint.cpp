#include <iostream>
#include "opencv2/opencv.hpp"

using namespace cv;

int main()
{
    Mat img(200, 640, CV_8UC3, Scalar(255, 255, 255));

    const String text = "Hello, OpenCV";
    int fontFace = FONT_HERSHEY_TRIPLEX;
    double fontScale = 2.0;
    int thinknes = 1;

    Size sizeText = getTextSize(text, fontFace, fontScale, thinknes, 0);
    Size sizeImg = img.size();

    Point org(
        (sizeImg.width - sizeText.width) / 2,
        (sizeImg.height + sizeText.height) / 2);

    putText(img, text, org, fontFace, fontScale, Scalar(255, 0, 0), thinknes);
    rectangle(img, org, org + Point(sizeText.width, -sizeText.height), Scalar(255, 0, 0), 1);

    imshow("img", img);
    waitKey(0);
}