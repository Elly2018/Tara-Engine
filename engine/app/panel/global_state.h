#pragma once
#include <vector>
#include "../../engine/core/config.h"
#include "../../engine/core/framebuffer/framebuffer.h"
#include "../../engine/core/renderer/renderer.h"
#include "allpanel.h"

namespace Tara {
	class TARA_API Scene;
	class TARA_API SceneObject;
	class TARA_API CameraComponent;

	namespace UI {
		/*
			Summary:
				Pst processing configuration for scene viewer.
				Apply it in update stage.
		*/
		struct TARA_API PostProcessConfig {
		public:
			MSAASamples m_sample = MSAASamples::None;
			// Is config dirty.
			bool m_update = false;
		};

		/*
			Summary:
				The collection of application use panels.
		*/
		class TARA_API PanelCollection {
		public:
			PanelCollection();
			~PanelCollection();

			AssetWindow* asset = nullptr;
			//FileExplorerWindow* fileExplorer;
			SceneViewerWindow* sceneViewer = nullptr;
			PropertiesWindow* properties = nullptr;
			HierarchyWindow* hierarchy = nullptr;
			HelperWindow* helperTips = nullptr;
			ConsoleWindow* console = nullptr;
			AppSettingWindow* appsetting = nullptr;
			FileExplorerWindow* fileexplorer = nullptr;

			// Popup
			ProjectCreationWindow* projectcreation = nullptr;

			std::vector<ImGui_WindowBase*> GetWins();
		};


		/*
			Summary:
				The collection of application use panels when dev mode is on.
		*/
		class TARA_API DevPanelCollection {
		public:
			DevPanelCollection();
			~DevPanelCollection();
		};

		class TARA_API PanelGlobalState final : public PanelCollection {
		public:
			static PanelGlobalState& Singleton();
			std::vector<Scene*> allScene = std::vector<Scene*>();
			SceneObject* focusedSceneObject = nullptr;
			ObjectBase* focusedObject = nullptr;
			PostProcessConfig post = PostProcessConfig();
			CameraComponent* selectCameraObject = nullptr;
			// Current render state.
			RenderState m_render = RenderState();
			// Properties panel fields display.
			bool debug = false;
			// Update function call.
			bool shouldUpdateScene = false;
			// Render function call.
			bool shouldRenderScene = false;
			// Should application record state.
			bool shouldRecordRenderState = true;
			// Show gizmo on scene viewer.
			bool showGizmo = false;
			// Should dev penal collection return.
			bool devMode = false;
			/*
				0: 
				1:
			*/
			int32_t rendermode = 0;

			/*
				Summary:
					Return application dev use panels.
					This will return nullptr is dev mode is false.
			*/
			DevPanelCollection* GetDevPanels();

		private:
			PanelCollection* panelCollection = nullptr;
			DevPanelCollection* devPanelCollection = nullptr;

		private:
			PanelGlobalState();
			~PanelGlobalState();
			static PanelGlobalState* m_singleton;
		};
	}
}