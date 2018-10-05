#ifndef SCORINGHPP
#define SCORINGHPP

#include <opencv2/opencv.hpp>

void score(cv::Mat expected, cv::Mat actual, int delta, double& precision, double& recall);

#endif