#include <iostream>
#include "opencv2/opencv.hpp"

#ifndef BASE_IMAGE_PATH
#define BASE_IMAGE_PATH "./"
#endif
#define IMAGE_PATH(PATH) BASE_IMAGE_PATH PATH
using namespace cv;

Mat calcGrayHist(const Mat &img);
Mat getGrayHistImage(const Mat &hist);
int main()
{
    Mat src = cv::imread(IMAGE_PATH("cameraman256.bmp"), IMREAD_GRAYSCALE);

    if (src.empty())
    {
        std::cout << "Image load failed!" << std::endl;
        return -1;
    }

    // Mat dst;
    // equalizeHist(src, dst);
    Mat hist = calcGrayHist(src);
    Mat hist_image = getGrayHistImage(hist);

    imshow("src", src);
    imshow("hist_image", hist_image);

    waitKey();
    destroyAllWindows();
    return 0;
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

Mat getGrayHistImage(const Mat &hist)
{
    CV_Assert(hist.type() == CV_32FC1);
    CV_Assert(hist.size() == Size(1, 256));

    double histMax;
    minMaxLoc(hist, 0, &histMax);

    int width = 300;
    int height = 200;

    Mat imgHist(height, width, CV_8UC3, Scalar(255, 255, 255));
    for (int i = 0; i < 256; i++)
    {
        // 100인 이유는 아래에서 위로 그려야하기 때문
        line(imgHist,
             Point(i * cvRound(width / 256), height),
             Point(i * cvRound(width / 256), height - cvRound(hist.at<float>(i, 0) / histMax * height)),
             Scalar(255, 200, 0),
             cvRound(width / 256));
    }

    return imgHist;
}