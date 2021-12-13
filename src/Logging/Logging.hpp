#pragma once

#include "Core/FirstEngineInclude.hpp"

enum ConsoleColour // Numbers correspond to ANSI sequences
{
	CONSOLE_COLOUR_BLACK			= 30,
	CONSOLE_COLOUR_RED,
	CONSOLE_COLOUR_GREEN,
	CONSOLE_COLOUR_YELLOW,
	CONSOLE_COLOUR_BLUE,
	CONSOLE_COLOUR_MAGENTA,
	CONSOLE_COLOUR_CYAN,
	CONSOLE_COLOUR_WHITE,
	CONSOLE_COLOUR_GREY				= 90,
	CONSOLE_COLOUR_BRIGHT_RED,
	CONSOLE_COLOUR_BRIGHT_GREEN,
	CONSOLE_COLOUR_BRIGHT_YELLOW,
	CONSOLE_COLOUR_BRIGHT_BLUE,
	CONSOLE_COLOUR_BRIGHT_MAGENTA,
	CONSOLE_COLOUR_BRIGHT_CYAN,
	CONSOLE_COLOUR_BRIGHT_WHITE
};

enum LogLevel
{
	LOG_LEVEL_GENERIC = 0,
	LOG_LEVEL_INFO,
	LOG_LEVEL_WARNING,
	LOG_LEVEL_ERROR,
	LOG_LEVEL_FATAL
};

namespace Logging
{
	void printColour(std::string message, ConsoleColour colour);

	void logCode(std::string message, LogLevel code);

	void logCode(std::string message, LogLevel code, std::string file, int line);

	void logToFile(std::string message);
};