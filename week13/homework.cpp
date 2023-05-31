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

void save_image(const Mat &frame);
int main()
{
    VideoCapture cap(0);

    if (!cap.isOpened())
    {
        cerr << "Video open failed" << endl;
        return -1;
    }

    CascadeClassifier face_classifier(XML_PATH("haarcascade_frontalface_default.xml"));
    CascadeClassifier eye_classifier(XML_PATH("haarcascade_eye.xml"));

    if (face_classifier.empty() || eye_classifier.empty())
    {
        cerr << "XML load failed!" << endl;
        return -1;
    }

    Mat frame;
    while (true)
    {
        cap >> frame;
        if (frame.empty())
            break;

        vector<Rect> faces;
        face_classifier.detectMultiScale(frame, faces);

        for (Rect face : faces)
        {
            rectangle(frame, face, Scalar(255, 0, 255), 2);
            Mat faceROI = frame(face);
            vector<Rect> eyes;
            eye_classifier.detectMultiScale(faceROI, eyes);

            for (Rect eye : eyes)
            {
                Point center(eye.x + eye.width / 2, eye.y + eye.height / 2);
                circle(faceROI, center, eye.width / 2, Scalar(255, 0, 0), 2, LINE_AA);
            }
        }

        imshow("frame", frame);
        int key = waitKey(1);
        if (key == 27)
        {
            break;
        }
        else if (key == 'S' || key == 's')
        {
            save_image(frame);
        }
    }
    return 0;
}

void save_image(const Mat &frame)
{
    Mat dst, bin_color, bin_gray, canny;
    imwrite("homework.png", frame);

    cvtColor(frame, dst, COLOR_BGR2GRAY);
    threshold(dst, bin_gray, 125, 255, THRESH_BINARY | THRESH_OTSU);
    imwrite("homework_bin_gray.png", bin_gray);

    threshold(frame, bin_color, 125, 255, THRESH_BINARY);
    imwrite("homework_bin.png", bin_color);

    Canny(bin_gray, canny, 50, 150);
    imwrite("homework_canny_gray.png", canny);

    Canny(bin_color, canny, 50, 150);
    imwrite("homework_canny.png", canny);
}