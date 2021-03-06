#pragma once
// Include std library
#include <vector>
#include <map>
#include <functional>

// Include third party library
#include <glm/glm.hpp>

// Include tara library
#include "../config.h"
#include "../event.h"

namespace Tara {
	/*
		Structures and classes
	*/
	class TARA_API EWindow;
	class TARA_API Scene;
	class TARA_API CameraComponent;
	struct TARA_API RenderState;

	/*
		Summary:
			Select GL version, and you can check the GLSL version in their description,
			first 3 bit means major version,
			last 3 bit means minor version,
			Then it use map in cpp file to get GLSL version string.
	*/
	enum class TARA_API OpenGLVersion {
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
			Get current use tara window
	*/
	TARA_API EWindow* CurrentWindow();


	/*
		Summary:
			Ewindow flags
			The struct organize glfw flags into a struct like object
	*/
	struct TARA_API EWindowConfig {
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
			Window object.
			The window base class, contain basic features such as,
			gui drawing, events register, update function, show/hide function.
	*/
	class TARA_API EWindow {
	public:
		/*
			Summary:
				Create tara window instance.
		*/
		EWindow(int32_t width = 800, int32_t height = 600, const char* name = "Tara Window", OpenGLVersion version = OpenGLVersion::Version4_5, EWindowConfig config = EWindowConfig());
		virtual ~EWindow();

		void Run();
		void* WindowPtr();
		std::pair<int, int> GetOpenGLVersion();
		std::string GetGLSLVersion();

		EventBase<std::function<void()>> WindowStartEvent = EventBase<std::function<void()>>();
		EventBase<std::function<void()>> ShutdownEvent = EventBase<std::function<void()>>();
		EventBase<std::function<void()>> RenderEvent = EventBase<std::function<void()>>();
		EventBase<std::function<void()>> PostRenderEvent = EventBase<std::function<void()>>();
		EventBase<std::function<void()>> UpdateEvent = EventBase<std::function<void()>>();
		EventBase<std::function<void()>> PipelineEvent = EventBase<std::function<void()>>();

	public:
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
		/*
			Summary:
				Resize the window.
		*/
		void Resize(int width, int height);
		/*
			Summary:
				Rename the window title.
		*/
		void Rename(const char* name);
		/*
			Summary:
				Clean color, depth, stencil buffers
		*/
		void CleanBuffer();
		/*
			Summary:
				Clean color buffer with color,
		*/
		void CleanColor(const glm::vec4 c = glm::vec4(0, 0, 0, 1));
		/*
			Summary:
				Clean color buffer with color,
		*/
		void CleanColor(float_t r = 0, float_t g = 0, float_t b = 0, float_t a = 1);
		/*
			Summary:
				Change viewport rect.
		*/
		void Viewport(int32_t x, int32_t y, size_t w, size_t h);
		/*
			Summary:
				Swap buffer.
		*/
		void Swap();
		/*
			Summary:
				Set active scene.
		*/
		void SetActiveScene(Scene* target);

	public:
		/*
			Summary:
				Get window position on screen.
		*/
		glm::ivec2 GetEWindowPos();
		/*
			Summary:
				Get window size.
		*/
		glm::ivec2 GetEWindowSize();
		/*
			Summary:
				Render state.
		*/
		RenderState& GetRenderState();

	protected:
		// Scenes current loaded.
		std::vector<Scene*> m_scenes = std::vector<Scene*>();
		// Use camera, They will render in render stage.
		std::vector<CameraComponent*> m_renderCamera = std::vector<CameraComponent*>();
		// Primary scene.
		int32_t m_main_scene = 0;
		// Decide that update scene or not.
		bool updateScenes = true;
		// Decide that render scene or not.
		bool renderScenes = true;
		// Decide that if application will collect render profiler.
		bool renderState = true;
		// Draw wireframe of objects on screen.
		bool wireframe = false;
		// Draw normally of objects on screen.
		bool shaded = true;
		// How many frame pass will cause garbage collect start.
		int32_t m_garbageCleanPassFrameCount = 20;
	private:
		/*
			Summary:
				Check if garbage collection should happend or not.
		*/
		void CheckCleanGarbage();

		// Opengl version major.
		int32_t m_major;
		// Opengl version minor.
		int32_t m_minor;
		// Frame count
		int32_t m_frameCount;
		// Count down of garbage collection, when it smaller than 1, garbage collection will happen.
		int32_t m_garbageCleanCountDown = 0;
	};
}