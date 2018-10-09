#include "scoring.hpp"

void score(cv::Mat expected, cv::Mat actual, int delta, double & precision, double & recall) {
	assert(expected.cols == actual.cols);
	assert(expected.rows == actual.rows);

	double truePositive = 0;
	double trueNegative = 0;
	double falsePositive = 0;
	double falseNegative = 0;

	for (int x = 0; x < expected.cols; x++) {
		for (int y = 0; y < expected.rows; y++) {

			auto expectedValue = expected.at<unsigned char>(cv::Point(x, y));
			auto actualValue = actual.at<unsigned char>(cv::Point(x, y));

			if (actualValue == UCHAR_MAX) {
				if (expectedValue == UCHAR_MAX)
					truePositive++;
				else {
					// Recherche dans le voisinnage
					bool found = false;
					for (int dx = std::max(-delta, -x); dx <= std::min(delta, expected.cols - x - 1) && !found; dx++) {
						for (int dy = std::max(-delta, -y); dy <= std::min(delta, expected.rows - y - 1) && !found; dy++) {
							if (actualValue == expected.at<unsigned char>(cv::Point(x + dx, y + dy)))
								found = true;
						}
					}
					if (found)
						truePositive++;
					else
						falsePositive++;
				}
			}
			else {
				if (expectedValue == 0)
					trueNegative++;
				else
					falseNegative++;
			}
		}
	}

	if ((truePositive + falsePositive) != 0)
		precision = truePositive / (truePositive + falsePositive);
	else
		precision = -1;

	if ((truePositive + falseNegative) != 0)
		recall = truePositive / (truePositive + falseNegative);
	else
		recall = -1;
}