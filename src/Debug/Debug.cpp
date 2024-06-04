#include "Debug/Debug.hpp"

#include <unordered_map>
#include <string>

#include "Setup.hpp"

#include "Debug/Logger.hpp"

namespace Tolik
{
Debug Debug::s_instance = Debug();

Debug::Debug()
{
	AddLogger("main", Logger("[@T] @M\n"));
}

void Debug::AddLogger(const std::string &name, const Logger &logger)
{
	std::unordered_map<std::string, Logger>::iterator it = s_instance.m_loggers.find(name);
	if(it != s_instance.m_loggers.end())
	{
		//GetLogger("main").Error("Logger with name: \'@0\', already exists", name);
		return;
	}
	s_instance.m_loggers.emplace_hint(it, name, logger);
}

Logger &Debug::GetLogger(const std::string &name)
{
  std::unordered_map<std::string, Logger>::iterator it = s_instance.m_loggers.find(name);
	if(it == s_instance.m_loggers.end())
	{
		//GetLogger("main").Error("No logger with name: \'@0\'", name);
		return s_instance.m_loggers.at("main");
	}
	return it->second;
}
}