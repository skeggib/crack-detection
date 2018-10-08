#include <iostream>
#include <opencv2/opencv.hpp>

#include "arguments.hpp"
#include "filters.hpp"

int main(int argc, char** argv) {
    arguments_t args(argc, argv);

	if (args.parametersSize() < 2) {
		std::cout << "usage: " << argv[0] << " input output" << std::endl;
		return 0;
	}

    auto image = cv::imread(args[0], cv::IMREAD_GRAYSCALE);
	if (!image.data) {
		std::cout << "Cannot load " << args[0] << std::endl;
		return 0;
	}

	gaussianFilter(image, 1, 1);
    sobelFilter(image);
    binaryFilter(image, 0.5);

    cv::imwrite(args[1], image);

    return 0;
}