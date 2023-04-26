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
    Mat src = cv::imread(IMAGE_PATH("rose.bmp"));

    if (src.empty())
    {
        cerr << "Image load failed!" << endl;
        return -1;
    }

    Mat dst1, dst2, dst3, dst4;
    resize(src, dst1, Size(), 4, 4, INTER_NEAREST);
    resize(src, dst2, Size(1920, 1280));
    resize(src, dst3, Size(1920, 1280), 0, 0, INTER_CUBIC);
    resize(src, dst4, Size(1920, 1280), 0, 0, INTER_LANCZOS4);

    imshow("src", src);
    imshow("dst1", dst1(Rect(400, 500, 400, 400)));
    imshow("dst2", dst2(Rect(400, 500, 400, 400)));
    imshow("dst3", dst3(Rect(400, 500, 400, 400)));
    imshow("dst4", dst4(Rect(400, 500, 400, 400)));

    waitKey();
    destroyAllWindows();
}