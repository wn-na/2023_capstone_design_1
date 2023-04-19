#include <iostream>
#include "opencv2/opencv.hpp"
using namespace std;
using namespace cv;

String filename = "data/mydata.csv";

void writeData();
int main()
{
    writeData();
    return 0;
}

void writeData()
{
    String name = "Jane";
    int age = 10;
    Point pt1(100, 200);
    vector<int> scores = {80, 90, 50};
    Mat mat1 = (Mat_<float>(2, 2) << 1.0f, 1.5f, 2.0f, 3.2f);

    FileStorage fs(filename, FileStorage::WRITE | FileStorage::FORMAT_JSON);

    if (!fs.isOpened())
    {
        std::cout << "File open failed!" << std::endl;
        return;
    }

    fs << "name" << name;
    fs << "age" << age;
    fs << "point" << pt1;
    fs << "scores" << scores;
    fs << "data" << mat1;

    fs.release();
}