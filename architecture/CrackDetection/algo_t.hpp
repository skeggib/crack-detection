#ifndef ALGOHPP
#define ALGOHPP

#include <opencv2/opencv.hpp>
#include "score_t.hpp"

class algo_t_
{
  public:
    virtual cv::Mat work(cv::Mat imageIn) = 0;
    virtual cv::Mat find(cv::Mat matrixOut, double threshold) = 0;
    virtual score_t eval(cv::Mat expected, cv::Mat actual) = 0;
    virtual double permThreshold() = 0;
    virtual double nonPermThreshold() = 0;
    virtual double step() = 0;
};

class algo_t : public algo_t_
{
  private:
    std::unique_ptr<algo_t_> algo;

  public:
    cv::Mat work(cv::Mat imageIn) { algo->work(imageIn); }
    cv::Mat find(cv::Mat imageOut, double threshold) { algo->find(imageOut, threshold); }
    score_t eval(cv::Mat expected, cv::Mat actual) { algo->eval(expected, actual); }
    double permThreshold() { algo->permThreshold(); }
    double nonPermThreshold() { algo->nonPermThreshold(); }
    double step() { algo->step(); }

    template<typename T>
    algo_t(std::unique_ptr<T> a) : algo(move(a)) {}

    template<typename T>
    algo_t(T&& a) : algo(std::make_unique<T>(move(a))) {}
};

#endif