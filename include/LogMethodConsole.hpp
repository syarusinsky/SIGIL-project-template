#ifndef LOGMETHODCONSOLE_HPP
#define LOGMETHODCONSOLE_HPP

/**************************************************************************
 * The LogMethodConsole classes provides the ability to log to the console
 * at a given logging level (error, warn, info).
**************************************************************************/

#include "LogMethods.hpp"

class LogMethodConsole : public LogMethod
{
	public:
		void log (const LogLevel& level, std::string message) const override;
};

#endif // LOGMETHODCONSOLE_HPP
