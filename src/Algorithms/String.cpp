#include "String.hpp"

#include <vector>
#include <string>

#include "Setup.hpp"

namespace Tolik
{
std::vector<std::string> SplitString(const std::string &str, const std::string &delimeter)
{
	std::vector<std::string> result;
	
	std::size_t fromPosition = 0;
	for(std::size_t delimetrPosition = str.find(delimeter); delimetrPosition != std::string::npos; delimetrPosition = str.find(delimeter, delimetrPosition + 1))
	{
		std::string element = str.substr(fromPosition, delimetrPosition - fromPosition);
		if(!element.empty())
			result.push_back(element);
		fromPosition = delimetrPosition + delimeter.length();
	}
	
	std::string element = str.substr(fromPosition, str.length());
	if(!element.empty())
		result.push_back(element);
	
	return result;
}
}