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
  static std::string GetExtention(const std::string &path);
  static inline bool FileExists(const std::string &path) { struct stat buffer; return (stat(path.c_str(), &buffer) == 0); }
};
} // Tolik

#endif // TOLIK_UTILITIES_FILE_READER_HPP