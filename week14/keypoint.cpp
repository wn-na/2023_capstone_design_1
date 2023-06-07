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
    Mat src = cv::imread(IMAGE_PATH("box_in_scene.png"), IMREAD_GRAYSCALE);

    if (src.empty())
    {
        cerr << "Image load failed" << endl;
        return -1;
    }

    Ptr<Feature2D> feature = ORB::create();

    vector<KeyPoint> keypoints;
    feature->detect(src, keypoints);

    Mat desc;
    feature->compute(src, keypoints, desc);

    cout << "keypoints.size(): " << keypoints.size() << endl;
    cout << "desc.size(): " << desc.size() << endl;

    Mat dst;
    drawKeypoints(src, keypoints, dst, Scalar::all(-1), DrawMatchesFlags::DRAW_RICH_KEYPOINTS);

    imshow("src", src);
    imshow("dst", dst);

    waitKey();
    destroyAllWindows();
}