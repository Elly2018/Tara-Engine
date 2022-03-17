#pragma once
// Import std library
#include <vector>
#include <string>
#include <functional>

// Include third party library
#include <glm/glm.hpp>

namespace Tara {
	struct __declspec(dllexport) LogMessage {
	public:
		std::string message;
		glm::vec3 color;
	};

	class __declspec(dllexport) Logger
	{
	public:
		/*
			Summary:
				Catch all stdout into file.
				DEBUG_FILENAME define the log output file.
		*/
		static void LogToFile();
		/*
			Summary:
				Menually flush the stdout.
				Clean the stdout buffer.
		*/
		static void Flush();
		/*
			Summary:
				Hide the console window (Not cross platform support).
		*/
		static void HideConsole();
		/*
			Summary:
				Show the console window (Not cross platform support)
		*/
		static void ShowConsole();
		/*
			Summary:
				Application debug output.
				This call does not use stdout, instead it save into log memory.
		*/
		static void ApplicationLog(const char* n);
		static std::vector<LogMessage> GetApplicationLog();
		static void RegisterLog(std::function<void(std::vector<LogMessage>)> logCallback);
		static void CleanEvent();

	private:
		/*
			Summary:
				The log message struct
		*/
		static std::vector<LogMessage> messages;
		static std::vector<std::function<void(std::vector<LogMessage>)>> events;
		static int32_t lastPosition;
		static int32_t lastLocation;
	};
}