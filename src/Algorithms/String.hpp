#ifndef TOLIK_ALGORITHMS_STRING_HPP
#define TOLIK_ALGORITHMS_STRING_HPP

#include <vector>
#include <string>

#include "Setup.hpp"

namespace Tolik
{
std::vector<std::string> SplitString(const std::string &str, const std::string &delimeter);
inline std::vector<std::string> SplitString(const std::string &str, char delimeter) { return SplitString(str, std::string(1, delimeter)); }
} // Tolik

#endif // TOLIK_ALGORITHMS_STRING_HPP