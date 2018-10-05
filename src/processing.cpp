#include <opencv2/opencv.hpp>
#include <iostream>

#include "arguments.hpp"
#include "filters.hpp"

int main(int argc, char** argv) {
    arguments_t args(argc, argv);
    if (args.parametersSize() < 2) {
        std::cout << "Usage: " << argv[0] << " input output [options]" << std::endl;
        return -1;
    }

    auto inputPath = args[0];
    auto outputPath = args[1];

    auto image = cv::imread(inputPath, cv::IMREAD_GRAYSCALE);

    cv::equalizeHist(image, image);

    if (args.containsOption("--gauss")) {
        auto sigma = std::stod(args["--gauss"]);
        gaussianFilter(image, 10, sigma);
    }

    sobelFilter(image);

    if (args.containsOption("--binary")) {
        auto factor = std::stod(args["--binary"]);
        binaryFilter(image, factor);
    }

    if (args.containsOption("--cluster")) {
        auto threshold = std::stoi(args["--cluster"]);
        clusterRemoval(image, threshold);
    }

    cv::imwrite(outputPath, image);
    
    cv::imshow("Output image", image);
    cv::waitKey();

    return 0;
}