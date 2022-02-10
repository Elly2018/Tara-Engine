// Include std library
#include "EWindow.h"
#include <list>
#include <map>
#include <filesystem>

// Include third party library
#include <glad/glad.h>
#include <GLFW/glfw3.h>

// Include tara library
#include <renderer.h>
#include <shader.h>
#include <texture.h>
#include <einput.h>

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
#include <Windows.h>
#define TARA_WINDOW
#endif
#if __linux__
#include "stdlib.h"
#include "stdio.h"
#include "string.h"
#include "sys/times.h"
#include "sys/vtimes.h"
#define TARA_LINUX
#endif

namespace Tara {
	#pragma region Global variables
	const std::map<std::pair<int, int>, const char*> GLSLVersionMap = {
		{std::pair<int, int>(2, 0), "#version 110"},
		{std::pair<int, int>(3, 0), "#version 130"},
		{std::pair<int, int>(3, 1), "#version 140"},
		{std::pair<int, int>(3, 2), "#version 150"},
		{std::pair<int, int>(3, 3), "#version 330"},
		{std::pair<int, int>(4, 0), "#version 400"},
		{std::pair<int, int>(4, 1), "#version 410"},
		{std::pair<int, int>(4, 2), "#version 420"},
		{std::pair<int, int>(4, 3), "#version 430"},
		{std::pair<int, int>(4, 4), "#version 440"},
		{std::pair<int, int>(4, 5), "#version 450"},
		{std::pair<int, int>(4, 6), "#version 460"},
	};
	const std::map<OpenGLVersion, std::string> GLSLVersion = {
		{OpenGLVersion::Version2_0, "#version 110"},
		{OpenGLVersion::Version3_0, "#version 130"},
		{OpenGLVersion::Version3_1, "#version 140"},
		{OpenGLVersion::Version3_2, "#version 150"},
		{OpenGLVersion::Version3_3, "#version 330"},
		{OpenGLVersion::Version4_0, "#version 400"},
		{OpenGLVersion::Version4_1, "#version 410"},
		{OpenGLVersion::Version4_2, "#version 420"},
		{OpenGLVersion::Version4_3, "#version 430"},
		{OpenGLVersion::Version4_4, "#version 440"},
		{OpenGLVersion::Version4_5, "#version 450"},
		{OpenGLVersion::Version4_6, "#version 460"},
	};
	GLFWwindow* window;
	EWindow* current;
	#pragma endregion

	#pragma region Local Functionality
	#ifdef TARA_WINDOW
	static ULARGE_INTEGER lastCPU, lastSysCPU, lastUserCPU;
	static int numProcessors;
	static HANDLE self;
	void ProfilerInit() {
		SYSTEM_INFO sysInfo;
		FILETIME ftime, fsys, fuser;

		GetSystemInfo(&sysInfo);
		numProcessors = sysInfo.dwNumberOfProcessors;

		GetSystemTimeAsFileTime(&ftime);
		memcpy(&lastCPU, &ftime, sizeof(FILETIME));

		self = GetCurrentProcess();
		GetProcessTimes(self, &ftime, &ftime, &fsys, &fuser);
		memcpy(&lastSysCPU, &fsys, sizeof(FILETIME));
		memcpy(&lastUserCPU, &fuser, sizeof(FILETIME));
	}

	double GetCurrentValue() {
		FILETIME ftime, fsys, fuser;
		ULARGE_INTEGER now, sys, user;
		double percent;

		GetSystemTimeAsFileTime(&ftime);
		memcpy(&now, &ftime, sizeof(FILETIME));

		GetProcessTimes(self, &ftime, &ftime, &fsys, &fuser);
		memcpy(&sys, &fsys, sizeof(FILETIME));
		memcpy(&user, &fuser, sizeof(FILETIME));
		percent = (sys.QuadPart - lastSysCPU.QuadPart) +
			(user.QuadPart - lastUserCPU.QuadPart);
		percent /= (now.QuadPart - lastCPU.QuadPart);
		percent /= numProcessors;
		lastCPU = now;
		lastUserCPU = user;
		lastSysCPU = sys;

		return percent * 100.0;
	}
	#endif
	#if TARA_LINUX
	clock_t lastCPU, lastSysCPU, lastUserCPU;
	int numProcessors;
	void ProfilerInit() {
		FILE* file;
		struct tms timeSample;
		char line[128];

		lastCPU = times(&timeSample);
		lastSysCPU = timeSample.tms_stime;
		lastUserCPU = timeSample.tms_utime;

		file = fopen("/proc/cpuinfo", "r");
		numProcessors = 0;
		while (fgets(line, 128, file) != NULL) {
			if (strncmp(line, "processor", 9) == 0) numProcessors++;
		}
		fclose(file);
	}

	double GetCurrentValue() {
		struct tms timeSample;
		clock_t now;
		double percent;

		now = times(&timeSample);
		if (now <= lastCPU || timeSample.tms_stime < lastSysCPU ||
			timeSample.tms_utime < lastUserCPU) {
			//Overflow detection. Just skip this value.
			percent = -1.0;
		}
		else {
			percent = (timeSample.tms_stime - lastSysCPU) +
				(timeSample.tms_utime - lastUserCPU);
			percent /= (now - lastCPU);
			percent /= numProcessors;
			percent *= 100;
		}
		lastCPU = now;
		lastSysCPU = timeSample.tms_stime;
		lastUserCPU = timeSample.tms_utime;

		return percent;
	}
	#endif // TARA_WINDOW
	#pragma endregion

	#pragma region Global Functions
	void Tara_Initialization()
	{
		TARA_DEBUG_LEVEL("Tara initialization start", 2);
		TARA_DEBUG("Debug level: %i", DEBUG_LEVEL);
		TARA_DEBUG("Debug filename: %s", DEBUG_FILENAME);
#ifdef TARA_WINDOW || TARA_LINUX
		ProfilerInit();
#endif
		CreateDefaultShaders();
		CreateDefaultTextures();
		CreateDefaultMeshes();
		Renderer::pureColor = new Material(*Shader::GetCommon(CommonShader::Color));
		Renderer::pureColor->SetVec3("color", glm::vec3(1, 0, 0));
		TARA_DEBUG_LEVEL("Tara initialization end", 2);
	}
	EWindow* CurrentWindow()
	{
		return current;
	}
	bool IsCurrentWindowIconify() {
		return glfwGetWindowAttrib(window, GLFW_ICONIFIED);
	}
	#pragma endregion

	#pragma region EWindow Config
	EWindowConfig::EWindowConfig()
	{
		MinimumSize = glm::ivec2(800, 600);
		MaximumSize = glm::ivec2(0, 0); // Don't care
		AspectRatio = glm::ivec2(0, 0); // Won't apply
		WindowPos = glm::ivec2(100, 100);
	}
	void EWindowConfig::Print()
	{
		TARA_DEBUG_LEVEL("\tGLFW_RESIZABLE: %s", 2, Resizable ? "GLFW_TRUE" : "GLFW_FALSE");
		TARA_DEBUG_LEVEL("\tGLFW_VISIBLE: %s", 2, Visible ? "GLFW_TRUE" : "GLFW_FALSE");
		TARA_DEBUG_LEVEL("\tGLFW_DECORATED: %s", 2, Decorated ? "GLFW_TRUE" : "GLFW_FALSE");
		TARA_DEBUG_LEVEL("\tGLFW_FOCUSED: %s", 2, Focused ? "GLFW_TRUE" : "GLFW_FALSE");
		TARA_DEBUG_LEVEL("\tGLFW_AUTO_ICONIFY: %s", 2, AutoIconify ? "GLFW_TRUE" : "GLFW_FALSE");
		TARA_DEBUG_LEVEL("\tGLFW_FLOATING: %s", 2, Floating ? "GLFW_TRUE" : "GLFW_FALSE");
		TARA_DEBUG_LEVEL("\tGLFW_MAXIMIZED: %s", 2, Maximized ? "GLFW_TRUE" : "GLFW_FALSE");
		TARA_DEBUG_LEVEL("\tGLFW_CENTER_CURSOR: %s", 2, CenterCursor ? "GLFW_TRUE" : "GLFW_FALSE");
		TARA_DEBUG_LEVEL("\tGLFW_TRANSPARENT_FRAMEBUFFER: %s", 2, TransparentFramebuffer ? "GLFW_TRUE" : "GLFW_FALSE");
		TARA_DEBUG_LEVEL("\tGLFW_FOCUS_ON_SHOW: %s", 2, FocusOnShow ? "GLFW_TRUE" : "GLFW_FALSE");
		TARA_DEBUG_LEVEL("\tGLFW_SCALE_TO_MONITOR: %s", 2, ScaleToMonitor ? "GLFW_TRUE" : "GLFW_FALSE");
		TARA_DEBUG_LEVEL("\tglfwSetWindowPos: %ix%i", 2, WindowPos.x, WindowPos.y);
		TARA_DEBUG_LEVEL("\thave_limit: %s", 2, HaveLimit() ? "True" : "False");
		TARA_DEBUG_LEVEL("\t\tminimum_size: %ix%i, have: %s", 2, MinimumSize.x, MinimumSize.y, HaveMinLimit() ? "TRUE" : "FALSE");
		TARA_DEBUG_LEVEL("\t\tmaximum_size: %ix%i, have: %s", 2, MaximumSize.x, MaximumSize.y, HaveMaxLimit() ? "TRUE" : "FALSE");
		TARA_DEBUG_LEVEL("\thave_aspect_ratio: %s", 2, HaveAspectRatio() ? "True" : "False");
		TARA_DEBUG_LEVEL("\t\taspect_ratio: %ix%i", 2, AspectRatio.x, AspectRatio.y);
	}
	bool EWindowConfig::HaveLimit()
	{
		return HaveMinLimit() || HaveMaxLimit();
	}
	bool EWindowConfig::HaveMinLimit()
	{
		return !(MinimumSize.x == 0 && MinimumSize.y == 0);
	}
	bool EWindowConfig::HaveMaxLimit()
	{
		return !(MaximumSize.x == 0 && MaximumSize.y == 0);
	}
	bool EWindowConfig::HaveAspectRatio()
	{
		return !(AspectRatio.x == 0 && AspectRatio.y == 0);
	}
	#pragma endregion

	#pragma region EWindow
	EWindow::EWindow(int32_t width, int32_t height, const char* name, OpenGLVersion version, EWindowConfig config) {
		Logger::LogToFile();
		std::filesystem::create_directory("temp");

		if (glfwInit() != GLFW_TRUE) {
			TARA_RUNTIME_ERROR("GLFW failed to initialize");
		}

		m_major = (((int)version & 56) >> 3); // (version & 111000) then >> 3
		m_minor = ((int)version & 7); // (version % 000111)

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, m_major);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, m_minor);
		// For some reason the first line of debug message
		// Won't output from 'Logger::GetApplicationLog()'
		// So we print a dummy message first then
		TARA_DEBUG();
		TARA_DEBUG_LEVEL("GLFW version: %i.%i", 4, m_major, m_minor);
		TARA_DEBUG_LEVEL("GLSL version: %s", 4, GLSLVersion.at(version).c_str());

	#ifdef __APPLE__
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	#endif

		config.Print();
		window = glfwCreateWindow(width, height, name, NULL, NULL);
		TARA_DEBUG_LEVEL("Window created", 4);
		if (!window)
		{
			glfwTerminate();
			TARA_RUNTIME_ERROR("GLFW failed to create window");
		}
		UpdateWindowFlags(config);
		ApplyWindowFlags(config);

		glfwMakeContextCurrent(window);
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
			glfwTerminate();
			TARA_RUNTIME_ERROR("GLAD failed to initialize");
		}
		TARA_DEBUG_LEVEL("Glad initialized", 4);
		glfwSwapInterval(config.Vsync ? 1 : 0);
		current = this;
		Logger::Flush();
	}
	EWindow::~EWindow()
	{
		CleanGarbage();
		TARA_DEBUG_LEVEL("Texture asset size: %i", 1, Texture::GetAssetPool()->Size());
		Texture::GetAssetPool()->DeleteAll();
		TARA_DEBUG_LEVEL("Shader asset size: %i", 1, Shader::GetAssetPool()->Size());
		Shader::GetAssetPool()->DeleteAll();
		TARA_DEBUG_LEVEL("Mesh asset size: %i", 1, Mesh::GetAssetPool()->Size());
		Mesh::GetAssetPool()->DeleteAll();
		TARA_DEBUG_LEVEL("Framebuffer asset size: %i", 1, FrameBuffer::GetAssetPool()->Size());
		FrameBuffer::GetAssetPool()->DeleteAll();
		Logger::Flush();
#ifndef TARA_NO_IMGUI
		UI::ImGui_Destroy();
#endif
		Logger::Flush();
		TARA_DEBUG("Delete glfw window");
		glfwDestroyWindow(window);
		Logger::Flush();
		TARA_DEBUG("Delete glfw terminate");
		glfwTerminate();
		Logger::Flush();
		current = nullptr;
		Logger::Flush();
	}

	void EWindow::Start() {
#ifndef TARA_NO_IMGUI
		UI::ImGui_Initialization(GLSLVersionMap.at(std::pair<int, int>(m_major, m_major)), (void*)window);
#endif
		RegisterEvents();
		m_postprocessShader = new Material(*Shader::GetCommon(CommonShader::DefaultPostprocess));
		m_screenQuad = Mesh::GetCommon(CommomMesh::Quad);
	}
	void EWindow::RegisterEvents()
	{
		TARA_DEBUG("Register events...");
		GLFWkeyfun f1 = [](GLFWwindow* window, int key, int scancode, int action, int mods) -> void { EInput::KeyInput(key, scancode, action, mods); };
		GLFWscrollfun f2 = [](GLFWwindow * window, double xoffset, double yoffset) -> void { EInput::ScrollInput(xoffset, yoffset); };
		GLFWmousebuttonfun f3 = [](GLFWwindow* window, int button, int action, int mods) -> void { EInput::MouseButtonInput(button, action, mods); };
		GLFWcursorposfun f4 = [](GLFWwindow* window, double xpos, double ypos) -> void { EInput::PosInput(xpos, ypos); };
		GLFWcharfun f5 = [](GLFWwindow* window, unsigned int codepoint) -> void { EInput::CharInput(codepoint); };
		GLFWframebuffersizefun f6 = [](GLFWwindow* window, int width, int height) -> void { glViewport(0, 0, width, height); };
		ImGui_ChangeViewport f7 = [](int x, int y, int width, int height) -> void { glViewport(x, y, width, height); };
		glfwSetKeyCallback(window, f1);
		glfwSetScrollCallback(window, f2);
		glfwSetMouseButtonCallback(window, f3);
		glfwSetCursorPosCallback(window, f4);
		glfwSetCharCallback(window, f5);
		glfwSetFramebufferSizeCallback(window, f6);
		glfwSetWindowSizeCallback(window, f6);
#ifndef TARA_NO_IMGUI
		UI::ImGui_ViewportCallback(f7);
#endif
		TARA_DEBUG("Register events finished");
	}
	void EWindow::Mainloop()
	{
		while (!glfwWindowShouldClose(window))
		{
			CCamera& maincamera = Renderer::MainCamera();

			float_t m_cpu = Renderer::m_RenderState.CPU_Usage;
			Renderer::m_RenderState = RenderState();
			if (renderScenes) Renderer::m_RenderState.CPU_Usage = m_cpu;
			else Renderer::m_RenderState.CPU_Usage = 0;

			bool ogState = Renderer::m_renderRecord;
			// Update glfw events, receive callback functions
			glfwPollEvents();
			// Render 2D/3D scene
			Render();
			{
				Renderer::m_renderRecord = false;
				maincamera.Use();
				glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
				glEnable(GL_DEPTH_TEST);
			}
			Gizmo();
			{
				Renderer::m_renderRecord = ogState;
				maincamera.Unuse();
				glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
				glDisable(GL_DEPTH_TEST);
			}
			// Post processing
			PostRender();
			// Gui new frame
			GUI();
			// Gui drawing
			PostGUI();
			// Event updating
			Update();
			// Frame swap
			Swap();
			// Update input state
			EInput::Update(glfwGetTime());
			Logger::Flush();
		}
		TARA_DEBUG("Application exit !");
		Logger::Flush();
	}
	void EWindow::Render() {
		if (m_scenes.size() == 0 || !renderScenes) return;

		Renderer::MainCamera().Render();
		Renderer::wireframeMode = wireframe;
		Renderer::shadedMode = shaded;
		Renderer::m_renderRecord = renderState;

		std::vector<CCamera*> useCam = std::vector<CCamera*>(m_renderCamera);
		useCam.push_back(&Renderer::MainCamera());

		for (auto maincamera : useCam) {
			if (!maincamera) continue;
			maincamera->Use();
			glm::ivec2 wsize = GetEWindowSize();
			Viewport(0, 0, wsize.x, wsize.y);
			CleanBuffer();

			glEnable(GL_DEPTH_TEST);
			glEnable(GL_CULL_FACE);
			glCullFace(GL_FRONT_AND_BACK);
			glFrontFace(GL_CCW);
			glLineWidth(5);
			// Apply camera view, projection matrix
			Renderer::view = maincamera->ViewMatrix();
			Renderer::projection = maincamera->ProjectionMatrix();
			Renderer::CameraFrustum() = maincamera->GetFrustum();
			for (Scene* s : m_scenes) {
				s->Render();
			}
			glDisable(GL_CULL_FACE);
			glDisable(GL_DEPTH_TEST);
			maincamera->Blit();
			maincamera->Unuse();
		}
	}
	void EWindow::Gizmo() {
		if (m_scenes.size() == 0 || !renderScenes) return;
		for (Scene* s : m_scenes) {
			s->Gizmo();
		}
	}
	void EWindow::GUI()
	{
#ifndef TARA_NO_IMGUI
		UI::ImGui_NewFrame();
#endif
	}
	void EWindow::PostGUI()
	{
#ifndef TARA_NO_IMGUI
		for (auto it = m_guiWindows.begin(); it != m_guiWindows.end(); it++) {
			(*it)->Start();
			(*it)->Render();
		}
		UI::ImGui_Render(window);
#endif
	}
	void EWindow::Update() {
		if (m_scenes.size() == 0 || !updateScenes) return;
		Renderer::MainCamera().Update();
		for (Scene* i : m_scenes) {
			i->Update();
		}
		m_frameCount++;

		if (renderState) {
			Renderer::m_RenderState.FPS = 1.0 / EInput::Delta();
#ifdef TARA_WINDOW || TARA_LINUX
			double m_cpu = GetCurrentValue();
			Renderer::m_RenderState.CPU_Usage = m_cpu == 0.0 ? Renderer::m_RenderState.CPU_Usage : m_cpu;
#endif // TARA_WINDOW
		}

	}
	void EWindow::PostRender()
	{
		CCamera& maincamera = Renderer::MainCamera();
		if (m_scenes.size() == 0 || !updateScenes  || !m_screenQuad || !m_postprocessShader) return;
		CleanBuffer();
		m_postprocessShader->Use();
		m_postprocessShader->UniformVec2("screenSize", GetEWindowSize());
		glActiveTexture(GL_TEXTURE0);
		//Texture::GetCommon(CommomTexture::Grid)->Bind();
		maincamera.Bind();
		m_screenQuad->Draw();
		maincamera.Unbind();
	}
	void EWindow::Show()
	{
		glfwShowWindow(window);
	}
	void EWindow::Hide()
	{
		glfwHideWindow(window);
	}
	void EWindow::Iconify()
	{
		glfwIconifyWindow(window);
	}
	void EWindow::Maximum()
	{
		glfwMaximizeWindow(window);
	}
	void EWindow::Close()
	{
		glfwSetWindowShouldClose(window, true);
	}
	void EWindow::ApplyWindowFlags(EWindowConfig config)
	{
		glfwWindowHint(GLFW_RESIZABLE, config.Resizable ? GLFW_TRUE : GLFW_FALSE);
		glfwWindowHint(GLFW_VISIBLE, config.Visible ? GLFW_TRUE : GLFW_FALSE);
		glfwWindowHint(GLFW_DECORATED, config.Decorated ? GLFW_TRUE : GLFW_FALSE);
		glfwWindowHint(GLFW_FOCUSED, config.Focused ? GLFW_TRUE : GLFW_FALSE);
		glfwWindowHint(GLFW_AUTO_ICONIFY, config.AutoIconify ? GLFW_TRUE : GLFW_FALSE);
		glfwWindowHint(GLFW_FLOATING, config.Floating ? GLFW_TRUE : GLFW_FALSE);
		glfwWindowHint(GLFW_MAXIMIZED, config.Maximized ? GLFW_TRUE : GLFW_FALSE);
		glfwWindowHint(GLFW_CENTER_CURSOR, config.CenterCursor ? GLFW_TRUE : GLFW_FALSE);
		glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, config.TransparentFramebuffer ? GLFW_TRUE : GLFW_FALSE);
		glfwWindowHint(GLFW_FOCUS_ON_SHOW, config.FocusOnShow ? GLFW_TRUE : GLFW_FALSE);
		glfwWindowHint(GLFW_SCALE_TO_MONITOR, config.ScaleToMonitor ? GLFW_TRUE : GLFW_FALSE);
	}
	void EWindow::UpdateWindowFlags(EWindowConfig config)
	{
		if (config.Center) {
			// We want the default window position is at center of the screen
			// So get monitor, get video mode, calculate the position, DA LA 
			int window_width, window_height;
			glfwGetWindowSize(window, &window_width, &window_height);

			int monitors_length;
			GLFWmonitor* monitor = glfwGetPrimaryMonitor();

			if (monitor == NULL) {
				// Got no monitors back
				return;
			}
			const GLFWvidmode* mode = glfwGetVideoMode(monitor);

			glfwSetWindowPos(window, (mode->width - window_width) / 2, (mode->height - window_height) / 2);
		}
		else {
			glfwSetWindowPos(window, config.WindowPos.x, config.WindowPos.y);
		}
		if (config.HaveLimit()) {
			bool min_have = config.HaveMinLimit();
			bool max_have = config.HaveMaxLimit();
			glfwSetWindowSizeLimits(window,
				min_have ? config.MinimumSize.x : GLFW_DONT_CARE,
				min_have ? config.MinimumSize.y : GLFW_DONT_CARE,
				max_have ? config.MaximumSize.x : GLFW_DONT_CARE,
				max_have ? config.MaximumSize.y : GLFW_DONT_CARE
			);
		}
		if (config.HaveAspectRatio())
			glfwSetWindowAspectRatio(window, config.AspectRatio.x, config.AspectRatio.y);
	}
	void EWindow::Resize(int width, int height)
	{
		glfwSetWindowSize(window, width, height);
	}
	void EWindow::Rename(const char* name)
	{
		glfwSetWindowTitle(window, name);
	}
	void EWindow::CleanBuffer()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	}
	void EWindow::CleanColor(const glm::vec4 c)
	{
		glClearColor(c.r, c.g, c.b, c.a);
	}
	void EWindow::CleanColor(float_t r, float_t g, float_t b, float_t a)
	{
		glClearColor(r, g, b, a);
	}
	void EWindow::Viewport(int32_t x, int32_t y, size_t w, size_t h)
	{
		glViewport(x, y, w, h);
	}
	void EWindow::Swap()
	{
		glfwSwapBuffers(window);
	}
	void EWindow::SetActiveScene(Scene* target)
	{
		std::vector<Scene*>::iterator it = std::find(m_scenes.begin(), m_scenes.end(), target);
		if (it != m_scenes.end()) {
			m_main_scene = std::distance(m_scenes.begin(), it);
		}
		else {
			m_scenes.push_back(target);
			m_main_scene = m_scenes.size() - 1;
		}
	}

	glm::ivec2 EWindow::GetEWindowPos() {
		int w, h;
		glfwGetWindowPos(window, &w, &h);
		return glm::ivec2(w, h);
	}
	glm::ivec2 EWindow::GetEWindowSize() {
		int w, h;
		glfwGetWindowSize(window, &w, &h);
		return glm::ivec2(w, h);
	}
	RenderState& EWindow::GetRenderState()
	{
		return Renderer::m_RenderState;
	}
	void EWindow::CleanGarbage()
	{
		Texture::GetAssetPool()->CleanNull();
		Shader::GetAssetPool()->CleanNull();
		Mesh::GetAssetPool()->CleanNull();
		FrameBuffer::GetAssetPool()->CleanNull();
	}
	void EWindow::CheckCleanGarbage()
	{
		m_garbageCleanCountDown--;
		if (m_garbageCleanCountDown <= 0) {
			m_garbageCleanCountDown = m_garbageCleanPassFrameCount;
			CleanGarbage();
		}
	}
	#pragma endregion
};