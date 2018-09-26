#include <opencv2/opencv.hpp>
#include <iostream>

int main(int argc, char** argv) {
	if (argc < 3) {
		std::cout << "usage: ./sobel image_entree image_binaire_sortie" << std::endl;
		return 0;
	}

	auto imageIn = cv::imread(argv[1], cv::IMREAD_GRAYSCALE);
	if (!imageIn.data)
	{
		std::cout << "Could not open or find the image" << std::endl;
		return -1;
	}

	int l = std::stoi(argv[3]);
	int sigma = std::stoi(argv[4]);

	cv::Mat imageBlured;
	cv::GaussianBlur(imageIn, imageBlured, cv::Size(2*l+1, 2*l+1), sigma, sigma);

	cv::imshow("image", imageBlured);
	cv::waitKey();

	return 0;
}