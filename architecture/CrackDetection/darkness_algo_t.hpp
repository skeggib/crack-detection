#ifndef DARKNESSALGOHPP
#define DARKNESSALGOHPP

#include <opencv2/opencv.hpp>
#include "algo_t.hpp"

class darkness_algo_t : public algo_t_
{
  public:
    cv::Mat work(cv::Mat imageIn);
    cv::Mat find(cv::Mat imageOut, double threshold);
    score_t eval(cv::Mat expected, cv::Mat actual);
    double permThreshold() { return 255; }
    double nonPermThreshold() { return 0; }
    double step() { return 1; }
};

#endif