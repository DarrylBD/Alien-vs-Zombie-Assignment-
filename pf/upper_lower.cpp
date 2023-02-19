#include "upper_lower.h"
#include <cstdlib>
#include <algorithm>
#include <iostream>

namespace pf
{
    // custom: lowercase
    std::string LowerCaseConvert(std::string data)
    {
        std::transform(data.begin(), data.end(), data.begin(), [](unsigned char c) { return std::tolower(c); });
        return data;
    }

    // custom: uppercase
    std::string UpperCaseConvert(std::string data)
    {
        std::transform(data.begin(), data.end(), data.begin(), [](unsigned char c) { return std::toupper(c); });
        return data;
    }
}