#include "LogMethodConsole.hpp"

#include "LLPD.hpp"
#include "LogLevels.hpp"

#define LOGGING_USART_NUM USART_NUM::USART_2

void LogMethodConsole::log (const LogLevel& level, std::string message) const
{
	LLPD::usart_log( LOGGING_USART_NUM, message.c_str() );
}
