#ifndef TOOLSHPP
#define TOOLSHPP

#include <opencv2/opencv.hpp>

void gaussianFilter(cv::Mat& image, int l, double sigma);

void sobelFilter(cv::Mat& image);

void laplacianFilter(cv::Mat& image);

void binaryFilter(cv::Mat& image, double factor);

void varianceFilter(cv::Mat & image, int l);

class mPoint : public cv::Point {
public:
	mPoint(int x, int y);
};

bool operator<(mPoint lhs, mPoint rhs);

void clusterRemoval(cv::Mat& binary, int threshold);
std::set<mPoint> findCluster(cv::Mat binary, int x, int y);
void searchCluster(cv::Mat binary, mPoint point, std::set<mPoint>& cluster);

#endif
