#include <opencv2/opencv.hpp>
#include <iostream>

#include "arguments.hpp"
#include "filters.hpp"
#include "scoring.hpp"
#include "prcurve.hpp"

int main(int argc, char** argv) {
    arguments_t args(argc, argv);
    if (args.parametersSize() < 2) {
        std::cout << "Usage: " << argv[0] << " input expected" << std::endl;
        return -1;
    }

	auto image = cv::imread(args[0], cv::IMREAD_GRAYSCALE);
	auto expected = cv::imread(args[1], cv::IMREAD_GRAYSCALE);

	std::vector<parameterScore<int>> list;
	int i = 0;

	double bestPerformance = 0;
	double bestPrecision = 0;
	double bestRecall = 0;
	double bestSigma = 0;
	double bestFactor = 0;

	for (double sigma = 0.1; sigma < 5; sigma += 0.1) {
		for (double factor = 0.1; factor < 1; factor += 0.1) {

			auto clone = image.clone();
			cv::equalizeHist(image, image);
			gaussianFilter(clone, 10, sigma);
			sobelFilter(clone);
			binaryFilter(clone, factor);

			double precision, recall;
			score(expected, clone, 1, precision, recall);
			list.push_back(parameterScore<int>(i, precision, recall));
			++i;

            double absDiff = std::abs(precision - recall);
			double performance = precision * precision + recall * recall / (absDiff * absDiff);
			if (bestPerformance < performance) {
				bestPerformance = performance;
				bestPrecision = precision;
				bestRecall = recall;
				bestSigma = sigma;
				bestFactor = factor;
			}

			std::cout << " sigma=" << sigma;
			std::cout << ", factor=" << factor;
			std::cout << " => precision=" << precision;
			std::cout << ", recall=" << recall;
			std::cout << " => " << performance;
			std::cout << std::endl;
		}
	}

	std::cout << std::endl;
	std::cout << "sigma=" << bestSigma;
	std::cout << ", factor=" << bestFactor;
	std::cout << " => precision=" << bestPrecision;
	std::cout << ", recall=" << bestRecall;
	std::cout << " => " << bestPerformance;
	std::cout << std::endl;

	//cv::imshow("PR curve", prcurve(list));
	//cv::waitKey();

	return 0;
}

