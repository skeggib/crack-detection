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

    auto gauss = image.clone();
    cv::medianBlur(image, gauss, 7);
    image = image - gauss;
    //cv::equalizeHist(image, image);

    cv::imshow("result", gauss);
    cv::waitKey();

    cv::imwrite(args[1], image);
    return 0;
}