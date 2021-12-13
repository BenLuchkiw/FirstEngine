#include "Logging.hpp"

namespace Logging
{
	namespace
	{
		bool fileOpened = false; // I see no reason to create a global object so this will work
	}
	void printColour(std::string message, ConsoleColour colour)
	{
		std::string temp = "%c[xxm" + message;
		temp.replace(3, 2, std::to_string(colour));
		printf(temp.c_str(), 27);
		printf("%c[37m\n", 27); // New line and resets colour
	}

	void logCode(std::string message, LogLevel code)
	{
		switch (code)
		{
		case LOG_LEVEL_GENERIC: // Bright White
			printColour(message, CONSOLE_COLOUR_GREY);
			logToFile("Generic:\n" + message);
			break;

		case LOG_LEVEL_INFO:    // Bright Green
			printColour("\nInfo:", CONSOLE_COLOUR_BRIGHT_GREEN);
			printColour(message, CONSOLE_COLOUR_BRIGHT_GREEN);
			logToFile("Info:\n" + message);
			break;

		case LOG_LEVEL_WARNING: // Yellow
			printColour("\nWarning:", CONSOLE_COLOUR_BRIGHT_YELLOW);
			printColour(message, CONSOLE_COLOUR_BRIGHT_YELLOW);
			logToFile("Warning:\n" + message);
			break;

		case LOG_LEVEL_ERROR:   // Bright Red
			printColour("\nError:", CONSOLE_COLOUR_BRIGHT_RED);
			printColour(message, CONSOLE_COLOUR_BRIGHT_RED);
			logToFile("Error:\n" + message);
			break;

		case LOG_LEVEL_FATAL:   // Bright Magenta
			printColour("\nFatal:", CONSOLE_COLOUR_BRIGHT_MAGENTA);
			printColour(message, CONSOLE_COLOUR_BRIGHT_MAGENTA);
			logToFile("Fatal:\n" + message);
			break;
		}

	}

	void logCode(std::string message, LogLevel code, std::string file, int line)
	{
		logCode("File: " + file + ", line: " + std::to_string(line) + message, code);
	}

	void logToFile(std::string message)
	{
		std::ofstream stream;
		if (!fileOpened) // If the file has not been opened yet it will be cleared
		{
			stream.open(ROOT_DIR + std::string("/src/Logging/Dump.txt"), std::ostream::trunc | std::ofstream::out);
			fileOpened = true;
		}
		else
		{
			stream.open(ROOT_DIR + std::string("/src/Logging/Dump.txt"), std::ofstream::out | std::ofstream::app);
		}

		if (!stream.is_open())
		{
			return;
		}
		message += "\n\n";
		stream.write(message.c_str(), message.size());

		stream.close();
	}

};