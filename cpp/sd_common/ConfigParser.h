#ifndef __CONFIG_PARSER_H_
#define __CONFIG_PARSER_H_

#include <sstream>
#include <string>
#include <unordered_map>

/**
 * @class ConfigParser
 * @brief A simple I/O class for configuration file settings
 */
class ConfigParser
{
public:
    /// Default constructor
    ConfigParser() = default;

    /// Attempts to load the configuration file at the given path, returning true on success, false on failure.
    bool load(std::string filePath);

    /// Returns the value associated with the given key
    template <typename T>
    T getValue(const std::string &key)
    {
        T value;
        std::string strVal = m_configMap[key];
        std::istringstream ss(strVal);
        ss >> value;
        return value;
    }

private:
    /// Map of configurable settings
    std::unordered_map<std::string, std::string> m_configMap;
};                                                                                                                                                                                             
                                                                                                                                                                                               
#endif //__CONFIG_PARSER_H_ 

