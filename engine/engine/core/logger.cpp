#include "logger.h"
#include <iostream>
#include <stdarg.h>
#include <fstream>
#define NOMINMAX
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
#include <Windows.h>
#define TARA_WINDOW
#endif

#include <backward.hpp>
#include <glm/glm.hpp>

#include "config.h"

namespace Tara {
	std::vector<LogMessage> Logger::messages = std::vector<LogMessage>();
	std::vector<std::function<void(LogMessage)>> Logger::events = std::vector<std::function<void(LogMessage)>>();
	std::vector<std::function<void()>> Logger::cevents = std::vector<std::function<void()>>();
	int32_t Logger::lastPosition = -1;

	void Logger::LogToFile(LoggerStreamType type)
	{
		FILE* stream = nullptr;
		switch (type) {
		case LoggerStreamType::STDOUT:
			stream = freopen(DEBUG_FILENAME, "w", stdout);
			break;
		case LoggerStreamType::STDERR:
			stream = freopen(DEBUG_FILENAME, "w", stderr);
			break;
		}
		if(stream) setvbuf(stream, 0, _IONBF, 0); // No Buffering
	}
	void Logger::LogToConsole(LoggerStreamType type)
	{
		FILE* stream = nullptr;
		switch (type) {
		case LoggerStreamType::STDOUT:
			stream = freopen("CONOUT$", "w", stdout);
			break;
		case LoggerStreamType::STDERR:
			stream = freopen("CONOUT$", "w", stderr);
			break;
		}
		if (stream) setvbuf(stream, 0, _IONBF, 0); // No Buffering
	}
	void Logger::Flush() {
		fflush(stdout);
		fflush(stderr);
	}
	void Logger::HideConsole() {
		::ShowWindow(::GetConsoleWindow(), SW_HIDE);
	}
	void Logger::ShowConsole() {
		::ShowWindow(::GetConsoleWindow(), SW_SHOW);
	}
	std::vector<LogMessage> Logger::GetApplicationLog() {
		return messages;
	}
	void Logger::RegisterLog(std::function<void(LogMessage)> logCallback)
	{
		if (logCallback != nullptr) {
			events.push_back(logCallback);
		}
	}
	void Logger::RegisterClean(std::function<void()> logCallback)
	{
		if (logCallback != nullptr) {
			cevents.push_back(logCallback);
		}
	}
	void Logger::CleanEvent()
	{
		events.clear();
		cevents.clear();
	}

	void Logger::PrintStackTrace()
	{
		backward::StackTrace st; st.load_here(32);
		backward::Printer p;
		p.object = true;
		p.color_mode = backward::ColorMode::always;
		p.address = true;
		p.print(st);
	}

	void Logger::Clean()
	{
		messages.clear();
		for (auto& i : cevents) {
			i();
		}
	}
}