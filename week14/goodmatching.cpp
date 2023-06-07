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
    Mat src1 = cv::imread(IMAGE_PATH("box.png"), IMREAD_GRAYSCALE);
    Mat src2 = cv::imread(IMAGE_PATH("box_in_scene.png"), IMREAD_GRAYSCALE);

    if (src1.empty() || src2.empty())
    {
        cerr << "Image load failed" << endl;
        return -1;
    }

    Ptr<Feature2D> feature = ORB::create();

    vector<KeyPoint> keypoints1, keypoints2;
    Mat desc1, desc2;
    feature->detectAndCompute(src1, Mat(), keypoints1, desc1);
    feature->detectAndCompute(src2, Mat(), keypoints2, desc2);

    Ptr<DescriptorMatcher> matcher = BFMatcher::create(NORM_HAMMING);

    vector<DMatch> matches;
    matcher->match(desc1, desc2, matches);

    sort(matches.begin(), matches.end());

    vector<DMatch> good_matches(matches.begin(), matches.begin() + 50);

    Mat dst;
    drawMatches(src1, keypoints1, src2, keypoints2, good_matches, dst,
                Scalar::all(-1), Scalar::all(-1), vector<char>(),
                DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS);

    imshow("dst", dst);

    waitKey();
    destroyAllWindows();
}