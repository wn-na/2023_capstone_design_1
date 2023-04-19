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
    String name;
    int age;
    Point pt1;
    vector<int> scores;
    Mat mat1;

    FileStorage fs(filename, FileStorage::READ | FileStorage::FORMAT_JSON);

    if (!fs.isOpened())
    {
        std::cout << "File open failed!" << std::endl;
        return;
    }

    fs["name"] >> name;
    fs["age"] >> age;
    fs["points"] >> pt1;
    fs["scores"] >> scores;
    fs["data"] >> mat1;

    fs.release();

    std::cout << name << std::endl;

    std::cout << age << std::endl;

    std::cout << pt1 << std::endl;

    std::cout << Mat(scores).t() << std::endl;

    std::cout << mat1 << std::endl;
}