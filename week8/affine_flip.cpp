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
    Mat src = cv::imread(IMAGE_PATH("eastsea.bmp"));

    if (src.empty())
    {
        cerr << "Image load failed!" << endl;
        return -1;
    }

    imshow("src", src);

    Mat dst;

    int flipCode[] = {1, 0, -1};
    for (int i = 0; i < 3; i++)
    {
        flip(src, dst, flipCode[i]);
        String desc = format("flipCode: %d", flipCode[i]);
        String title = format("dst%d", flipCode[i]);
        putText(dst, desc, Point(10, 30), FONT_HERSHEY_SIMPLEX, 1.0, Scalar(255, 0, 0), 1, LINE_AA);

        imshow(title, dst);

        waitKey();
    }
    destroyAllWindows();
}