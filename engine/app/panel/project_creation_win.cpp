#include "project_creation_win.h"
#include <glm/glm.hpp>
#include "../../editor/editor_style.h"
#include "../../editor/editor_lowlevel.h"
#include "../../editor/project/project.h"
#include "../../engine/core/input.h"
#include "../../engine/core/utility.h"
#include "../../engine/core/buildin/buildin_manager.h"
#include <nlohmann/json.hpp>
#include "file_explorer_win.h"
#include "global_state.h"

namespace Tara {
	namespace UI {
		ProjectCreationWindow::ProjectCreationWindow() : ImGui_PopWindow("Project Creation")
		{
			BuildinManager& bm = BuildinManager::Singleton();
			flag.NoMove = true;
			flag.NoCollapse = true;
			flag.UnsaveDocumentDot = true;
			flag.UnSave = true;
			flag.MenuBar = false;
			flag.NoResize = true;
			flag.NoDecoration = true;
			flag.AlwaysAutoResize = true;
			pflags.AnyPopupId = true;
			pflags.AnyPopupLevel = true;
			selectflag.DontClosePopups = true;

			// ! Import template
			m_Menu.push_back(ProjectTemplate("Create Empty Project", "Generate a project without any default resources.", std::bind(&ProjectCreationWindow::MenuEmpty, this)));
			if (bm.FileExist("template/templates.json")) {
				std::string jstring = bm.GetFileData_String("template/templates.json");
				nlohmann::json j = Utility::Json::ReadJsonString(jstring.c_str());
				nlohmann::json temps = j["templates"];
				if (temps.is_array()) {
					size_t tempCount = 0;
					for (auto& ts : temps) {
						nlohmann::json jn = ts["name"];
						nlohmann::json jd = ts["description"];
						if (!jn.is_string() || !jd.is_string()) continue;
						std::string n = jn.get<std::string>();
						std::string d = jd.get<std::string>();
						nlohmann::json links = ts["link"];
						if (links.is_array()) {
							for (auto& lks : links) {

							}
						}
						tempCount++;
					}
				}
			}

			m_Menu.push_back(ProjectTemplate("Create 3D Project", "Select 3D project templates.", std::bind(&ProjectCreationWindow::Menu3D, this), [&]()->bool {return select == 0; }));
			m_Menu.push_back(ProjectTemplate("Create 2D Project", "Select 2D project templates.", std::bind(&ProjectCreationWindow::Menu2D, this), [&]()->bool {return select == 1; }));
			m_Menu.push_back(ProjectTemplate("Create Animation Project", "Select animation project templates.", std::bind(&ProjectCreationWindow::MenuAnim, this), [&]()->bool {return select == 2; }));
			m_Menu.push_back(ProjectTemplate("Open Project", "Open exist project.", std::bind(&ProjectCreationWindow::MenuOpen, this)));
			m_Menu.push_back(ProjectTemplate("Continue", "Continue without project structure binding.", std::bind(&ProjectCreationWindow::MenuContinue, this)));

			m_Template3D.push_back(ProjectTemplate("Standard Scene", "Generate standard 3D scene.", std::bind(&ProjectCreationWindow::T3DStandard, this)));
			m_Template3D.push_back(ProjectTemplate("First Person", "Generate standard 3D scene.\nLoad first person script and prefab.", std::bind(&ProjectCreationWindow::T3DFirst, this)));
			m_Template3D.push_back(ProjectTemplate("Third Person", "Generate standard 3D scene.\nLoad third person script and prefab.", std::bind(&ProjectCreationWindow::T3DThird, this)));
			m_Template3D.push_back(ProjectTemplate("Top Down", "Generate standard 3D scene.\nLoad top down script and prefab.", std::bind(&ProjectCreationWindow::T3DTop, this)));
			m_Template3D.push_back(ProjectTemplate("Strategy", "Generate standard 3D scene.\nLoad strategy script and prefab.", std::bind(&ProjectCreationWindow::T3DStrategy, this)));
			m_Template3D.push_back(ProjectTemplate("Platfrom", "Generate standard 3D scene.\nLoad platfrom script and prefab.", std::bind(&ProjectCreationWindow::T3DPlatfrom, this)));

			m_Template2D.push_back(ProjectTemplate("Standard Scene", "Generate standard 2D scene.", std::bind(&ProjectCreationWindow::T2DStandard, this)));
			m_Template2D.push_back(ProjectTemplate("Platfrom", "", std::bind(&ProjectCreationWindow::T2DPlatfrom, this)));

			m_TemplateAnim.push_back(ProjectTemplate("Standard Scene", "Generate standard 3D scene.", std::bind(&ProjectCreationWindow::TAnimStandard, this)));
			CheckCreateState();
		}
		ProjectCreationWindow::~ProjectCreationWindow()
		{

		}
		void ProjectCreationWindow::Start()
		{
			glm::vec2 size = ImGui_GetViewportSize();
			ImGui_SetNextWindowSize({ std::fmin(size.x - 200, 600), std::fmin(size.y - 200, 600) });
			ImGui_SetNextWindowPos({ size.x / 2.f, size.y / 2.f }, {0.5, 0.5});
		}
		void ProjectCreationWindow::Content()
		{
			somethingHoverd = false;
			ImGui_CenterText("Project creation");
			ImGui_Dummy(0, 20);
			ImGui_Column(2, false);
			ImGui_SetColumnWidth(0, 200);
			LeftMenu();
			ImGui_NextColumn();
			RightContent();
			ImGui_NextColumn();
			ImGui_Column(1, false);
			if (somethingHoverd) tooltipCountdown += EInput::Delta();
			else tooltipCountdown = 0;
		}
		void ProjectCreationWindow::LeftMenu()
		{
			DrawTemplateMenu(m_Menu);
		}
		void ProjectCreationWindow::RightContent()
		{
			ImGui_BeginDisabled(errorMessage.size() > 0);
			if (ImGui_ColumnButton("Create")) {

			}
			ImGui_EndDisabled();
			if (ImGui_ColumnButton("Select Directory")) {

			}
			if (ImGui_TextField("Path", &projectPath)) {
				CheckCreateState();
			}
			ImGui_TextColor(1, 0.2f, 0.2f);
			ImGui_Text(errorMessage.c_str());
			ImGui_PopColor();
			ImGui_Text("Template Select:");
			switch (select) {
			case 0:
				DrawTemplateSecondaryMenu(m_Template3D);
				break;
			case 1:
				DrawTemplateSecondaryMenu(m_Template2D);
				break;
			case 2:
				DrawTemplateSecondaryMenu(m_TemplateAnim);
				break;
			}
		}
		void ProjectCreationWindow::OpenProject()
		{
			PanelGlobalState& pgs = PanelGlobalState::Singleton();
			pgs.fileexplorer->SetExtensionsFilter(false, { ".tara" });
			pgs.fileexplorer->RegisterCallback(std::bind(&ProjectCreationWindow::ReceivedFile, this, std::placeholders::_1));
			pgs.fileexplorer->Open();
		}
		void ProjectCreationWindow::OpenProjectDir()
		{
			PanelGlobalState& pgs = PanelGlobalState::Singleton();
			pgs.fileexplorer->SetFolderMode(true);
			pgs.fileexplorer->RegisterCallback(std::bind(&ProjectCreationWindow::ReceivedDir, this, std::placeholders::_1));
			pgs.fileexplorer->Open();
		}
		void ProjectCreationWindow::ReceivedFile(std::vector<std::string> ps)
		{
			PanelGlobalState& pgs = PanelGlobalState::Singleton();
			if (ps.size() != 1) {
				return;
			}
			std::string path = ps.at(0);
			TaraProject& tp = TaraProject::Singleton();
			bool succ = tp.OpenProject(path);
			pgs.fileexplorer->SetVisible(false);
		}
		void ProjectCreationWindow::ReceivedDir(std::vector<std::string> ps)
		{
			PanelGlobalState& pgs = PanelGlobalState::Singleton();
			if (ps.size() != 1) {
				return;
			}
			projectPath = ps.at(0);
		}
		void ProjectCreationWindow::CheckCreateState()
		{
			if (!std::filesystem::exists(projectPath)) {
				errorMessage = Utility::String::FormatString("Directory path does not exist: %s", projectPath.c_str());
				return;
			}

			errorMessage = "";
		}
		void ProjectCreationWindow::DrawTemplateMenu(std::vector<ProjectTemplate>& target)
		{
			ImGui_HeaderColor(0.2f, 0.8f, 0.8f, 0.3f);
			for (auto& i : target) {
				if (ImGui_Selectable(i.name.c_str(), (i.enable ? i.enable() : false) , selectflag)) {
					if (i.action) i.action();
				}
				if (ImGui_IsItemHovered()) {
					somethingHoverd = true;
					if (tooltipCountdown > 1.f && i.description.size() > 0) {
						ImGui_BeginTooltip();
						ImGui_Text(i.description.c_str());
						ImGui_EndTooltip();
					}
				}
			}
			ImGui_PopColor();
		}
		void ProjectCreationWindow::DrawTemplateSecondaryMenu(std::vector<ProjectTemplate>& target)
		{
			ImGui_HeaderColor(0.2f, 0.8f, 0.8f, 0.3f);
			int32_t c = 0;
			for (auto& i : target) {
				if (ImGui_Selectable(i.name.c_str(), second_select == c, selectflag)) {
					if (i.action) i.action();
				}
				if (ImGui_IsItemHovered()) {
					somethingHoverd = true;
					if (tooltipCountdown > 1.f && i.description.size() > 0) {
						ImGui_BeginTooltip();
						ImGui_Text(i.description.c_str());
						ImGui_EndTooltip();
					}
				}
				c++;
			}
			ImGui_PopColor();
		}
		void ProjectCreationWindow::MenuEmpty()
		{
			
		}
		void ProjectCreationWindow::Menu3D()
		{
			select = 0;
			second_select = -1;
		}
		void ProjectCreationWindow::Menu2D()
		{
			select = 1;
			second_select = -1;
		}
		void ProjectCreationWindow::MenuAnim()
		{
			select = 2;
			second_select = -1;
		}
		void ProjectCreationWindow::MenuOpen()
		{
			OpenProject();
		}
		void ProjectCreationWindow::MenuContinue()
		{
			TaraProject::Singleton().SetProjectSetupRequirement(false);
		}
		void ProjectCreationWindow::T3DStandard()
		{
			second_select = 0;
		}
		void ProjectCreationWindow::T3DFirst()
		{
			second_select = 1;
		}
		void ProjectCreationWindow::T3DThird()
		{
			second_select = 2;
		}
		void ProjectCreationWindow::T3DTop()
		{
			second_select = 3;
		}
		void ProjectCreationWindow::T3DStrategy()
		{
			second_select = 4;
		}
		void ProjectCreationWindow::T3DPlatfrom()
		{
			second_select = 5;
		}
		void ProjectCreationWindow::T2DStandard()
		{
		}
		void ProjectCreationWindow::T2DPlatfrom()
		{
		}
		void ProjectCreationWindow::TAnimStandard()
		{
		}
	}
}
