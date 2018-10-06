#include <iostream>
#include <opencv2/opencv.hpp>

#include "arguments.hpp"
#include "filters.hpp"

int main(int argc, char** argv) {
    arguments_t args(argc, argv);
    if (args.parametersSize() < 2) {
        std::cout << "usage: " << argv[0] << " <input> <output>" << std::endl;
        return 0;
    }

    cv::Mat image = cv::imread(args[0], cv::IMREAD_GRAYSCALE);
    if (!image.data) {
        std::cout << "Cannot open " << args[0] << std::endl;
        return 0;
    }

    gaussianFilter(image, 5, 3);

    cv::Mat grad_x, grad_y;

    cv::Sobel(image, grad_x, image.depth(), 1, 0);
    cv::Sobel(image, grad_y, image.depth(), 0, 1);
    cv::absdiff(grad_x, grad_y, image);
    binaryFilter(image, 0.25);

    cv::imshow("result", image);
    cv::waitKey();

    cv::imwrite(args[1], image);
    return 0;
}