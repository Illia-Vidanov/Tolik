#ifndef TOLIK_ALGORITHMS_STRING_HPP
#define TOLIK_ALGORITHMS_STRING_HPP

#include <vector>
#include <string>

#include "Setup.hpp"

namespace Tolik
{
std::vector<std::string> SplitString(const std::string &str, const std::string &delimeter);
inline std::vector<std::string> SplitString(const std::string &str, char delimeter)
{ return SplitString(str, std::string(1, delimeter)); }

// TODO:
// 1. Encodings (wide char, utf8, utf16, utf32)
// 2. String reverse (with consideration of encoding)
// 3. Random acces of encoded strings
} // Tolik

#endif // TOLIK_ALGORITHMS_STRING_HPP