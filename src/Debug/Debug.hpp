#ifndef TOLIK_DEBUG_HPP
#define TOLIK_DEBUG_HPP

#include <unordered_map>
#include <string>

#include "Setup.hpp"

#include "Debug/Logger.hpp"

namespace Tolik
{
class Debug
{
public:
	Debug();
	static const Debug &Get() { return s_instance; }
	static Logger &GetLogger(const std::string &name = "main"); // Can't return const reference because of optimization
	static void AddLogger(const std::string &name, const Logger &logger);

private:
	std::unordered_map<std::string, Logger> m_loggers;
  
	static Debug s_instance;
};
}

#endif