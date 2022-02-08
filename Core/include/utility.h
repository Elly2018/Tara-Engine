#pragma once
#include <string>
#include <config.h>

namespace Tara {
	class DllExport Utility
	{
	public:
		const char* AddressToChar();

		class DllExport File {
		public:
			/*
				Summary:
					Loading string from file
			*/
			static std::string LoadFromFile(const char* filename);
		};

		class DllExport Debug {
		public:
			/*
				Summary:
					Loading string from file
			*/
			static void PrintTrace();
			static const char* CurrentTimeString();
		};

		class DllExport String {
		public:
			static void RemoveString(std::string& main, std::string find);
		};
	};
}