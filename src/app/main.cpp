#include <iostream>
#include <exception>
#include "app.h"
#include "../engine/core/utility.h"

using namespace Tara;
/*
	Summary:
		Program entry point.
*/
int main(int argc, char** argv) {
	Utility::Argument::Singleton().Register(argc, argv);
	if (!Utility::Argument::Singleton().debugMode) Logger::HideConsole();
	TaraApplication& app = TaraApplication::Singleton();
	try {
		if (!app.Initialization()) {
			throw std::exception("Application initialization failed");
			return -1;
		}
		app.Run();
	}
	catch (std::exception e) {
		TARA_ERROR("%s", e.what());
		system("PAUSE");
		return -1;
	}
	return 0;
}
