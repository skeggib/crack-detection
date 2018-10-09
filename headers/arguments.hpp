#ifndef ARGUMENTSHPP
#define ARGUMENTSHPP

#include <vector>
#include <map>
#include <string>

/**
 * @brief Command line arguments parser.
 * Parses the command line arguments and stores them as options or parameters. Options are arguments
 * that starts with a '-' (e.g. '-option') and can have a value. Parameters are the remaining 
 * arguments. For example the arguments '-size 2 file1 file2 -s' have the folowwing options: '-size'
 * with a value of '2' and '-s', the parameters are 'file1' and 'file2'.
 */
class arguments_t {

private:

    std::map<std::string, std::string> options;
    std::vector<std::string> parameters;

public:

    /**
     * @brief Parses the command line arguments.
     * 
     * @param argc The number of arguments in argv.
     * @param argv The actual arguments including the executable path.
     */
    arguments_t(int argc, char** argv);

    /**
     * @brief Counts the number of options.
     * 
     * @return std::size_t The number of options.
     */
    std::size_t optionsSize();

    /**
     * @brief Counts the number of parameters.
     * 
     * @return std::size_t The number of parameters.
     */
    std::size_t parametersSize();

    /**
     * @brief Checks if an option exists.
     * 
     * @param key The options to search.
     * @return true If the options exists.
     * @return false If the options doesn't exists.
     */
    bool containsOption(std::string key) const;

    /**
     * @brief Gets the value of an option.
     * 
     * @param key The option to get the value of.
     * @return std::string The value of the option or an empty std::string if the option has no 
     * value.
     */
    std::string operator[](std::string const & key) const;

    /**
     * @brief Gets a parameter.
     * 
     * @param index The parameter position in the arguments (starting at 0).
     * @return std::string The parameter.
     */
    std::string operator[](int index) const;
};

#endif