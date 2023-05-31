#include <iostream>
#include "opencv2/opencv.hpp"

#ifndef BASE_IMAGE_PATH
#define BASE_IMAGE_PATH "./"
#endif
#define IMAGE_PATH(PATH) BASE_IMAGE_PATH PATH

#ifndef BASE_XML_PATH
#define BASE_XML_PATH "/opt/homebrew/Cellar/opencv/4.7.0_2/share/opencv4/haarcascades/"
#endif
#define XML_PATH(PATH) BASE_XML_PATH PATH

using namespace cv;
using namespace std;

#define HEIGHT 512
#define WIDTH 512

int main()
{
    Mat src = cv::imread(IMAGE_PATH("kids.png"));

    if (src.empty())
    {
        cerr << "Image load failed!" << endl;
        return -1;
    }

    CascadeClassifier classifier(XML_PATH("haarcascade_frontalface_default.xml"));

    if (classifier.empty())
    {
        cerr << "XML load failed!" << endl;
        return -1;
    }

    vector<Rect> faces;
    classifier.detectMultiScale(src, faces);

    for (Rect rc : faces)
    {
        rectangle(src, rc, Scalar(255, 0, 255), 2);
    }

    imshow("src", src);

    waitKey();
    destroyAllWindows();
    return 0;
}