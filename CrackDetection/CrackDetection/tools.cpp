#include "tools.hpp"

void gaussianFilter(cv::Mat& image, int l, double sigma) {
	cv::Mat filtered;
	cv::GaussianBlur(image, filtered, cv::Size(l*2+1, l * 2 + 1), sigma, sigma);
	image = filtered;
}

void sobelFilter(cv::Mat& image) {
	cv::Mat grad_x;
	cv::Sobel(image, grad_x, image.depth(), 1, 0);
	cv::Mat abs_grad_x;
	cv::convertScaleAbs(grad_x, abs_grad_x);

	cv::Mat grad_y;
	cv::Sobel(image, grad_y, image.depth(), 0, 1);
	cv::Mat abs_grad_y;
	cv::convertScaleAbs(grad_y, abs_grad_y);

	cv::Mat out;
	cv::addWeighted(abs_grad_x, 0.5, abs_grad_y, 0.5, 0, out);

	image = out;
}

void binaryFilter(cv::Mat& image, double factor) {
	cv::Mat out = image.clone();
	double min, max;
	cv::minMaxLoc(out, &min, &max);
	uchar threshold = max * factor;
	for (int x = 0; x < out.cols; x++)
	{
		for (int y = 0; y < out.rows; y++)
		{
			if (out.at<uchar>(cv::Point(x, y)) > threshold)
				out.at<uchar>(cv::Point(x, y)) = UCHAR_MAX;
			else
				out.at<uchar>(cv::Point(x, y)) = 0;
		}
	}
	image = out;
}

void clusterRemoval(cv::Mat& image, int threshold) {
	cv::Mat temp = image.clone();
	cv::Mat out = cv::Mat(image.rows, image.cols, image.type());
	for (int x = 0; x < out.cols; x++)
		for (int y = 0; y < out.rows; y++)
			out.at<uchar>(cv::Point(x, y)) = 0;
	for (int x = 0; x < temp.cols; x++) {
		for (int y = 0; y < temp.rows; y++) {
			if (temp.at<uchar>(cv::Point(x, y)) == UCHAR_MAX) {
				std::set<mPoint> cluster = findCluster(temp, x, y);
				if (cluster.size() > threshold) {
					for each (cv::Point point in cluster) {
						out.at<uchar>(point) = UCHAR_MAX;
					}
				}
				for each (cv::Point point in cluster) {
					temp.at<uchar>(point) = 0;
				}
			}
		}
	}
	image = out;
}

std::set<mPoint> findCluster(cv::Mat binary, int x, int y) {
	std::set<mPoint> cluster;
	searchCluster(binary, mPoint(x, y), cluster);
	return cluster;
}

void searchCluster(cv::Mat binary, mPoint point, std::set<mPoint>& cluster) {
	cluster.insert(point);

	std::set<mPoint> neighbors;
	if (point.x >= 1)
		neighbors.insert(mPoint(point.x - 1, point.y));
	if (point.y >= 1)
		neighbors.insert(mPoint(point.x, point.y - 1));
	if (point.x < binary.cols - 1)
		neighbors.insert(mPoint(point.x + 1, point.y));
	if (point.y < binary.rows - 1)
		neighbors.insert(mPoint(point.x, point.y + 1));

	for each (mPoint neighbor in neighbors) {
		if (std::find(cluster.begin(), cluster.end(), neighbor) == cluster.end()) {
			if (binary.at<uchar>(neighbor) == UCHAR_MAX) {
				searchCluster(binary, neighbor, cluster);
			}
		}
	}
}

mPoint::mPoint(int x, int y)
	: cv::Point(x, y) {

}

bool operator<(mPoint lhs, mPoint rhs) {
	if (lhs.x != rhs.x)
		return lhs.x < rhs.x;
	return lhs.y < rhs.y;
}