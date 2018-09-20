#include <opencv2/opencv.hpp>
#include <iostream>

int main(int argc, char** argv) {

	if (argc < 3) {
		std::cout << "usage: ./inverse image_entree image_binaire_sortie" << std::endl;
		return 0;
	}

	auto imageIn = cv::imread(argv[1], cv::IMREAD_GRAYSCALE);
	if (!imageIn.data)
	{
		std::cout << "Could not open or find the image" << std::endl;
		return -1;
	}

	auto imageOut = imageIn.clone();
	
	for (int i = 0; i < imageOut.rows; i++)
	{
		for (int j = 0; j < imageOut.cols; j++)
		{
			imageOut.at<char>(cv::Point(j, i)) = 255 - imageOut.at<char>(cv::Point(j, i));
		}
	}
	
	imwrite(argv[2], imageOut);
	return 0;
}