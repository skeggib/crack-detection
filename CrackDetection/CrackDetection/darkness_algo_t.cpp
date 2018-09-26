#include <cmath>
#include <opencv2/opencv.hpp>
#include "darkness_algo_t.hpp"

using namespace std;
using namespace cv;

Mat darkness_algo_t::work(Mat imageIn) { return imageIn.clone(); };

Mat darkness_algo_t::find(Mat input, double threshold)
{
    auto output = input.clone();

    for (int i = 0; i < output.rows; i++)
    {
        for (int j = 0; j < output.cols; j++)
        {
            output.at<uchar>(Point(j, i)) = input.at<uchar>(Point(j, i)) <= threshold ? UCHAR_MAX : 0;
        }
    }

    return output;
}

score_t darkness_algo_t::eval(Mat expected, Mat actual)
{
    int delta = 2;
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
					for (int dx = max(-delta, -x); dx <= min(delta, expected.cols - x - 1) && !found; dx++) {
						for (int dy = max(-delta, -y); dy <= min(delta, expected.cols - y - 1) && !found; dy++) {
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

    double precision, recall;

	if ((truePositive + falsePositive) != 0)
		precision = truePositive / (truePositive + falsePositive);
	else
		precision = -1;

	if ((truePositive + falseNegative) != 0)
		recall = truePositive / (truePositive + falseNegative);
	else
		recall = -1;

    return score_t(precision, recall);
}