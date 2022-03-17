#include "logger.h"
#include <iostream>
#include <stdarg.h>
#include <fstream>
#define NOMINMAX
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
#include <Windows.h>
#define TARA_WINDOW
#endif

#include <glm/glm.hpp>

#include "config.h"

namespace Tara {
	const std::string systemtag = "[System]";
	const std::string warningtag = "[Warning]";
	const std::string errortag = "[Error]";
	std::vector<LogMessage> Logger::messages = std::vector<LogMessage>();
	std::vector<std::function<void(std::vector<LogMessage>)>> Logger::events = std::vector<std::function<void(std::vector<LogMessage>)>>();
	int32_t Logger::lastPosition = -1;

	bool ReadLogger(std::string prefix, glm::vec3 color, std::vector<LogMessage>* buffer, bool* first, std::string line, LogMessage* current) {
		bool find = line.rfind(prefix, 0) == 0;
		if (find) {
			if (!(*first)){
				// Push last message
				(*buffer).push_back(*current);
				(*current) = LogMessage();
			}
			line.erase(0, prefix.size());
			(*current).message.clear();
			(*current).color = color;
			(*current).message = line;
			(*first) = false;
		}
		return find;
	}

	void Logger::LogToFile()
	{
#ifndef TARA_NO_LOGGER
		FILE* stream = freopen(DEBUG_FILENAME, "w", stdout); // Added missing pointer
		setvbuf(stream, 0, _IONBF, 0); // No Buffering
#endif // !TARA_NO_LOGGER
	}
	void Logger::Flush()
	{
		fflush(stdout);
		std::vector<LogMessage> r = GetApplicationLog();
		if (r.size() > 0) {
			for (auto e : events) {
				if(e != nullptr) e(r);
			}
		}
	}
	void Logger::HideConsole() {
#ifdef TARA_WINDOW
		::ShowWindow(::GetConsoleWindow(), SW_HIDE);
#endif
	}
	void Logger::ShowConsole() {
#ifdef TARA_WINDOW
		::ShowWindow(::GetConsoleWindow(), SW_SHOW);
#endif
	}
	void Logger::ApplicationLog(const char* n)
	{
	}
	std::vector<LogMessage> Logger::GetApplicationLog() {
		std::vector<LogMessage> result = std::vector<LogMessage>();
		std::ifstream input(DEBUG_FILENAME);

		LogMessage current = LogMessage();
		bool first = true;
		std::string line;
		int32_t currentPos = 0;
		bool finish = false;

		while (!finish)
		{
			currentPos++;
			if (currentPos < lastPosition) {
				input.ignore(std::numeric_limits<std::streamsize>::max(), input.widen('\n'));
				finish = input.eof();
				continue;
			}
			else {
				std::getline(input, line);
				finish = input.eof();
			}
			if (ReadLogger(systemtag, LOGCOLOR_NORMAL, &result, &first, line, &current)) continue;
			else if (ReadLogger(warningtag, LOGCOLOR_WARNING, &result, &first, line, &current)) continue;
			else if (ReadLogger(errortag, LOGCOLOR_ERROR, &result, &first, line, &current)) continue;
			else current.message += line;
		}
		if (!first) {
			result.push_back(current);
		}
		lastPosition = currentPos;
		return result;
	}
	void Logger::RegisterLog(std::function<void(std::vector<LogMessage>)> logCallback)
	{
		if (logCallback != nullptr) {
			events.push_back(logCallback);
		}
	}
	void Logger::CleanEvent()
	{
		events.clear();
	}
}