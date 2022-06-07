#include "creator.h"
#include <filesystem>
#include "engine/core/logger.h"
#include "engine/tara.h"
#include "engine/core/window/ewindow.h"
#include "engine/extension/tara_extension.h"
#include "engine/core/renderer/renderer.h"
#include "editor/editor.h"
#include "appcore/global_panels.h"
#include "appcore/global_states.h"
#include "window/app_window.h"
#include "engine/core/buildin/buildin_manager.h"

/*
	Panels includes
*/
#include "asset_win.h"
#include "code_editor_win.h"
#include "console_win.h"
#include "debug_win.h"
#include "export_win.h"
#include "file_explorer_win.h"
#include "framebuffer_viewer_win.h"
#include "helper_win.h"
#include "hierarchy_win.h"
#include "node_editor_win.h"
#include "project_creation_win.h"
#include "properties_win.h"
#include "scene_viewer_win.h"
#include "setting_win.h"
#include "timeline_win.h"

namespace Tara {
	TaraApplication::TaraApplication()
	{
		extensions = std::list<std::shared_ptr<Extension>>();
	}

	TaraApplication::~TaraApplication()
	{
		for (auto ext : extensions) ext.reset();
		extensions.clear();
	}

	bool TaraApplication::Initialization()
	{
		if (!Tara_Initialization()) {
			return false;
		}
		return true;
	}
	bool TaraApplication::RegisterExtension(std::shared_ptr<Extension> extension)
	{
		if (!extension->Initialization()) {
			return false;
		}
		extensions.push_back(extension);
		return true;
	}
	void TaraApplication::Run()
	{	
		TARA_DEBUG_LEVEL("Start application run method", 2);
		RegisterGlobalPanel();
		GlobalPanels& pg = GlobalPanels::Singleton();
		UI::ConsoleWindow* console = pg.GetPanel<UI::ConsoleWindow>("Console");
		UI::HelperWindow* helper = pg.GetPanel<UI::HelperWindow>("Helper");

		Logger::RegisterLog(std::bind(&UI::ConsoleWindow::AddMessage, console, std::placeholders::_1));
		helper->SetVisible(false);

		// Create app window
		std::unique_ptr<AppWindow> app = std::make_unique<AppWindow>();
		// Editor init
		UI::Tara_GUI_Initialization();
		
		for (auto& i : pg.GetPanels()) {
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
	}


	GlobalPanels& TaraApplication::RegisterGlobalPanel()
	{
		GlobalPanels& pg = GlobalPanels::Singleton();
		pg.AddPanel("Asset", new UI::AssetWindow());
		pg.AddPanel("Console", new UI::ConsoleWindow());
#ifdef _TDEBUG
		pg.AddPanel("Debug", new UI::DebugWindow());
#endif
		pg.AddPanel("FileExplorerWindow", new UI::FileExplorerWindow());
		pg.AddPanel("FrameBuffer", new UI::FramebufferViewerWindow());
		pg.AddPanel("Helper", new UI::HelperWindow());
		pg.AddPanel("Hierarchy", new UI::HierarchyWindow());
		pg.AddPanel("Node", new UI::NodeEditorWindow());
		pg.AddPanel("ProjectCreation", new UI::ProjectCreationWindow());
		pg.AddPanel("Property", new UI::PropertiesWindow());
		pg.AddPanel("Scene", new UI::SceneViewerWindow());
		pg.AddPanel("Setting", new UI::AppSettingWindow());
		return pg;
	}
}