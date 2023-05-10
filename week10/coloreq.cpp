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
    Mat src = cv::imread(IMAGE_PATH("pepper.bmp"), IMREAD_COLOR);

    if (src.empty())
    {
        std::cerr << "Image not found" << std::endl;
        return -1;
    }
    Mat src_ycrcb;

    cvtColor(src, src_ycrcb, COLOR_BGR2YCrCb);

    vector<Mat> ycrcb_planes;
    split(src_ycrcb, ycrcb_planes);

    equalizeHist(ycrcb_planes[0], ycrcb_planes[0]);

    Mat dst_ycrcb;

    merge(ycrcb_planes, dst_ycrcb);

    Mat dst;
    cvtColor(dst_ycrcb, dst, COLOR_YCrCb2BGR);

    imshow("src", src);
    imshow("dst", dst);

    waitKey();
    destroyAllWindows();
    return 0;
}