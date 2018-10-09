#include <iostream>
#include <opencv2/opencv.hpp>

#include "scoring.hpp"
#include "arguments.hpp"

int main(int argc, char** argv) {

	arguments_t args(argc, argv);

	if (args.parametersSize() < 2) {
		std::cout << "usage: " << argv[0] << " truth binary_image" << std::endl;
		return 0;
	}

	cv::Mat matTruth = cv::imread(args[0], cv::IMREAD_GRAYSCALE);
	if (!matTruth.data) {
		std::cout << "Cannot load " << args[0] << std::endl;
		return 0;
	}

	cv::Mat matOutput = cv::imread(args[1], cv::IMREAD_GRAYSCALE);
	if (!matOutput.data) {
		std::cout << "Cannot load " << args[1] << std::endl;
		return 0;
	}

	double precision, recall;
	score(matTruth, matOutput, 1, precision, recall);

	std::cout << recall << std::endl;

	return 0;
}
