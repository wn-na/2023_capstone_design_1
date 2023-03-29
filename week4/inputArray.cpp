#include <iostream>
#include "opencv2/opencv.hpp"

using namespace cv;

void InputArrayOp();
void printMat(InputArray _mat);

int main()
{
    InputArrayOp();
}

void InputArrayOp()
{
    uchar data1[] = {1, 2, 3, 4, 5, 6};
    Mat mat1(2, 3, CV_8U, data1);
    printMat(mat1);

    std::vector<float> vec1 = {1.2f, 3.4f, -2.1f};
    printMat(vec1);
}

void printMat(InputArray _mat)
{
    Mat mat = _mat.getMat();
    std::cout << mat << std::endl;
}