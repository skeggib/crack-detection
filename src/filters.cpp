#include "filters.hpp"

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

void laplacianFilter(cv::Mat& image) {
	cv::Laplacian(image, image, image.depth());
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

void varianceFilter(cv::Mat & image, int l) {
    cv::Mat image32f;
    image.convertTo(image32f, CV_32F);

    cv::Mat mean;
    cv::blur(image32f, mean, cv::Size(l*2+1, l*2+1));

    cv::Mat sqrs;
    cv::blur(image32f.mul(image32f), sqrs, cv::Size(l*2+1, l*2+1));

    cv::Mat sigma;
    cv::sqrt(sqrs - mean.mul(mean), sigma);

    cv::normalize(sigma, image, 0.0, 255.0, cv::NORM_MINMAX);
    image.convertTo(image, CV_8UC1);
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
					for (auto point : cluster) {
						out.at<uchar>(point) = UCHAR_MAX;
					}
				}
				for (auto point : cluster) {
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

	for (auto neighbor : neighbors) {
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