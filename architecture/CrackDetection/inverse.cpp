#include <opencv2/opencv.hpp>
#include <stdio.h>
#include <iostream>

using namespace std;
using namespace cv;

int main(int argc, char** argv) {

	if (argc < 3) {
		std::cout << "usage: ./inverse image_entree image_binaire_sortie" << std::endl;
		return 0;
	}

	auto imageIn = imread(argv[1], IMREAD_GRAYSCALE);
	if (!imageIn.data)
	{
		cout << "Could not open or find the image" << std::endl;
		return -1;
	}

	auto imageOut = imageIn.clone();
	
	for (int i = 0; i < imageOut.rows; i++)
	{
		for (int j = 0; j < imageOut.cols; j++)
		{
			imageOut.at<char>(Point(j, i)) = 255 - imageOut.at<char>(Point(j, i));
		}
	}
	
	imwrite(argv[2], imageOut);
	return 0;
}