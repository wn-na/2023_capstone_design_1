#include <iostream>
#include "opencv2/opencv.hpp"

#ifndef BASE_IMAGE_PATH
#define BASE_IMAGE_PATH "./"
#endif
#define IMAGE_PATH(PATH) BASE_IMAGE_PATH PATH

using namespace cv;

void camera_in_video_out()
{
    VideoCapture cap(0);

    if (!cap.isOpened())
    {
        std::cerr << "Video open failed!" << std::endl;
        return;
    }

    int w = cvRound(cap.get(CAP_PROP_FRAME_WIDTH));
    int h = cvRound(cap.get(CAP_PROP_FRAME_HEIGHT));
    double fps = cap.get(CAP_PROP_FPS);

    int fourcc = VideoWriter::fourcc('D', 'I', 'V', 'X');
    int delay = cvRound(1000 / fps);

    VideoWriter outputVideo("output.avi", fourcc, fps, Size(w, h));

    if (!outputVideo.isOpened())
    {
        std::cout << "File open failed!" << std::endl;
    }

    Mat frame, inversed;
    while (true)
    {
        cap >> frame;
        if (frame.empty())
        {
            break;
        }

        inversed = ~frame;
        outputVideo << inversed;

        imshow("frame", frame);
        imshow("inversed", inversed);
        if (waitKey(delay) == 27)
        {
            break;
        }
    }
    destroyAllWindows();
}

int main()
{
    camera_in_video_out();
}