#include <functional>
#include <opencv2/opencv.hpp>
#include "tools.hpp"
#include "scoring.hpp"
#include <string>
#include "prcurve.hpp"

uchar dichotomy(std::function<void(uchar, double&, double&)> scoreFunction, uchar min, uchar max, std::string name);

int main(int argc, char** argv) {
	auto real = cv::imread(argv[1], cv::IMREAD_GRAYSCALE);
	auto expected = cv::imread(argv[2], cv::IMREAD_GRAYSCALE);

	cv::Mat edges = sobelFilter(real);
	auto pairs = prlist<double>([=](double parameter, double& precision, double& recall) {
		cv::Mat blured = gaussianFilter(edges, 20, parameter);
		cv::Mat binary = binaryFilter(blured, 0.3);
		cv::Mat clustered = clusterRemoval(binary, 100);
		score(expected, clustered, 1, precision, recall);
		std::cout << parameter << " => \t" << precision << " \t" << recall << std::endl;
	}, 0.1, 1, 0.1);
	cv::imshow("curve", prcurve(pairs));
	cv::waitKey();
	std::ofstream stream;
	stream.open("curve.csv");
	for each (auto pair in pairs)
		stream << pair.second << ", " << pair.first << std::endl;
	stream.close();
	/*auto pairs = prlist<uchar>([=](uchar parameter, double& precision, double&recall) {
		score(expected, binary(filtered, parameter), 0, precision, recall);
	}, 0, 255, 10);
	auto curve = prcurve<int>(pairs);
	cv::imshow("curve", curve);
	cv::waitKey();*/
	
	/*uchar binaryThreshold = dichotomy([=](uchar threshold, double& precision, double& recall) {
		score(expected, toBinary(edges, threshold), 0, precision, recall);
	}, 0, 255, "binary");

	cv::Mat binary = toBinary(edges, binaryThreshold);

	uchar clusterThreshold = dichotomy([=](uchar threshold, double& precision, double& recall) {
		score(expected, clusterRemoval(binary, threshold), 0, precision, recall);
	}, 0, 255, "cluster");

	cv::Mat out = clusterRemoval(binary, clusterThreshold);

	cv::imshow("out", out);
	cv::waitKey();*/
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