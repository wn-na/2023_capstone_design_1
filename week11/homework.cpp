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

int delay = 100;
Mat getCapImage(bool isGrayMode, int limit);

int main()
{
    Mat src = getCapImage(true, 10);

    Mat bin;
    (int)threshold(src, bin, 0, 255, THRESH_BINARY | THRESH_OTSU);

    Mat dst1, dst2, gradient, canny;
    morphologyEx(bin, dst1, MORPH_OPEN, Mat());
    morphologyEx(bin, dst2, MORPH_CLOSE, Mat());
    morphologyEx(bin, gradient, MORPH_GRADIENT, Mat());
    Canny(bin, canny, 50, 150);

    imshow("src", src);
    imshow("bin", bin);
    imshow("MORPH_OPEN(erode)", dst1);
    imshow("MORPH_CLOSE(dilate)", dst2);
    imshow("MORPH_GRADIENT", gradient);
    imshow("Canny", canny);

    imwrite("Canny.jpg", canny);
    imwrite("MORPH_GRADIENT.jpg", gradient);

    waitKey();
    destroyAllWindows();
}

Mat getCapImage(bool isGrayMode = true, int limit = -1)
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
        if (waitKey(delay) == 27 || limit == 0)
        {
            break;
        }
        if (limit > 0)
        {
            limit--;
        }
    }
    resize(frame, frame, Size(WIDTH, HEIGHT), 0, 0, INTER_LINEAR);

    if (isGrayMode)
    {
        cvtColor(frame, frame, COLOR_BGR2GRAY);
    }
    return frame;
}
