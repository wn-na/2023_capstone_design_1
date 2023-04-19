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

int delay = cvRound(1000 / 24);

Mat getCapImage(bool isGrayMode);
void showImage(char *title, Mat image);

int main()
{
    Mat src = getCapImage(false);

    int num = (int)(src.total() * 0.1);
    for (int i = 0; i < num; i++)
    {
        int x = rand() % src.cols;
        int y = rand() % src.rows;
        if (src.type() == CV_8UC1)
        {
            src.at<uchar>(y, x) = (i % 2) * 255;
        }
        else
        {
            src.at<Vec3b>(y, x)[0] = (i % 2) * 255;
            src.at<Vec3b>(y, x)[1] = (i % 2) * 255;
            src.at<Vec3b>(y, x)[2] = (i % 2) * 255;
        }
    }

    Mat dst1;
    GaussianBlur(src, dst1, Size(), 1);

    Mat dst2;
    medianBlur(src, dst2, 3);

    showImage("src", src);
    showImage("dst1", dst1);
    showImage("dst2", dst2);

    waitKey();
    destroyAllWindows();
}

Mat getCapImage(bool isGrayMode = true)
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

    if (isGrayMode)
    {
        cvtColor(frame, frame, COLOR_BGR2GRAY);
    }
    return frame;
}

void showImage(char *title, Mat image)
{
    imwrite(format("%s.bmp", title), image);
    imshow(title, image);
}