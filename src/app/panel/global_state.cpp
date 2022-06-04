#include "global_state.h"

namespace Tara {
	namespace UI {
		PanelGlobalState* PanelGlobalState::m_singleton = nullptr;
		PanelCollection::PanelCollection() {
			console = new ConsoleWindow();
			asset = new AssetWindow();
			sceneViewer = new SceneViewerWindow("Scene viewer");
			properties = new PropertiesWindow();
			hierarchy = new HierarchyWindow();
			helperTips = new HelperWindow();
			appsetting = new AppSettingWindow();
			nodeeditor = new NodeEditorWindow();
		}
		PanelCollection::~PanelCollection() {
			delete asset;
			delete sceneViewer;
			delete properties;
			delete hierarchy;
			delete helperTips;
			delete console;
			delete appsetting;
			delete nodeeditor;
		}

		std::vector<ImGui_WindowBase*> PanelCollection::GetWins()
		{
			return std::vector<ImGui_WindowBase*>({ 
				asset,
				sceneViewer,
				properties,
				hierarchy,
				helperTips,
				console,
				appsetting,
				nodeeditor,
				});
		}

		DevPanelCollection::DevPanelCollection() {

		}
		DevPanelCollection::~DevPanelCollection() {

		}

		PanelGlobalState& PanelGlobalState::Singleton() {
			if (m_singleton == nullptr) m_singleton = new PanelGlobalState();
			return *m_singleton;
		}

		DevPanelCollection* PanelGlobalState::GetDevPanels() {
			if (devMode && !devPanelCollection) {
				devPanelCollection = new DevPanelCollection();
				return devPanelCollection;
			}
			else if (devMode && devPanelCollection) {
				return devPanelCollection;
			}
			else if (!devMode && devPanelCollection) {
				delete devPanelCollection;
			}
			else {
				return nullptr;
			}
		}

		PanelGlobalState::PanelGlobalState() : PanelCollection() {
			panelCollection = new PanelCollection();
		}

		PanelGlobalState::~PanelGlobalState() {
			delete panelCollection;
			if (devPanelCollection) delete devPanelCollection;
		}
	}
}