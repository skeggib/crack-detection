#include <iostream>
#include <opencv2/opencv.hpp>
#include "scoring.hpp"

int main(int argc, char** argv) {
	if (argc < 3) {
		std::cout << "usage: ./evaluation image_binaire_verite terrain_image_binaire_sortie" << std::endl;
		return 0;
	}

	auto pathTruth = argv[1];
	auto pathOutput = argv[2];

	cv::Mat matTruth = cv::imread(pathTruth, cv::IMREAD_GRAYSCALE);
	if (!matTruth.data) {
		std::cout << "Cannot load " << pathTruth << std::endl;
		return 0;
	}

	cv::Mat matOutput = cv::imread(pathOutput, cv::IMREAD_GRAYSCALE);
	if (!matOutput.data) {
		std::cout << "Cannot load " << pathOutput << std::endl;
		return 0;
	}

	double precision, recall;
	score(matTruth, matOutput, 1, precision, recall);

	std::cout << precision << std::endl;
	std::cout << recall << std::endl;

	return 0;
}