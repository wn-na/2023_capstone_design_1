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

    Mat ref, ref_ycrcb, mask;
    ref = imread(IMAGE_PATH("ref.png"), IMREAD_COLOR);
    mask = imread(IMAGE_PATH("mask.bmp"), IMREAD_GRAYSCALE);

    cvtColor(ref, ref_ycrcb, COLOR_BGR2YCrCb);

    Mat hist;
    int channels[] = {1, 2};
    int cr_bins = 128, cb_bins = 128;
    int histSize[] = {cr_bins, cb_bins};
    float cr_range[] = {0, 256};
    float cb_range[] = {0, 256};

    const float *ranges[] = {cr_range, cb_range};

    calcHist(&ref_ycrcb, 1, channels, mask, hist, 2, histSize, ranges);

    Mat src, src_ycrcb;
    src = imread(IMAGE_PATH("kids.png"), IMREAD_COLOR);
    cvtColor(src, src_ycrcb, COLOR_BGR2YCrCb);

    Mat backproj;
    calcBackProject(&src_ycrcb, 1, channels, hist, backproj, ranges, 1, true);

    imshow("src", src);
    imshow("hist", hist);
    imshow("backproj", backproj);

    waitKey();
    destroyAllWindows();
}