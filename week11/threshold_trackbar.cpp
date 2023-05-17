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

void on_threshold(int, void *);
Mat calcGrayHist(const Mat &img);
Mat getGrayHistImage(const Mat &hist, const Mat &src);

int main(int argc, char **argv)
{

    Mat src;

    if (argc < 2)
    {
        src = imread(IMAGE_PATH("neutrophils.png"), IMREAD_GRAYSCALE);
    }
    else
    {
        src = imread(argv[1], IMREAD_GRAYSCALE);
    }

    if (src.empty())
    {
        cerr << "Image load failed!" << endl;
    }

    imshow("src", src);
    Mat hist = calcGrayHist(src);
    Mat hist_image = getGrayHistImage(hist, src);

    imshow("hist_image", hist_image);

    namedWindow("dst");
    createTrackbar("Threshold", "dst", 0, 255, on_threshold, (void *)&src);
    setTrackbarPos("Threshold", "dst", 128);

    waitKey();
    destroyAllWindows();
    return 0;
}

void on_threshold(int pos, void *userdata)
{
    Mat src = *(Mat *)userdata;

    Mat dst;
    threshold(src, dst, pos, 255, THRESH_BINARY);

    imshow("dst", dst);
}

Mat calcGrayHist(const Mat &img)
{
    CV_Assert(img.type() == CV_8UC1);

    Mat hist;
    int channels[] = {0};
    int dims = 1;
    const int histSize[] = {256};
    float graylevel[] = {0, 256};
    const float *ranges[] = {graylevel};

    calcHist(&img, 1, channels, noArray(), hist, dims, histSize, ranges);

    return hist;
}

Mat getGrayHistImage(const Mat &hist, const Mat &src)
{
    CV_Assert(hist.type() == CV_32FC1);
    CV_Assert(hist.size() == Size(1, 256));

    double histMax;
    minMaxLoc(hist, 0, &histMax);

    int width = src.cols;
    int height = src.rows;

    Mat imgHist(height, width, CV_8UC3, Scalar(255, 255, 255));
    for (int i = 0; i < 256; i++)
    {
        line(imgHist,
             Point(cvRound(i * width / 256), height),
             Point(cvRound(i * width / 256), height - cvRound(hist.at<float>(i, 0) / histMax * height)),
             Scalar(255, 200, 0),
             1
             //  cvRound(width / 256)
        );
    }

    return imgHist;
}