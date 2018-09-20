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

	cv::Mat edges = sobelFilter(imageIn);
	cv::Mat binary = binary(edges, 127);
	cv::Mat cracks = clusterRemoval(binary, 18);
	cv::imshow("image", cracks);
	cv::waitKey();

	//cv::imwrite(argv[2], binary);
	return 0;
}