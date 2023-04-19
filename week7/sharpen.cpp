#include <iostream>
#include "opencv2/opencv.hpp"

#ifndef BASE_IMAGE_PATH
#define BASE_IMAGE_PATH "./"
#endif
#define IMAGE_PATH(PATH) BASE_IMAGE_PATH PATH
using namespace cv;

int main()
{
    Mat src = cv::imread(IMAGE_PATH("rose.bmp"), IMREAD_GRAYSCALE);

    if (src.empty())
    {
        std::cerr << "Image load failed" << std::endl;
        return -1;
    }
    imshow("src", src);

    for (int sigma = 1; sigma <= 5; sigma++)
    {
        Mat blurred;
        GaussianBlur(src, blurred, Size(), (double)sigma);

        float alpha = 1.f;

        Mat dst = (1 + alpha) * src - alpha * blurred;

        String desc = format("sigma = %d", sigma);
        putText(dst, desc, Point(10, 30), FONT_HERSHEY_SIMPLEX, 1.0, Scalar(255), 1, LINE_AA);

        imshow(desc, dst);
        waitKey();
    }

    destroyAllWindows();
}