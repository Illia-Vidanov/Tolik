#include "Utilities/FileReader.hpp"

#include <fstream>
#include <string>

#include "Setup.hpp"

#include "Debug/Debug.hpp"

namespace Tolik
{
void FileReader::ReadTxtFile(const std::string &path, std::string &output)
{
  std::ifstream file(path);
  if(file.bad())
  {
    //Debug::GetLogger().Error("Can't read file ", path);
    return;
  }
  file.seekg(0, std::ios::end);
  output.reserve(static_cast<int>(file.tellg()) + output.length());
  file.seekg(0, std::ios::beg);
  output.insert(output.end(), (std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
}

std::string FileReader::GetExtention(const std::string &path)
{
  auto check = [&path](std::size_t pos) -> std::size_t { if(pos == std::string::npos) return 0; else return pos; };
  std::size_t slashPos = std::max(check(path.rfind('\\')), check(path.rfind('/')));
  std::size_t dotPos = check(path.rfind('.'));
  if(dotPos > slashPos)
    return std::string(&path[dotPos + 1], &path[path.size()]);
  return std::string();
}
};