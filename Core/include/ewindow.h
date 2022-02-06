#pragma once
// Include std library
#include <vector>
#include <map>

// Include third party library
#include <glm/glm.hpp>

// Include tara library
#include "config.h"
#include <scene.h>
#include <gui.h>

namespace Tara {
	/*

		Structs, classes declaration

	*/
	struct DllExport EWindowConfig;
	class DllExport EWindow;

	/*
		Summary:
			Select GL version, and you can check the GLSL version in their description,
			first 3 bit means major version,
			last 3 bit means minor version,
			Then it use map in cpp file to get GLSL version string.
	*/
	DllExport enum class OpenGLVersion {
		Version2_0 = 16, // 010-000 -> #version 110
		Version3_0 = 24, // 011-000 -> #version 130
		Version3_1 = 25, // 011-001 -> #version 140
		Version3_2 = 26, // 011-010 -> #version 150
		Version3_3 = 27, // 011-011 -> #version 330
		Version4_0 = 32, // 100-000 -> #version 400
		Version4_1 = 33, // 100-001 -> #version 410
		Version4_2 = 34, // 100-010 -> #version 420
		Version4_3 = 35, // 100-011 -> #version 430
		Version4_4 = 36, // 100-100 -> #version 440
		Version4_5 = 37, // 100-101 -> #version 450
		Version4_6 = 38  // 100-110 -> #version 460
	};

	/*
		Summary:
			Initialize the resources and stuff.
	*/
	DllExport void Tara_Initialization();
	DllExport EWindow* CurrentWindow();
	DllExport bool IsCurrentWindowIconify();

	/*
		Summary:
			Ewindow flags
			The struct organize glfw flags into a struct like object
	*/
	struct EWindowConfig
	{
	public:
		EWindowConfig();
		bool Resizable = true;
		bool Visible = true;
		bool Decorated = true;
		bool Focused = true;
		bool AutoIconify = true;
		bool Floating = false;
		bool Maximized = false;
		bool CenterCursor = true;
		bool TransparentFramebuffer = false;
		bool FocusOnShow = true;
		bool ScaleToMonitor = false;
		bool Vsync = true;
		bool Center = true;
		glm::ivec2 WindowPos = glm::ivec2();
		glm::ivec2 MinimumSize = glm::ivec2();
		glm::ivec2 MaximumSize = glm::ivec2();
		glm::ivec2 AspectRatio = glm::ivec2();

		/*
			Summary:
				Print the current flags out
		*/
		void Print();
		/*
			Summary:
				Check if it's needs to use glfwSetWindowSizeLimits function
				By looking if both minimum_size and maximum_size are zero
		*/
		bool HaveLimit();
		/*
			Summary:
				Check if minimum_size is zero
		*/
		bool HaveMinLimit();
		/*
			Summary:
				Check if maximum_size is zero
		*/
		bool HaveMaxLimit();
		/*
			Summary:
				Check if it's needs to use glfwSetWindowAspectRatio function
				By looking if aspect_ratio is zero
		*/
		bool HaveAspectRatio();
	};

	/*
		Summary:
			Window object
			The window base class, contain basic features such as
			gui drawing, events register, update function, show/hide function
	*/
	class EWindow
	{
	public:
		/*
			Summary:
				Create tara window instance.
		*/
		EWindow(int32_t width = 800, int32_t height = 600, const char* name = "Tara Window", OpenGLVersion version = OpenGLVersion::Version4_5, EWindowConfig config = EWindowConfig());
		~EWindow();

		/*
			Summary:
				After window constructor finish.
		*/
		virtual void Start();
		/*
			Summary:
				Register glfw window events.
		*/
		virtual void RegisterEvents();
		/*
			Summary:
				Enter window loop, it will run until glfwWindowShouldClose equal to True.
		*/
		virtual void Mainloop();
		/*
			Summary:
				Enter window rendering, called every frame before gui and update called.
		*/
		virtual void Render();
		/*
			Summary:
				gui new frame method, called every frame.
		*/
		virtual void GUI();
		/*
			Summary:
				gui render method, called every frame.
		*/
		virtual void PostGUI();
		/*
			Summary:
				Update method, called every frame.
		*/
		virtual void Update();
		/*
			Summary:
				After gui and render methods called, usually handles post processing stage.
		*/
		virtual void PostRender();
		/*
			Summary:
				Set the visible flag to True.
		*/
		void Show();
		/*
			Summary:
				Set the visible flag to False.
		*/
		void Hide();
		/*
			Summary:
				Minimize window.
		*/
		void Iconify();
		/*
			Summary:
				Maximize window.
		*/
		void Maximum();
		/*
			Summary:
				Set close flag to true.
		*/
		void Close();

	protected:
		/*
			Summary:
				Apply the flags to glfw window.
				Flags that does not require window instance.
		*/
		void ApplyWindowFlags(EWindowConfig config);
		/*
			Summary:
				Apply the flags to glfw window,
				Flags that does require window instance.
		*/
		void UpdateWindowFlags(EWindowConfig config);
		void Resize(int width, int height);
		void Rename(const char* name);
		void CleanBuffer();
		void CleanColor(const glm::vec4 c = glm::vec4(0, 0, 0, 1));
		void CleanColor(float_t r = 0, float_t g = 0, float_t b = 0, float_t a = 1);
		void Viewport(int32_t x, int32_t y, size_t w, size_t h);
		void Swap();
		void SetActiveScene(Scene* target);

	public:
		glm::ivec2 GetEWindowPos();
		glm::ivec2 GetEWindowSize();

	protected:
		std::vector<Scene*> m_scenes = std::vector<Scene*>();
		int32_t m_main_scene = 0;
		CCamera* m_camera;
		bool updateScenes = true;
		bool renderScenes = true;

	#pragma region UI::ImGui include condition
	#ifndef TARA_NO_ImGui
		std::vector<UI::ImGui_WindowBase*> m_guiWindows = std::vector<UI::ImGui_WindowBase*>();
	#endif
	private:

		void ImGuiStart(const char* version, void* window) {
	#ifndef TARA_NO_ImGui
			UI::ImGui_Initialization(version, window);
	#endif
		}
		void ImGuiViewport(ImGui_ChangeViewport callback) {
	#ifndef TARA_NO_ImGui
			UI::ImGui_ViewportCallback(callback);
	#endif
		}
		void ImGuiDestroy() {
	#ifndef TARA_NO_ImGui
			UI::ImGui_Destroy();
	#endif
		}
		void ImGuiGUI()
		{
#ifndef TARA_NO_ImGui
			UI::ImGui_NewFrame();
#endif
		}
		void ImGuiPostGUI(void* window)
		{
	#ifndef TARA_NO_ImGui
			for (auto it = m_guiWindows.begin(); it != m_guiWindows.end(); it++) {
				(*it)->Start();
				(*it)->Render();
			}
			UI::ImGui_Render(window);
	#endif
		}
	#pragma endregion

		// Screen render shader
		Material* m_postprocessShader;
		// Screen render quad
		Mesh* m_screenQuad;
		// Opengl version major
		int32_t m_major;
		// Opengl version minor
		int32_t m_minor;
	};
}