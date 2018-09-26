#include "arguments.hpp"

arguments_t::arguments_t(int argc, char** argv) {
    argc--;
    argv++;
    while (argc > 0) {
        if (*argv[0] == '-') {
            std::string key(*argv);
            argc--;
            argv++;
            std::string value;
            if (argc > 0) {
                value = std::string(*argv);
                argc--;
                argv++;
            }
            this->options[key] = value;
        }
        else {
            this->parameters.push_back(*argv);
            argc--;
            argv++;
        }
    }
}

std::size_t arguments_t::optionsSize() {
    return this->options.size();
}

std::size_t arguments_t::parametersSize() {
    return this->parameters.size();
}

bool arguments_t::containsOption(std::string key) const {
    return this->options.find(key) != this->options.end();
}

std::string arguments_t::operator[](std::string const & key) const {
    return this->options.at(key);
}

std::string arguments_t::operator[](int index) const {
    return this->parameters[index];
}
