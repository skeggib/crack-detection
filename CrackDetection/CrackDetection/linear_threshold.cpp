#include <iostream>
#include <opencv2/opencv.hpp>
#include "algo_t.hpp"
#include "darkness_algo_t.hpp"

int main(int argc, char **argv)
{
    if (argc < 3)
    {
        std::cout << "usage: ./evaluation image_binaire_verite terrain_image_binaire_sortie" << std::endl;
        return 0;
    }

    char *pathTruth = argv[1];
    cv::Mat expected = cv::imread(pathTruth, cv::IMREAD_GRAYSCALE);
    char *pathInput = argv[2];
    cv::Mat image = cv::imread(pathTruth, cv::IMREAD_GRAYSCALE);
    algo_t algo = darkness_algo_t();

    std::cout << "best threshold for pathInput is: " << find_threshold(expected, image, algo) << std::endl;

    return 0;
}

double find_threshold(cv::Mat expected, cv::Mat image, algo_t algo)
{
    double min = std::min(algo.permThreshold(), algo.nonPermThreshold());
    double max = std::max(algo.permThreshold(), algo.nonPermThreshold());
    double step = std::abs(algo.step());

    if (min > max)
    {
        std::swap(min, max);
    }

    double bestThreshold = min;
    score_t bestScore = score_t(0, 0);
    cv::Mat output = algo.work(image);

    for (double threshold = min; threshold <= max; threshold += step)
    {
        cv::Mat actual = algo.find(output, threshold);
        score_t score = algo.eval(expected, actual);

        if (score.compare(bestScore) == 1)
        {
            bestThreshold = threshold;
            bestScore = score;
        }
    }

    return bestThreshold;
}