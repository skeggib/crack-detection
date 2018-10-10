#ifndef TOOLSHPP
#define TOOLSHPP

#include <opencv2/opencv.hpp>

/**
 * @brief Applies a gaussian filter on an image.
 * 
 * @param image The image to apply the filter to.
 * @param l The size of the filter, the actual filter will be of the size (2l+1)x(2l+1).
 * @param sigma The standard deviation of the gaussian function.
 */
void gaussianFilter(cv::Mat & image, int l, double sigma);

/**
 * @brief Applies a sobel filter on an image and normalizes the values between 0 and 255.
 * 
 * @param image The image to apply the filter on.
 */
void sobelFilter(cv::Mat & image);

/**
 * @brief Applies a laplacian filter on an image and normalizes the values between 0 and 255.
 * 
 * @param image The image to apply the filter on.
 */
void laplacianFilter(cv::Mat & image);

/**
 * @brief Applies a binary filter on an image.
 * 
 * @param image The image to apply the filter on.
 * @param factor All pixels over max(image)*factor will be white.
 */
void binaryFilter(cv::Mat & image, double factor);

/**
 * @brief Applies a variance filter on an image and normalizes the values between 0 and 255.
 * 
 * @param image The image to apply the filter on.
 * @param l The size of the filter, the actual filter will be of the size (2l+1)x(2l+1).
 */
void varianceFilter(cv::Mat & image, int l);

class mPoint : public cv::Point {
public:
	mPoint(int x, int y);
};

bool operator<(mPoint lhs, mPoint rhs);

void clusterRemoval(cv::Mat & binary, int threshold);
std::set<mPoint> findCluster(cv::Mat binary, int x, int y);
void searchCluster(cv::Mat binary, mPoint point, std::set<mPoint> & cluster);

#endif
