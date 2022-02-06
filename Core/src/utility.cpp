#include "utility.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <filesystem>
#include <backward.hpp>

namespace Tara {

	const char* Utility::AddressToChar()
	{
		const void* address = static_cast<const void*>(this);
		std::stringstream ss;
		ss << address;
		return ss.str().c_str();
	}

	std::string Utility::File::LoadFromFile(const char* filename)
	{	
		std::string line = "", text = "";
		std::ifstream in(filename);
		if (!in.good()) {
			TARA_ERROR_LEVEL("File does not exist: %s", 2, filename);
			return nullptr;
		}
		while (std::getline(in, line))
		{
			text += line + "\n";
		}
		return text;
	}

	void Utility::Debug::PrintTrace() {
		backward::StackTrace st; st.load_here(32);
		backward::Printer p;
		p.object = true;
		p.color_mode = backward::ColorMode::always;
		p.address = true;
		p.print(st);
	}

	const char* Utility::Debug::CurrentTimeString()
	{
		time_t rawtime;
		struct tm* timeinfo;
		char buffer[80];

		time(&rawtime);
		timeinfo = localtime(&rawtime);

		strftime(buffer, sizeof(buffer), "%d-%m-%Y %H:%M:%S", timeinfo);
		std::string str(buffer);

		return str.c_str();
	}
}