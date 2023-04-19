#include <iostream>
#include "opencv2/opencv.hpp"

#ifndef BASE_IMAGE_PATH
#define BASE_IMAGE_PATH "./"
#endif
#define IMAGE_PATH(PATH) BASE_IMAGE_PATH PATH
using namespace cv;

int main()
{
    Mat img = cv::imread(IMAGE_PATH("lenna.bmp"));

    if (img.empty())
    {
        std::cerr << "Image load failed" << std::endl;
        return -1;
    }

    namedWindow("img");
    imshow("img", img);

    while (true)
    {
        int key = waitKey();

        if (key == 'i' || key == 'I')
        {
            img = ~img;
            imshow("img", img);
        }
        else if (key == 'q' || key == 'Q' || key == 27)
        {
            break;
        }
    }

    return 0;
}