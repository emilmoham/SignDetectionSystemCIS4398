#include "ConfigParser.h"
#include <algorithm>
#include <fstream>

bool ConfigParser::load(std::string filePath)
{
    m_configMap.clear();

    std::ifstream fIn(filePath, std::ifstream::in);
    if (!fIn.is_open())
        return false;

    // Read one line at a time, placing key-value pairs into the map
    std::string line;
    while (fIn.good())
    {
        std::getline(fIn, line);

        // Ignore empty lines, and lines starting with '#' or '['
        if (line.empty() || line[0] == '#' || line[0] == '[')
            continue;

        // Line should be of format 'key = value'
        // Strip whitespaces and parse as 'key=value'
        line.erase(std::remove(line.begin(), line.end(), ' '), line.end());

        std::size_t delimPos = line.find('=');
        if (delimPos == std::string::npos)
            continue;

        // Insert values into map
        m_configMap.insert({ line.substr(0,delimPos), line.substr(delimPos + 1) });
    }

    return true;
}

