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
    Mat src = cv::imread(IMAGE_PATH("candies.png"));

    if (src.empty())
    {
        std::cerr << "Image not found" << std::endl;
        return -1;
    }

    vector<Mat> bgr_planes;
    split(src, bgr_planes);

    imshow("src", src);
    imshow("b", bgr_planes[0]);
    imshow("g", bgr_planes[1]);
    imshow("r", bgr_planes[2]);

    waitKey();
    destroyAllWindows();
}