#pragma once
// Import std library
#include <map>
#include <vector>
#include <string>
#include <functional>

// Include third party library
#include <glm/glm.hpp>

namespace Tara {
#define DLLEXPORT __declspec( dllexport )
#define DLLIMPORT __declspec( dllimport )

#ifndef TARA_APP_API
	#define TARA_APP_API
#endif // !DLLEXPORT
#ifndef TARA_API
	#define TARA_API
#endif // !DLLEXPORT
#ifndef TARA_EDITOR_API
	#define TARA_EDITOR_API
#endif // !DLLEXPORT


// Printf color normal
#define KNRM  "\x1B[0m"
// Printf color red
#define KRED  "\x1B[31m"
// Printf color green
#define KGRN  "\x1B[32m"
// Printf color yellow
#define KYEL  "\x1B[33m"
// Printf color blue
#define KBLU  "\x1B[34m"
// Printf color magenta
#define KMAG  "\x1B[35m"
// Printf color cyan
#define KCYN  "\x1B[36m"
// Printf color white
#define KWHT  "\x1B[37m"

	enum class TARA_API LoggerType;

	struct TARA_API LogMessage {
		LogMessage() = default;
		std::string message;
		std::string tag;
		int32_t level;
		glm::vec3 color;
		LoggerType type;
	};

	enum class TARA_API LoggerStreamType {
		STDOUT,
		STDERR
	};

	enum class TARA_API LoggerType {
		Log = 1 << 0,
		Warning = 1 << 1,
		Error = 1 << 2,
		Exception = 1 << 3
	};

	namespace Logger {
		/*
			Summary:
				Catch all stdout into file.
				DEBUG_FILENAME define the log output file.
		*/
		TARA_API void LogToFile(LoggerStreamType type = LoggerStreamType::STDOUT);
		TARA_API void LogToConsole(LoggerStreamType type = LoggerStreamType::STDOUT);
		/*
			Summary:
				Menually flush the stdout.
				Clean the stdout buffer.
		*/
		TARA_API void Flush();
		/*
			Summary:
				Hide the console window (Not cross platform support).
		*/
		TARA_API void HideConsole();
		/*
			Summary:
				Show the console window (Not cross platform support)
		*/
		TARA_API void ShowConsole();
		/*
			Summary:
				Application debug output.
				This call does not use stdout, instead it save into log memory.
		*/
		TARA_API std::vector<LogMessage> GetApplicationLog();
		TARA_API void RegisterLog(std::function<void(LogMessage)> logCallback);
		TARA_API void RegisterClean(std::function<void()> logCallback);
		TARA_API void CleanEvent();

		static std::vector<LogMessage> messages = std::vector<LogMessage>();
		static std::vector<std::function<void(LogMessage)>> events = std::vector<std::function<void(LogMessage)>>();
		static std::vector<std::function<void()>> cevents = std::vector<std::function<void()>>();
		static int32_t lastPosition = -1;
		static int32_t lastLocation = -1;

		template<typename ... Args>
		static std::string FormatString(std::string main, Args ... args) {
			int size_s = std::snprintf(nullptr, 0, main.c_str(), args ...) + 1; // Extra space for '\0'
			if (size_s <= 0) { throw std::runtime_error("Error during formatting."); }
			auto size = static_cast<size_t>(size_s);
			auto buf = std::make_unique<char[]>(size);
			std::snprintf(buf.get(), size, main.c_str(), args ...);
			return std::string(buf.get(), buf.get() + size - 1); // We don't want the '\0' inside
		}

		template<typename ... Args>
		static void Print(LoggerType type, int32_t level, std::string Tag, std::string message, Args ... args) {
			std::string typestring = "";
			glm::vec3 typecolor = glm::vec3(1);
			switch (type) {
			case LoggerType::Log:
				typestring = "Log";
				break;
			case LoggerType::Warning:
				typestring = "Warning";
				break;
			case LoggerType::Error:
				typestring = "Error";
				break;
			case LoggerType::Exception:
				typestring = "Exception";
				break;
			}
			switch (type) {
			case LoggerType::Log:
				typecolor = glm::vec3(1, 1, 1);
				break;
			case LoggerType::Warning:
				typecolor = glm::vec3(1, 1, 0);
				break;
			case LoggerType::Error:
				typecolor = glm::vec3(1, 0, 0);
				break;
			case LoggerType::Exception:
				typecolor = glm::vec3(1, 0, 0);
				break;
			}

			std::string real_message = FormatString(message, args ...);
			std::string main = FormatString("[%s | %s | %i] %s", typestring.c_str(), Tag.c_str(), level, real_message.c_str());
			LogMessage current = LogMessage();
			current.color = typecolor;
			current.level = level;
			current.tag = Tag.c_str();
			current.message = main;
			current.type = type;
			messages.push_back(current);

			for (auto& i : events) {
				i(current);
			}

			main += "\n";
			printf(main.c_str());
		}
		TARA_API void PrintStackTrace();
		TARA_API void Clean();
	}
}