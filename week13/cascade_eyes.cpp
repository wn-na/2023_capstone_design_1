#include <iostream>
#include "opencv2/opencv.hpp"

#ifndef BASE_IMAGE_PATH
#define BASE_IMAGE_PATH "./"
#endif
#define IMAGE_PATH(PATH) BASE_IMAGE_PATH PATH

#ifndef BASE_XML_PATH
#define BASE_XML_PATH "./"
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

    CascadeClassifier face_classifier(XML_PATH("haarcascade_frontalface_default.xml"));
    CascadeClassifier eye_classifier(XML_PATH("haarcascade_eye.xml"));

    if (face_classifier.empty() || eye_classifier.empty())
    {
        cerr << "XML load failed!" << endl;
        return -1;
    }

    vector<Rect> faces;
    face_classifier.detectMultiScale(src, faces);

    for (Rect face : faces)
    {
        rectangle(src, face, Scalar(255, 0, 255), 2);
        Mat faceROI = src(face);
        vector<Rect> eyes;
        eye_classifier.detectMultiScale(faceROI, eyes);

        for (Rect eye : eyes)
        {
            Point center(eye.x + eye.width / 2, eye.y + eye.height / 2);
            circle(faceROI, center, eye.width / 2, Scalar(255, 0, 0), 2, LINE_AA);
        }
    }

    imshow("src", src);

    waitKey();
    destroyAllWindows();
    return 0;
}