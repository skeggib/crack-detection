#include "arg.hpp"

std::map<std::string, std::string> parseNamed(int argc, char** argv) {
	std::map<std::string, std::string> map;
	for (size_t i = 0; i < argc; i++)
	{
		if (argv[i][0] == '-' && i < argc - 1) {
			map.insert(argv[i], argv[i + 1]]);
			i++;
		}
	}
}

std::vector<std::string> parseUnnamed(int argc, char** argv) {

}