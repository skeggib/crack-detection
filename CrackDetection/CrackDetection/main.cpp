#include <opencv2/opencv.hpp>
#include <stdio.h>
#include <iostream>

using namespace std;
using namespace cv;

int main(int argc, char** argv) {

	Mat imageIn = imread(argv[1], IMREAD_GRAYSCALE);
	if (!imageIn.data)
	{
		cout << "Could not open or find the image" << std::endl;
		return -1;
	}
	imshow("Display window", imageIn);
	waitKey(0);
	return 0;
}