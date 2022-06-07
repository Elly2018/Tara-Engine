#include <iostream>
#include <memory>
#include <exception>
#include "creator.h"
#include "../engine/core/utility.h"

using namespace Tara;
/*
	Summary:
		Program entry point.
*/
int main(int argc, char** argv) {
	Utility::Argument::Singleton().Register(argc, argv);
	if (!Utility::Argument::Singleton().debugMode) Logger::HideConsole();
	std::unique_ptr<TaraApplication> app = std::make_unique<TaraApplication>();
	if (!app->Initialization()) {
		throw std::exception("Application initialization failed");
		return -1;
	}
	app->Run();
	return 0;
}
