#include <iostream>
#include "opencv2/opencv.hpp"

#ifndef BASE_IMAGE_PATH
#define BASE_IMAGE_PATH "./"
#endif
#define IMAGE_PATH(PATH) BASE_IMAGE_PATH PATH
using namespace cv;

void contrast2();
int main()
{
    contrast2();
    return 0;
}

void contrast2()
{
    Mat src = cv::imread(IMAGE_PATH("lenna.bmp"), IMREAD_GRAYSCALE);

    if (src.empty())
    {
        std::cout << "Image load failed!" << std::endl;
        return;
    }

    float alpha = 1.f;
    // dst(x, y) = saturate(src(x, y) + (src(x, y) - 128) * alpha)
    // 밝기의 간격 -> 그라데이션
    // 이런 단순식은 좋은 영상처리는 아님
    // 그래서 보통 s자 곡선함수로 만듬
    Mat dst = src + (src - 128) * alpha;

    imshow("src", src);
    imshow("dst", dst);

    waitKey();
    destroyAllWindows();
}