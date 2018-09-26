#include <opencv2/opencv.hpp>
#include <iostream>
#include "tools.hpp"

int main(int argc, char** argv) {
	if (argc < 3) {
		std::cout << "usage: ./sobel image_entree image_binaire_sortie" << std::endl;
		return 0;
	}

	auto imageIn = cv::imread(argv[1], cv::IMREAD_GRAYSCALE);
	if (!imageIn.data)
	{
		std::cout << "Could not open or find the image" << std::endl;
		return -1;
	}

	/*cv::Mat imageBlured = gaussianFilter(imageIn, 21, 10);
	cv::imshow("blured", imageBlured);
	cv::waitKey();*/

	sobelFilter(imageIn);
	cv::imshow("edges", imageIn);
	cv::waitKey();

	uchar threshold = 200;
	if (argc >= 4)
		threshold = std::stoi(argv[3]);

	binaryFilter(imageIn, threshold);
	cv::imshow("imageOut", imageIn);
	cv::waitKey();

	cv::imwrite(argv[2], imageIn);
	return 0;
}