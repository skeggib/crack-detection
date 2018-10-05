#ifndef ARGUMENTSHPP
#define ARGUMENTSHPP

#include <vector>
#include <map>
#include <string>

class arguments_t {
private:
    std::map<std::string, std::string> options;
    std::vector<std::string> parameters;
public:
    arguments_t(int argc, char** argv);
    std::size_t optionsSize();
    std::size_t parametersSize();
    bool containsOption(std::string key) const;
    std::string operator[](std::string const & key) const;
    std::string operator[](int index) const;
};

#endif