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

	struct TARA_API LogMessage {
	public:
		std::string message;
		std::string tag;
		int32_t level;
		glm::vec3 color;
	};

	enum class TARA_API LoggerStreamType {
		STDOUT,
		STDERR
	};

	enum class TARA_API LoggerType {
		Log,
		Warning,
		Error,
		Exception
	};

	class TARA_API Logger
	{
	public:
		/*
			Summary:
				Catch all stdout into file.
				DEBUG_FILENAME define the log output file.
		*/
		static void LogToFile(LoggerStreamType type = LoggerStreamType::STDOUT);
		static void LogToConsole(LoggerStreamType type = LoggerStreamType::STDOUT);
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
		static std::vector<LogMessage> GetApplicationLog();
		static void RegisterLog(std::function<void(LogMessage)> logCallback);
		static void RegisterClean(std::function<void()> logCallback);
		static void CleanEvent();

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

			std::string real_message = Logger::FormatString(message, args ...);
			std::string main = Logger::FormatString("[%s | %s | %i] %s", typestring.c_str(), Tag.c_str(), level, real_message.c_str());
			LogMessage current = LogMessage();
			current.color = typecolor;
			current.level = level;
			current.tag = Tag.c_str();
			current.message = main;
			messages.push_back(current);

			for (auto& i : events) {
				i(current);
			}

			main += "\n";
			printf(main.c_str());
		}
		static void PrintStackTrace();
		static void Clean();

	private:
		/*
			Summary:
				The log message struct
		*/
		static std::vector<LogMessage> messages;
		static std::vector<std::function<void(LogMessage)>> events;
		static std::vector<std::function<void()>> cevents;
		template<typename ... Args>
		static std::string FormatString(std::string main, Args ... args) {
			int size_s = std::snprintf(nullptr, 0, main.c_str(), args ...) + 1; // Extra space for '\0'
			if (size_s <= 0) { throw std::runtime_error("Error during formatting."); }
			auto size = static_cast<size_t>(size_s);
			auto buf = std::make_unique<char[]>(size);
			std::snprintf(buf.get(), size, main.c_str(), args ...);
			return std::string(buf.get(), buf.get() + size - 1); // We don't want the '\0' inside
		}

		static int32_t lastPosition;
		static int32_t lastLocation;
	};
}