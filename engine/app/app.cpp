#include "app.h"
#include <filesystem>
#include "../engine/core/logger.h"
#include "../engine/tara.h"
#include "../engine/core/window/ewindow.h"
#include "../extension/tara_extension.h"
#include "../engine/core/renderer/renderer.h"
#include "../editor/editor.h"
#include "panel/global_state.h"
#include "window/app_window.h"
#include "../engine/core/buildin/buildin_manager.h"

namespace Tara {
	TaraApplication* TaraApplication::m_app = new TaraApplication();

	TaraApplication::TaraApplication()
	{
		extensions = std::list<Extension*>();
	}

	TaraApplication& TaraApplication::Singleton()
	{
		return *m_app;
	}
	bool TaraApplication::Initialization()
	{
		if (!Tara_Initialization()) {
			return false;
		}

		//resources.tara
		BuildinManager::Singleton();
		return true;
	}
	bool TaraApplication::RegisterExtension(Extension* extension)
	{
		if (!extension->Initialization()) {
			return false;
		}
		extensions.push_back(extension);
		return true;
	}
	void TaraApplication::Run()
	{
		// Register all editor windows here
		UI::PanelGlobalState& pg = UI::PanelGlobalState::Singleton();

		Logger::RegisterLog(std::bind(&UI::ConsoleWindow::AddMessage, pg.console, std::placeholders::_1));
		pg.helperTips->SetVisible(false);

		// Create app window
		AppWindow* app = new AppWindow();
		// Editor init
		UI::Tara_GUI_Initialization();
		
		for (auto& i : pg.GetWins()) {
			UI::AddGUIWindow(i);
		}

		// Enter application cycle
		app->Run();

		// We have to delete all the register logger events.
		// Otherwise it will call a nullptr if we keep it.
		Logger::CleanEvent();
		// Destroy ImGui context.
		UI::Tara_GUI_Shutdown();
		// Destroy tara application context.
		Tara_Shutdown();
		delete app;
	}
}