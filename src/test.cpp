#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>

#include "filters.hpp"

void variancePyramids(cv::Mat & image, int pyrsNumber, int lVariance, double binaryFactor) {
    std::vector<cv::Mat> pyrs;
    for (int i = 0; i < pyrsNumber; ++i) {
        cv::Mat current = image.clone();
        for (int j = 0; j < i; ++j)
            cv::pyrDown(current, current);
        varianceFilter(current, lVariance);
        binaryFilter(current, binaryFactor);
        for (int j = 0; j < i; ++j)
            cv::pyrUp(current, current);
        pyrs.push_back(current);
    }

    for (int y = 0; y < image.rows; ++y) {
        for (int x = 0; x < image.cols; ++x) {
            image.at<uchar>(y, x) = 0;
            for (int s = 0; s < pyrsNumber; ++s) {
                if (pyrs[s].at<uchar>(y, x) == 255)
                    image.at<uchar>(y, x) = 255;
                    break;
            }
        }
    }
}

int main(int argc, char** argv) {
    auto image = cv::imread(argv[1], cv::IMREAD_GRAYSCALE);

    cv::equalizeHist(image, image);
    gaussianFilter(image, 3, 1);

    variancePyramids(image, 4, 10, 0.5);

    cv::Mat element = cv::getStructuringElement(cv::MORPH_CROSS, cv::Size(3, 3));
    cv::Mat temp(image.size(), CV_8UC1), skel(image.size(), CV_8UC1, cv::Scalar(0));
    bool done = false;
    do {
        cv::morphologyEx(image, temp, cv::MORPH_OPEN, element);
        cv::bitwise_not(temp, temp);
        cv::bitwise_and(image, temp, temp);
        cv::bitwise_or(skel, temp, skel);
        cv::erode(image, image, element);
        
        double max;
        cv::minMaxLoc(image, 0, &max);
        done = (max == 0);
    } while (!done);

    clusterRemoval(skel, 10);

    cv::imshow(argv[2], skel);
    cv::waitKey();

    return 0;
}