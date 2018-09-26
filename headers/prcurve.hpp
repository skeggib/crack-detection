#ifndef PRCURVEHPP
#define PRCURVEHPP

#include <functional>
#include <opencv2/opencv.hpp>
#include <vector>
#include <ostream>

template <typename T>
struct parameterScore {
	T parameter;
	double precision;
	double recall;

	parameterScore(T parameter, double precision, double recall) {
		this->parameter = parameter;
		this->precision = precision;
		this->recall = recall;
	}
};

template <typename T>
std::vector<parameterScore<T>> prlist(
	std::function<void(T parameter, double& precision, double& recall)> scoreFunction,
	T min,
	T max,
	T step) {

	std::vector<parameterScore<T>> pairs;

	auto last = min;
	for (T parameter = min; parameter < max; parameter += step) {
		if (parameter < last)
			break;
		last = parameter;
		double precision, recall;
		scoreFunction(parameter, precision, recall);
		pairs.push_back(parameterScore<T>(parameter, precision, recall));
	}

	return pairs;
}

template <typename T>
cv::Mat prcurve(std::vector<parameterScore<T>> prlist) {
	int size = 200;
	cv::Mat curve(size, size, CV_8UC1);
	for (auto it = curve.begin<uchar>(); it != curve.end<uchar>(); ++it)
		*it = 0;
	for (int i = 1; i < prlist.size(); ++i) {
		auto pair1 = prlist[i - 1];
		auto pair2 = prlist[i];
		cv::Point p1((int)(pair1.recall * size), (int)(size - pair1.precision * size));
		cv::Point p2((int)(pair2.recall * size), (int)(size - pair2.precision * size));
		cv::line(curve, p1, p2, 255);
	}

	return curve;
}

template <typename T>
void writeCsv(std::ostream& stream, std::vector<parameterScore<T>> scores) {
	for each (auto score in scores)
	{
		stream << score.parameter << ", ";
		stream << score.precision << ", ";
		stream << score.recall << std::endl;
	}
}

template <typename T>
void writeCsv(std::string filename, std::vector<parameterScore<T>> scores) {
	std::ofstream stream;
	stream.open(filename);
	writeCsv(stream, scores);
	stream.close();
}

#endif