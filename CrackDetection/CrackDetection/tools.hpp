#ifndef TOOLSHPP
#define TOOLSHPP

#include <opencv2/opencv.hpp>

cv::Mat gaussianFilter(cv::Mat image, int l, double sigma);

cv::Mat sobelFilter(cv::Mat image);

cv::Mat binaryFilter(cv::Mat image, double factor);

class mPoint : public cv::Point {
public:
	mPoint(int x, int y);
};

bool operator<(mPoint lhs, mPoint rhs);

cv::Mat clusterRemoval(cv::Mat binary, int threshold);
std::set<mPoint> findCluster(cv::Mat binary, int x, int y);
void searchCluster(cv::Mat binary, mPoint point, std::set<mPoint>& cluster);

#endif
