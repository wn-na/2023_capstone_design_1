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

void on_trackbar(int, void *);
Mat calcGrayHist(const Mat &img);
Mat getGrayHistImage(const Mat &hist, const Mat &src);

int main(int argc, char **argv)
{

    Mat src = imread(IMAGE_PATH("sudoku.jpg"), IMREAD_GRAYSCALE);

    if (src.empty())
    {
        cerr << "Image load failed!" << endl;
    }

    imshow("src", src);

    namedWindow("dst");
    createTrackbar("Block Size", "dst", 0, 200, on_trackbar, (void *)&src);
    setTrackbarPos("Block Size", "dst", 11);

    waitKey();
    destroyAllWindows();
    return 0;
}

void on_trackbar(int pos, void *userdata)
{
    Mat src = *(Mat *)userdata;

    int bsize = pos;

    if (bsize % 2 == 0)
        bsize--;
    if (bsize < 3)
        bsize = 3;

    Mat dst;
    adaptiveThreshold(src, dst, 255, ADAPTIVE_THRESH_GAUSSIAN_C, THRESH_BINARY, bsize, 5);

    imshow("dst", dst);
}