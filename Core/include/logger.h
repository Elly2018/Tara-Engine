#pragma once
#include <vector>
#include <string>
#include <glm/glm.hpp>

namespace Tara {
	struct __declspec(dllexport) LogMessage {
	public:
		std::string message;
		glm::vec3 color;
	};

	typedef void(*OnLog)(std::vector<LogMessage> n);

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
		static void RegisterLog(OnLog logCallback);

	private:
		/*
			Summary:
				The log message struct
		*/
		static std::vector<LogMessage> messages;
		static std::vector<OnLog> events;
		static int32_t lastPosition;
		static int32_t lastLocation;
	};
}