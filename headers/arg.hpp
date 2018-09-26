#ifndef ARGHPP
#define ARGHPP

#include <map>
#include <string>
#include <vector>

std::map<std::string, std::string> parseNamed(int argc, char** argv);

std::vector<std::string> parseUnnamed(int argc, char** argv);

#endif