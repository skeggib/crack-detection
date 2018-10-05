#include "dichotomy.hpp"

uchar dichotomy(std::function<void(uchar, double&, double&)> scoreFunction, uchar min, uchar max, std::string name) {
	uchar param = (min + max) / 2;
	double precision, recall;
	bool found = false;

	while (max - min > 1) {
		param = (min + max) / 2;
		scoreFunction(param, precision, recall);
		if (precision <= 0 || recall <= 0) {
			max = param;
			continue;
		}
		found = true;
		double score = precision / recall;
		std::cout << "[" << name << "] " << (int)param << " => " << precision << " / " << recall << " = " << score << std::endl;
		if (score < 1)
			min = param;
		else if (score > 1)
			max = param;
		else
			return param;
	}
	return found ? param : -1;
}