#ifndef TOLIK_UTILITIES_FILE_READER_HPP
#define TOLIK_UTILITIES_FILE_READER_HPP

#include <string>
#include <sys/stat.h>

#include "Setup.hpp"

namespace Tolik
{
class FileReader
{
public:
  static void ReadTxtFile(const std::string &path, std::string &output);
};
} // Tolik

#endif // TOLIK_UTILITIES_FILE_READER_HPP