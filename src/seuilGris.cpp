#include <iostream>
#include <opencv2/opencv.hpp>

#include "arguments.hpp"
#include "filters.hpp"

int main(int argc, char** argv) {
    arguments_t args(argc, argv);

	if (args.parametersSize() < 3) {
		std::cout << "usage: " << argv[0] << " threshold input output" << std::endl;
		return 0;
	}

    auto image = cv::imread(args[1], cv::IMREAD_GRAYSCALE);
	if (!image.data) {
		std::cout << "Cannot load " << args[1] << std::endl;
		return 0;
	}

    binaryFilter(image, std::stod(args[0]));

    cv::imwrite(args[2], image);

    return 0;
}