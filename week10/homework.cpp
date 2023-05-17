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

    Mat ref, mask;
    ref = imread(IMAGE_PATH("ref.png"), IMREAD_COLOR);
    mask = imread(IMAGE_PATH("mask.bmp"), IMREAD_GRAYSCALE);

    int channels[] = {1, 2};
    int cr_bins = 128, cb_bins = 128;
    int histSize[] = {cr_bins, cb_bins};
    float cr_range[] = {0, 256};
    float cb_range[] = {0, 256};

    const float *ranges[] = {cr_range, cb_range};

    Mat faceOnly;
    copyTo(ref, faceOnly, mask);

    Mat faceOnly_ycrcb;
    Mat faceOnly_hist;
    cvtColor(faceOnly, faceOnly_ycrcb, COLOR_BGR2YCrCb);

    calcHist(&faceOnly_ycrcb, 1, channels, mask, faceOnly_hist, 2, histSize, ranges);

    Mat result = Mat::zeros(Size(faceOnly_hist.cols * 3, faceOnly_hist.rows * 3), CV_8UC1);

    for (int j = 0; j < faceOnly_hist.rows; j++)
    {
        for (int i = 0; i <= faceOnly_hist.cols; i++)
        {
            if (faceOnly_hist.at<float>(j, i))
            {
                result.at<uchar>(j * 3, i * 3) = 255;
            }
        }
    }

    imshow("faceOnly", faceOnly);
    imshow("result", result);
    waitKey();
    destroyAllWindows();
}