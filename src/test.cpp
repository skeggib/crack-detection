#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>

#include "filters.hpp"

cv::Mat pyrSobel(cv::Mat image, int level) {
    for (int i = 0; i < level; ++i) {
        cv::pyrDown(image, image);
    }

    sobelFilter(image);
    
    for (int i = 0; i < level; ++i) {
        cv::pyrUp(image, image);
    }

    return image;
}

cv::Mat multPyrSobel(cv::Mat image, int maxLevel) {
    std::vector<cv::Mat> scales;
    for (int i = 0; i <= maxLevel; ++i) {
        scales.push_back(pyrSobel(image, i));
    }

    for (int y = 0; y < image.rows; ++y) {
        for (int x = 0; x < image.cols; ++x) {
            cv::Point point(x, y);
            image.at<uchar>(point) = 0;
            for (int s = 0; s < scales.size(); ++s) {
                int value = (maxLevel + 1 - s) * scales[s].at<uchar>(point);
                if (value > image.at<uchar>(point))
                    image.at<uchar>(point) = value;
            }
        }
    }

    return image;
}

void varianceFilter(cv::Mat & image, int l) {
    auto clone = image.clone();
    for (int y = 0; y < clone.rows; ++y) {
        for (int x = 0; x < clone.cols; ++x) {
            int sum = 0;
            int sqrs = 0;
            int samples = 0;
            for (int n = std::max(-l, -y); n <= std::min(l, clone.rows - y - 1); ++n) {
                //std::cout << std::min(l, clone.rows - y) << std::endl;
                for (int m = std::max(-l, -x); m <= std::min(l, clone.cols - x - 1); ++m) {
                    //std::cout << x << " + " << m << ", " << y << " + " << n << std::endl;
                    auto val = clone.at<uchar>(y + n, x + m);
                    sum += val;
                    sqrs += val * val;
                    ++samples;
                }
            }
            auto mean = (sum / (double)samples);
            auto variance = sqrs / (double)samples - mean * mean;
            if (variance > 255) variance = 255;
            image.at<uchar>(y, x) = (uchar)variance;
        }
    }
}

int main() {
    auto image = cv::imread("input.jpg", cv::IMREAD_GRAYSCALE);

    varianceFilter(image, 3);
    
    cv::imshow("image", image);
    cv::waitKey();

    return 0;
}