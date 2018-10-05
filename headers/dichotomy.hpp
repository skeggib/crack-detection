#ifndef DICHOTOMYHPP
#define DICHOTOMYHPP

#include <opencv2/opencv.hpp>
#include <functional>

uchar dichotomy(std::function<void(uchar, double&, double&)> scoreFunction, uchar min, uchar max, std::string name);

#endif