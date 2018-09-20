#include <functional>
#include <opencv2/opencv.hpp>
#include "tools.hpp"
#include "scoring.hpp"
#include <string>
#include "prcurve.hpp"

uchar dichotomy(std::function<void(uchar, double&, double&)> scoreFunction, uchar min, uchar max, std::string name);

int main(int argc, char** argv) {
	auto realName = argv[1];
	auto expectedName = argv[2];
	auto real = cv::imread(realName, cv::IMREAD_GRAYSCALE);
	auto expected = cv::imread(expectedName, cv::IMREAD_GRAYSCALE);

	auto list = prlist<int>([=](auto parameter, auto& precision, auto& recall) {
		auto image = real.clone();
		gaussianFilter(image, 20, 0.5);
		sobelFilter(image);
		binaryFilter(image, 0.5);
		clusterRemoval(image, parameter);
		score(expected, image, 1, precision, recall);
		std::cout << parameter << " => " << precision << " " << recall << std::endl;
	}, 0, 200, 10);
	writeCsv("curve.csv", list);
	cv::imshow("curve", prcurve(list));
	cv::waitKey();
}

uchar dichotomy(std::function<void(uchar, double&, double&)> scoreFunction, uchar min, uchar max, std::string name) {
	uchar param = (min + max) / 2;
	double precision, recall;
	bool found = false;

	while (max - min > 1) {
		param = (min + max) / 2;
		scoreFunction(param, precision, recall);
		if (precision <= 0 || recall <= 0) {
			max = param;
			continue;
		}
		found = true;
		double score = precision / recall;
		std::cout << "[" << name << "] " << (int)param << " => " << precision << " / " << recall << " = " << score << std::endl;
		if (score < 1)
			min = param;
		else if (score > 1)
			max = param;
		else
			return param;
	}
	return found ? param : -1;
}