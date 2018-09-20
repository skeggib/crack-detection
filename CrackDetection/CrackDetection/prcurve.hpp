#ifndef PRCURVEHPP
#define PRCURVEHPP

#include <functional>
#include <opencv2/opencv.hpp>
#include <vector>

template <typename T>
std::vector<std::pair<double, double>> prlist(
	std::function<void(T parameter, double& precision, double& recall)> scoreFunction,
	T min,
	T max,
	T step) {

	std::vector<std::pair<double, double>> pairs;

	T last = min;
	for (T parameter = min; parameter < max; parameter += step) {
		if (parameter < last)
			break;
		last = parameter;
		double precision, recall;
		scoreFunction(parameter, precision, recall);
		pairs.push_back(std::pair<double, double>(precision, recall));
	}

	return pairs;
}

cv::Mat prcurve(std::vector<std::pair<double, double>> prlist) {
	int size = 200;
	cv::Mat curve(size, size, CV_8UC1);
	for (auto it = curve.begin<uchar>(); it != curve.end<uchar>(); ++it)
		*it = 0;
	for (int i = 1; i < prlist.size(); ++i) {
		std::pair<double, double> pair1 = prlist[i - 1];
		std::pair<double, double> pair2 = prlist[i];
		cv::Point p1((int)(pair1.second * size), (int)(size - pair1.first * size));
		cv::Point p2((int)(pair2.second * size), (int)(size - pair2.first* size));
		cv::line(curve, p1, p2, 255);
	}

	return curve;
}

#endif