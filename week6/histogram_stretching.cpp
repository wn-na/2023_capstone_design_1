#include <iostream>
#include "opencv2/opencv.hpp"

#ifndef BASE_IMAGE_PATH
#define BASE_IMAGE_PATH "./"
#endif
#define IMAGE_PATH(PATH) BASE_IMAGE_PATH PATH
using namespace cv;
using namespace std;

#define HEIGHT 256
#define WIDTH 256

int delay = cvRound(1000 / 24);

Mat calcGrayHist(const Mat &img);
Mat getGrayHistImage(const Mat &hist);
Mat getCapImage();
void histogram_streching();
int main()
{
    histogram_streching();
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

    Mat imgHist(HEIGHT, WIDTH, CV_8UC3, Scalar(255, 255, 255));
    for (int i = 0; i < 256; i++)
    {
        // 100인 이유는 아래에서 위로 그려야하기 때문
        line(imgHist,
             Point(i * cvRound(WIDTH / 256), HEIGHT),
             Point(i * cvRound(WIDTH / 256), HEIGHT - cvRound(hist.at<float>(i, 0) / histMax * HEIGHT)),
             Scalar(1),
             cvRound(WIDTH / 256));
    }
    return imgHist;
}

Mat getCapImage()
{
    VideoCapture cap(0);
    cap.set(CAP_PROP_FRAME_WIDTH, WIDTH);
    cap.set(CAP_PROP_FRAME_HEIGHT, HEIGHT);

    if (!cap.isOpened())
    {
        std::cerr << "Camera open failed!" << std::endl;
        return Mat();
    }

    Mat frame;

    while (true)
    {
        cap >> frame;
        if (frame.empty())
        {
            break;
        }
        imshow("src", frame);
        if (waitKey(delay) == 27)
        {
            break;
        }
    }
    resize(frame, frame, Size(WIDTH, HEIGHT), 0, 0, INTER_LINEAR);
    return frame;
}

void histogram_streching()
{
    Mat frame = getCapImage();
    Mat src;

    cvtColor(frame, src, COLOR_BGR2GRAY);

    double gmin, gmax;
    minMaxLoc(src, &gmin, &gmax);

    Mat dst = (src - gmin) * 255 / (gmax - gmin);

    Mat srcHist = getGrayHistImage(calcGrayHist(src));
    Mat dstHist = getGrayHistImage(calcGrayHist(dst));

    imshow("src", src);
    imshow("srcHist", srcHist);

    imshow("dst", dst);
    imshow("dstHist", dstHist);

    imwrite("src.bmp", src);
    imwrite("srcHist.bmp", srcHist);
    imwrite("dst.bmp", dst);
    imwrite("dstHist.bmp", dstHist);

    waitKey();
    destroyAllWindows();
}