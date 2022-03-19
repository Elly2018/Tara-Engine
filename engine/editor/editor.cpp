#include "editor.h"
// Include Std library
#include <functional>

// Include Third party library
#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>
//#include <glad/glad.h>
//#include <GLFW/glfw3.h>

// Include Tara library
#include "../engine/core/lowlevel.h"
#include "../engine/core/window/ewindow.h"
#include "../engine/core/renderer/renderer.h"
#include "../engine/core/scene_object/scene_object.h"
#include "../engine/core/event.h"
#include "../engine/core/utility.h"
#include "../engine/component/camera.h"
#include "editor_setting.h"

namespace Tara {
	namespace UI {
		std::vector<ImGui_WindowBase*> m_guiWindows = std::vector<ImGui_WindowBase*>();
		int32_t gizmoPipeline, guiPipeline, postGUIPipeline;
		ImGuiContext* ctx = nullptr;

		void Init()
		{
			Tara::EWindow* wptr = Tara::CurrentWindow();
			GLFWwindow* w = (GLFWwindow*)wptr->WindowPtr();
			if (!w) {
				TARA_RUNTIME_ERROR("ImGui failed to initialization.");
				return;
			}
			TARA_DEBUG("%s: %s", "Imgui gui version", ImGui::GetVersion());
			IMGUI_CHECKVERSION();
			ctx = ImGui::CreateContext();
			ImGui::SetCurrentContext(ctx);
			ImGuiIO& io = ImGui::GetIO(); (void)io;

			//io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
			//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
			io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;     // Enable Keyboard Controls
			//io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;   // Enable Gamepad Controls
			//io.ConfigViewportsNoAutoMerge = true;
			//io.ConfigViewportsNoTaskBarIcon = true;

			// Setup Platform/Renderer backends
			ImGui_ImplGlfw_InitForOpenGL(w, true);
			ImGui_ImplOpenGL3_Init(wptr->GetGLSLVersion().c_str());

			// Load Fonts
			// - If no fonts are loaded, dear imgui will use the default font. You can also load multiple fonts and use ImGui::PushFont()/PopFont() to select them.
			// - AddFontFromFileTTF() will return the ImFont* so you can store it if you need to select the font among multiple.
			// - If the file cannot be loaded, the function will return NULL. Please handle those errors in your application (e.g. use an assertion, or display an error and quit).
			// - The fonts will be rasterized at a given size (w/ oversampling) and stored into a texture when calling ImFontAtlas::Build()/GetTexDataAsXXXX(), which ImGui_ImplXXXX_NewFrame below will call.
			// - Read 'docs/FONTS.md' for more instructions and details.
			// - Remember that in C/C++ if you want to include a backslash \ in a string literal you need to write a double backslash \\ !
			//io.Fonts->AddFontDefault();
			ImGui_InitFont();
			//io.Fonts->AddFontFromFileTTF("../../misc/fonts/Cousine-Regular.ttf", 15.0f);
			//io.Fonts->AddFontFromFileTTF("../../misc/fonts/DroidSans.ttf", 16.0f);
			//io.Fonts->AddFontFromFileTTF("../../misc/fonts/ProggyTiny.ttf", 10.0f);
			//ImFont* font = io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\ArialUni.ttf", 18.0f, NULL, io.Fonts->GetGlyphRangesJapanese());
			//IM_ASSERT(font != NULL);

			// Setup Dear ImGui style
			EditorStyle& es = EditorStyle::Singleton();
			es.LoadInstance();
			if (!Utility::File::Exist(EDITOR_STYLE_FILE)) {
				ImGui_SetTaraTheme();
				es.Apply();
				es.Save(EDITOR_STYLE_FILE);
			}
			else {
				if (!es.Load(EDITOR_STYLE_FILE)) {
					ImGui_SetTaraTheme();
					es.Save(EDITOR_STYLE_FILE);
				}
				es.Apply();
			}

			if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
			{
				es.vars.WindowRounding = 0.0f;
				es.colors.m_WindowBg.w = 1.0f;
				es.ApplyVar();
			}

			ImGui_NotifyInit();
		}

		void ShutdownGUI() {
			TARA_DEBUG("Shutdown ImGui context");
			ImGui_ImplOpenGL3_Shutdown();
			ImGui_ImplGlfw_Shutdown();
			if (ctx != nullptr) delete ctx;
			ImGui::SetCurrentContext(NULL);
		}

		void NewFrame() {
			ImGui_ImplOpenGL3_NewFrame();
			ImGui_ImplGlfw_NewFrame();
			ImGui::NewFrame();
		}

		void Render() {
			ImGui::Render();
			glm::ivec2 fsize = LowLevel::FramebufferSize();
			
			LowLevel::Viewport(fsize.x, fsize.y);
			
			ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

			ImGuiIO& io = ImGui::GetIO(); (void)io;
			if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
			{
				void* backup_current_context = LowLevel::GetWindowConext();
				ImGui::UpdatePlatformWindows();
				ImGui::RenderPlatformWindowsDefault();
				LowLevel::SetWindowConext(backup_current_context);
			}
		}

		void Gizmo() {
			Renderer& renderer = Renderer::Singleton();
			CameraComponent& camera = renderer.MainCamera();

			camera.Use();
			LowLevel::WireframeMode(true);
			LowLevel::DepthTest(true);

			camera.Unuse();
			LowLevel::WireframeMode(false);
			LowLevel::DepthTest(false);
		}

		void GUI() {
			NewFrame();
			ImGui_DockspaceOverviewport();
		}

		void PostGUI() {
			int c = 0;
			for (auto it = m_guiWindows.begin(); it != m_guiWindows.end(); it++) {
				if (!(*it)) continue;
				(*it)->Render();
				c++;
			}
			ImGui_RenderNotifycation();
			Render();
		}

		void Tara_GUI_Initialization()
		{
			m_guiWindows = std::vector<ImGui_WindowBase*>();
			EWindow* w = CurrentWindow();

			w->WindowStartEvent.Add(&Init);
			w->ShutdownEvent.Add(&ShutdownGUI);
			gizmoPipeline = w->PipelineEvent.Add(-1500, Gizmo);
			guiPipeline = w->PipelineEvent.Add(-905, GUI);
			postGUIPipeline = w->PipelineEvent.Add(-900, PostGUI);

			TaraEvent& tara = TaraEvent::Singleton();
			EditorComponentManager& ecomp = EditorComponentManager::Singleton();

			tara.SceneObjectCreateEvent.Add(std::bind(&EditorComponentManager::NewEObjectCreate, ecomp, std::placeholders::_1));
			tara.SceneObjectDestroyEvent.Add(std::bind(&EditorComponentManager::NewEObjectDestroy, ecomp, std::placeholders::_1));
			
			tara.ComponentCreateEvent.Add(std::bind(&EditorComponentManager::NewEComponentCreate, ecomp, std::placeholders::_1));
			tara.ComponentDestroyEvent.Add(std::bind(&EditorComponentManager::NewEComponentDestroy, ecomp, std::placeholders::_1));
			TARA_DEBUG("ImGui Initialized");
		}

		void Tara_GUI_Shutdown()
		{
			CleanGUIWindow();
			EWindow* w = CurrentWindow();
			w->PipelineEvent.Remove(gizmoPipeline);
			w->PipelineEvent.Remove(guiPipeline);
			w->PipelineEvent.Remove(postGUIPipeline);
		}

		void AddGUIWindow(ImGui_WindowBase* window)
		{
			m_guiWindows.push_back(window);
		}

		void RemoveGUIWindow(ImGui_WindowBase* window)
		{
			std::remove(m_guiWindows.begin(), m_guiWindows.end(), window);
			delete window;
		}

		void CleanGUIWindow()
		{
			size_t size = m_guiWindows.size();
			for (int i = 0; i < size; i++) {
				RemoveGUIWindow(m_guiWindows[0]);
			}
		}
	}
}