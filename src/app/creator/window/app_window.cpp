#include "app_window.h"
#include "engine/tara.h"
#include "engine/core/shader/shader.h"
#include "engine/core/material/material.h"
#include "engine/core/renderer/renderer.h"
#include "engine/component/transformation.h"
#include "engine/component/camera.h"
#include "engine/component/light.h"
#include "engine/core/scene/scene.h"
#include "editor/editor_lowlevel.h"
#include "editor/editor_flags.h"
#include "editor/project/project.h"
#include "appcore/global_panels.h"
#include "appcore/global_states.h"
#include "engine/core/buildin/buildin_manager.h"
#include "project_creation_win.h"

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
	UI::ProjectCreationWindow* projectcreation = nullptr;

	EWindowConfig& GetAppWindowConfig() {
		EWindowConfig config = EWindowConfig();
		config.Vsync = false;
		return config;
	}

	AppWindow::AppWindow() : EWindow(800, 600, "Tara", OpenGLVersion::Version4_6, GetAppWindowConfig())
	{
		BuildinManager* bm = PackageManager::Singleton().buildin;
		ShaderLibrary& sl = ShaderLibrary::Singleton();
		if (!sl.SupportExtension()) {
			TARA_ERROR("Current version does not support glsl include extension!");
		}
		nlohmann::json& mani = bm->Manifest;
		nlohmann::json& shaderConfig = mani["shaderConfig"];
		nlohmann::json& loadCommomLibrary = shaderConfig["loadCommomLibrary"];
		nlohmann::json& loadCommomShaders = shaderConfig["loadCommomShaders"];

		if (shaderConfig.is_null()) {
			TARA_RUNTIME_ERROR("Buildin manifest does not contain shaderConfig");
		}
		if (loadCommomLibrary.is_null()) {
			TARA_RUNTIME_ERROR("Buildin manifest shaderConfig does not contain loadCommomLibrary");
		}
		if (shaderConfig.is_null()) {
			TARA_RUNTIME_ERROR("Buildin manifest shaderConfig does not contain loadCommomShaders");
		}
		

		// ! Loading commom shader library from buildin package, according manifest.json file.
		if (loadCommomLibrary.is_array()) {
			for (auto& i : loadCommomLibrary) {
				if (i.is_string()) {
					std::string shaderPath = i.get<std::string>();
					std::string shaderPath_wext = Utility::String::FormatString("%s%s", shaderPath.c_str(), ".glsl");
					sl.AddLibraryFromMemory(shaderPath_wext.c_str(), bm->GetShaderString(shaderPath.c_str(), ShaderType::Commom));
				}
			}
		}

		// ! Loading commom shaders from buildin package, according manifest.json file.
		if (loadCommomShaders.is_array()) {
			for (auto& i : loadCommomShaders) {
				nlohmann::json& jtype = i["type"];
				nlohmann::json& jname = i["name"];
				if (!jtype.is_number() || !jname.is_string()) continue;
				CommomMaterialType enum_type = (CommomMaterialType)jtype.get<int32_t>();
				std::string string_name = jname.get<std::string>();
				std::vector<std::string> filesp = bm->GetFiles(Utility::String::FormatString("shader/%s.*", string_name.c_str()));
				Shader* shader = bm->PackagingShader(string_name);
				if (!shader) continue;
				RegisterCommom(enum_type, shader);
			}
		}

		CommomMaterial().at(CommomMaterialType::Color)->SetVec3("ColorData.color", glm::vec3(1));
		PipelineEvent.Add(-904, std::bind(&AppWindow::GUI, this));
		Maximum();
		projectcreation = new UI::ProjectCreationWindow();
	}

	AppWindow::~AppWindow()
	{
	}

	void AppWindow::Start()
	{
		EWindow::Start();
		Scene* scene = new Scene();
		scene->Name = "Demo";

		Renderer& renderer = Renderer::Singleton();
		ObjectFactory& factory = ObjectFactory::Singleton();
		BuildinManager* bm = PackageManager::Singleton().buildin;
		GlobalPanels& pg = GlobalPanels::Singleton();
		UI::SceneViewerWindow* scenev = pg.GetPanel<UI::SceneViewerWindow>("Scene");

		Material* colorMat = new Material(*bm->PackagingShader("Color"));
		Material* lembertMat = new Material(*bm->PackagingShader("Lambert"));
		Material* blinnMat = new Material(*bm->PackagingShader("Blinn"));

		colorMat->SetVec3("ColorData.color", glm::vec3(1, 1, 1));
		lembertMat->SetVec2("TextureData.offset", glm::vec2(0));
		lembertMat->SetVec2("TextureData.scale", glm::vec2(1));
		lembertMat->SetVec3("TextureData.tint", glm::vec3(1));
		lembertMat->SetTexture2D("surface", bm->GetPrimitiveTexture("Default.png"));
		lembertMat->Config().Shaded = MaterialShadedMode::Lit;
		lembertMat->Apply();
		blinnMat->SetVec2("TextureData.offset", glm::vec2(0));
		blinnMat->SetVec2("TextureData.scale", glm::vec2(1));
		blinnMat->SetVec3("TextureData.tint", glm::vec3(1));
		blinnMat->SetTexture2D("surface", bm->GetPrimitiveTexture("Grid.png"));
		blinnMat->Config().Shaded = MaterialShadedMode::Lit;
		blinnMat->Apply();

		//factory.m_Viewer.CreateFreeCamera();
		SceneObject* cube = factory.m_3D.CreateMesh(bm->GetPrimitiveMesh("Sphere.obj"), blinnMat);
		TransformationComponent* cubetran = cube->GetRelateComponent<TransformationComponent>();

		SceneObject* cube2 = factory.m_3D.CreateMesh(bm->GetPrimitiveMesh("Cube.obj"), blinnMat);
		TransformationComponent* cubetran2 = cube2->GetRelateComponent<TransformationComponent>();

		SceneObject* light = factory.m_Lighting.CreateDirection();
		SceneObject* plight = factory.m_Lighting.CreatePointLight();
		TransformationComponent* lighttrans = light->GetRelateComponent<TransformationComponent>();
		TransformationComponent* plighttrans = plight->GetRelateComponent<TransformationComponent>();
		light->Name = "Light";
		plight->Name = "Point Light";

		LightComponent* lcomp = light->GetRelateComponent<LightComponent>();
		lcomp->m_color = glm::vec3(1);
		lcomp->m_intensity = 1.f;

		cubetran->LocalPosition() = glm::vec3(0, 1, 3);
		cubetran2->LocalPosition() = glm::vec3(0, 1, -3);
		plighttrans->LocalPosition() = glm::vec3(0, 1, 0);
		lighttrans->LocalEualrAngle() = glm::vec3(45, 15, 0);;

		SceneObject* floorGround = factory.CreateEmpty();

		for (int32_t x = -3; x < 3; x++) {
			for (int32_t y = -3; y < 3; y++) {
				SceneObject* plane = factory.m_3D.CreateMesh(bm->GetPrimitiveMesh("Plane.obj"), lembertMat);
				plane->SetParent(floorGround);
				TransformationComponent* planetran = plane->GetRelateComponent<TransformationComponent>();
				planetran->LocalPosition() = glm::vec3(x * 25, 0, y * 25);
				planetran->LocalEualrAngle() = glm::vec3(180, 0, 0);
				planetran->LocalScale() = glm::vec3(10, 1, 10);
				std::string n = "plane: ";
				n += std::to_string(x);
				n += "x";
				n += std::to_string(y);
				plane->Name = n;
			}
		}
		m_scenes.push_back(scene);
		scenev->SetCam(&renderer.MainCamera());
	}
	void AppWindow::Update()
	{
		EWindow::Update();	
		GlobalPanels& pg = GlobalPanels::Singleton();
		Global::GlobalStatePackage& psg = Global::GlobalStatePackage::Singleton();
		Renderer& renderer = Renderer::Singleton();
		
		UI::SceneViewerWindow* scene = pg.GetPanel<UI::SceneViewerWindow>("Scene");
		bool shouldupdatescene = psg.state_bool.GetState("Should_Update_Scene");
		bool shouldrenderscene = psg.state_bool.GetState("Should_Render_Scene");
		bool shouldrecordrenderstate = psg.state_bool.GetState("Should_Record_Render_State");
		int32_t rendermode = psg.state_int.GetState("RenderMode");
		RenderState renderstate = psg.state_renderState.GetState("Current", RenderState());
		CameraComponent* selectcamera = psg.state_camera.GetState("SelectCamera");
		std::vector<Scene*> scenes = psg.scenes.GetStates("Scenes");
		

		if (!scene->HaveCam()) {
			scene->SetCam(&renderer.MainCamera());
		}
		scenes = m_scenes;
		shouldrenderscene = scene->Visible();
		updateScenes = shouldupdatescene;
		renderScenes = shouldrenderscene;
		renderState = shouldrecordrenderstate && scene->Visible();
		renderstate = GetRenderState();
		if (selectcamera) {
			m_renderCamera = std::vector<CameraComponent*>();
			m_renderCamera.push_back(selectcamera);
		}
		
		switch (rendermode)
		{
		case 0:
			wireframe = false;
			shaded = true;
			break;
		case 1:
			wireframe = true;
			shaded = false;
			break;
		case 2:
			wireframe = true;
			shaded = true;
			break;
		}
		psg.scenes.SetState("Scenes", scenes);
		psg.state_bool.SetState("Should_Render_Scene", shouldrenderscene);
		psg.state_renderState.SetState("Current", renderstate);
	}
	void AppWindow::Render()
	{
		EWindow::Render();
	}
	void AppWindow::PostRender()
	{
		EWindow::PostRender();
	}
	void AppWindow::GUI()
	{
		GlobalPanels& pg = GlobalPanels::Singleton();
		TaraProject& pc = TaraProject::Singleton();
		UI::ImGui_WindiwFlags wflags = UI::ImGui_WindiwFlags();
		wflags.MenuBar = true;

		UI::AppSettingWindow* setting = pg.GetPanel<UI::AppSettingWindow>("Setting");
		UI::ImGui_WindowBase* asset = pg.GetPanel("Asset");
		UI::ImGui_WindowBase* scenev = pg.GetPanel("Scene");
		UI::ImGui_WindowBase* _property = pg.GetPanel("Property");
		UI::ImGui_WindowBase* hierarchy = pg.GetPanel("Hierarchy");
		UI::ImGui_WindowBase* console = pg.GetPanel("Console");
		UI::ImGui_WindowBase* helper = pg.GetPanel("Helper");

		if (UI::ImGui_BeginMainmenuBar()) {
			if (UI::ImGui_BeginMenu("File")) {
				if (UI::ImGui_MenuItem("New Project")) {
					
				}
				if (UI::ImGui_MenuItem("Open Project")) {

				}
				if (UI::ImGui_MenuItem("Open Recent Project")) {

				}
				UI::ImGui_Separator();
				if (UI::ImGui_MenuItem("New Scene")) {

				}
				if (UI::ImGui_MenuItem("Load Scene (Single)")) {

				}
				if (UI::ImGui_MenuItem("Load Scene (Additional)")) {

				}
				if (UI::ImGui_BeginMenu("Load Demo Scene")) {
					if (UI::ImGui_MenuItem("Demo Scene")) {
						DeleteAllScene();
					}
					if (UI::ImGui_MenuItem("Complex Model Test Scene")) {
						DeleteAllScene();
					}
					if (UI::ImGui_MenuItem("Physics Test Scene")) {
						DeleteAllScene();
					}
					if (UI::ImGui_MenuItem("Framebuffer Texture Test Scene")) {
						DeleteAllScene();
					}
					UI::ImGui_EndMenu();
				}
				UI::ImGui_Separator();
				if (UI::ImGui_MenuItem("Import")) {

				}
				if (UI::ImGui_MenuItem("Export")) {

				}
				UI::ImGui_Separator();
				if (UI::ImGui_MenuItem("Exit")) {
					Close();
				}
				UI::ImGui_EndMenu();
			}
			if (UI::ImGui_BeginMenu("Edit")) {
				if (UI::ImGui_MenuItem("Cut")) {

				}
				if (UI::ImGui_MenuItem("Copy")) {

				}
				if (UI::ImGui_MenuItem("Duplicate")) {

				}
				if (UI::ImGui_MenuItem("Paste")) {

				}
				if (UI::ImGui_MenuItem("Delete")) {

				}
				UI::ImGui_Separator();
				if (UI::ImGui_BeginMenu("Preference")) {
					if (UI::ImGui_MenuItem("Application")) {
						setting->SetSelect(0);
						setting->SetVisible(true);
					}
					if (UI::ImGui_MenuItem("Style")) {
						setting->SetSelect(1);
						setting->SetVisible(true);
					}
					if (UI::ImGui_MenuItem("Editor")) {
						setting->SetSelect(2);
						setting->SetVisible(true);
					}
					if (UI::ImGui_MenuItem("Plugin")) {
						setting->SetSelect(3);
						setting->SetVisible(true);
					}
					UI::ImGui_EndMenu();
				}
				UI::ImGui_EndMenu();
			}
			if (UI::ImGui_BeginMenu("Asset")) {
				UI::ImGui_EndMenu();
			}
			if (UI::ImGui_BeginMenu("Window")) {
				if (UI::ImGui_BeginMenu("Common")) {
					if (UI::ImGui_MenuItem("Asset", 0, asset->Visible())) {
						asset->SetVisible(!asset->Visible());
					}
					if (UI::ImGui_MenuItem("Scene Viewer", 0, scenev->Visible())) {
						scenev->SetVisible(!scenev->Visible());
					}
					if (UI::ImGui_MenuItem("Properties", 0, _property->Visible())) {
						_property->SetVisible(!_property->Visible());
					}
					if (UI::ImGui_MenuItem("Hierarchy", 0, hierarchy->Visible())) {
						hierarchy->SetVisible(!hierarchy->Visible());
					}
					if (UI::ImGui_MenuItem("Console", 0, console->Visible())) {
						console->SetVisible(!console->Visible());
					}
					UI::ImGui_EndMenu();
				}
				if (UI::ImGui_BeginMenu("Environment")) {
					if (UI::ImGui_MenuItem("World")) {

					}
					UI::ImGui_EndMenu();
				}
				if (UI::ImGui_BeginMenu("Animation")) {
					if (UI::ImGui_MenuItem("Timeline")) {

					}
					UI::ImGui_EndMenu();
				}
				if (UI::ImGui_BeginMenu("Logic")) {
					if (UI::ImGui_MenuItem("System Blueprint")) {

					}
					if (UI::ImGui_MenuItem("Node Editor")) {

					}
					if (UI::ImGui_MenuItem("Code Editor")) {

					}
					UI::ImGui_EndMenu();
				}
				UI::ImGui_EndMenu();
			}
			if (UI::ImGui_BeginMenu("Help")) {
				if (UI::ImGui_MenuItem("Github Page")) {

				}
				if (UI::ImGui_MenuItem("Debug Menu", 0, helper->Visible())) {
					//helper->SetVisible(!helper->Visible());
				}
				if (UI::ImGui_MenuItem("About")) {

				}
				UI::ImGui_EndMenu();
			}
			UI::ImGui_EndMainmenuBar();
		}
		projectcreation->SetVisible(!pc.HaveProject() && pc.RequireProject());
		projectcreation->Render();
	}
	void AppWindow::DeleteAllScene() {
		Global::GlobalStatePackage& psg = Global::GlobalStatePackage::Singleton();
		std::vector<Scene*> scenes = psg.scenes.GetStates("Scenes");
		for (auto s : scenes) {
			delete s;
		}
		scenes.clear();
		psg.scenes.SetState("Scenes", scenes);
	}
}