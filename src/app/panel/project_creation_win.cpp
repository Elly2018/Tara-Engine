#include "project_creation_win.h"
#include <glm/glm.hpp>
#include "../../editor/editor_style.h"
#include "../../editor/editor_lowlevel.h"
#include "../../editor/project/project.h"
#include "../../engine/core/input.h"
#include "../../engine/core/utility.h"
#include "../../engine/core/texture/texture.h"
#include "../../engine/core/buildin/buildin_manager.h"
#include <nlohmann/json.hpp>
#include "file_explorer_win.h"
#include "global_state.h"

namespace Tara {
	namespace UI {
		ProjectCreationWindow::ProjectCreationWindow() : ImGui_PopWindow("Project Creation")
		{
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
			fileexplorer = new FileExplorerWindow();
			// ! Import template
			//m_Menu.push_back(ProjectTemplate("Create Empty Project", "Generate a project without any default resources.", std::bind(&ProjectCreationWindow::MenuEmpty, this)));
			ImportTemplates();
			CheckCreateState();
		}
		ProjectCreationWindow::~ProjectCreationWindow()
		{

		}
		void ProjectCreationWindow::Start()
		{
			glm::vec2 size = ImGui_GetViewportSize();
			ImGui_SetNextWindowSize({ std::fmin(size.x - 200, 1200), std::fmin(size.y - 200, 800) });
			ImGui_SetNextWindowPos({ size.x / 2.f, size.y / 2.f }, {0.5, 0.5});
		}
		void ProjectCreationWindow::Content()
		{
			ImGui_HeaderColor(0.2f, 0.8f, 0.8f, 0.3f);
			somethingHoverd = false;
			ImGui_CenterText("Project creation");
			ImGui_Dummy(0, 20);
			ImGui_Column(3, false);
			ImGui_SetColumnWidth(0, 200);
			CategoryMenu();
			ImGui_NextColumn();
			TemplateMenu();
			ImGui_NextColumn();
			DescriptionContent();
			ImGui_NextColumn();
			ImGui_Column(1, false);
			if (somethingHoverd) tooltipCountdown += EInput::Delta();
			else tooltipCountdown = 0;
			ImGui_PopColor();
			fileexplorer->Render();
		}
		void ProjectCreationWindow::CategoryMenu()
		{
			DrawTemplateMenu();
			if (ImGui_Selectable("Open Project##Project Creation")) {
				OpenProject();
			}
			if (ImGui_Selectable("Continue##Project Creation")) {
				TaraProject& project = TaraProject::Singleton();
				project.SetProjectSetupRequirement(false);
			}
		}
		void ProjectCreationWindow::TemplateMenu()
		{
			ImGui_Text("Template Select:");
			DrawTemplateSecondaryMenu(select);
		}
		void ProjectCreationWindow::DescriptionContent()
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
		}
		void ProjectCreationWindow::OpenProject()
		{
			fileexplorer->SetToDefault();
			fileexplorer->SetExtensionsFilter(false, { ".tara" });
			fileexplorer->RegisterCallback(std::bind(&ProjectCreationWindow::ReceivedFile, this, std::placeholders::_1));
			fileexplorer->Open();
		}
		void ProjectCreationWindow::OpenProjectDir()
		{
			fileexplorer->SetFolderMode(true);
			fileexplorer->RegisterCallback(std::bind(&ProjectCreationWindow::ReceivedDir, this, std::placeholders::_1));
			fileexplorer->Open();
		}
		void ProjectCreationWindow::ReceivedFile(std::vector<std::string> ps)
		{
			if (ps.size() != 1) {
				return;
			}
			std::string path = ps.at(0);
			TaraProject& tp = TaraProject::Singleton();
			bool succ = tp.OpenProject(path);
			fileexplorer->Done();
			TARA_DEBUG("Open project path at: %s", path.c_str());
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
		void ProjectCreationWindow::DrawTemplateMenu()
		{
			for (auto& header : category) {
				if (ImGui_Selectable(header.second.name.c_str(), (header.first == select), selectflag)) {
					select = header.first;
				}
				if (ImGui_IsItemHovered()) {
					somethingHoverd = true;
					if (tooltipCountdown > 1.f && header.second.description.size() > 0) {
						ImGui_BeginTooltip();
						ImGui_Text(header.second.description.c_str());
						ImGui_EndTooltip();
					}
				}
			}
		}
		void ProjectCreationWindow::DrawTemplateSecondaryMenu(int32_t key)
		{
			if (!temps.count(key)) return;
			int32_t c = 0;
			for (auto& ts : temps[key]) {
				if (ImGui_Selectable(ts.name.c_str(), (c == second_select), selectflag)) {
					second_select = c;
				}
				c++;
			}
		}
		void ProjectCreationWindow::ImportTemplates()
		{
			BuildinManager& bm = BuildinManager::Singleton();
			if (!bm.FileExist("template/templates.json")) return;
			std::string jstring = bm.GetFileData_String("template/templates.json");
			nlohmann::json j = Utility::Json::ReadJsonString(jstring.c_str());
			nlohmann::json jtemps = j["templates"];
			if (!jtemps.is_array()) return;
			// ! Get all template category
			for (auto& ts : jtemps) {
				std::vector<std::string> templinks = std::vector<std::string>();
				nlohmann::json jn = ts["name"];
				nlohmann::json jd = ts["description"];
				if (!jn.is_string() || !jd.is_string()) {
					TARA_WARNING("Template category format reading error: %s", "template/templates.json");
					continue;
				}
				std::string n = jn.get<std::string>();
				std::string d = jd.get<std::string>();
				nlohmann::json links = ts["link"];
				if (!links.is_array()) {
					TARA_WARNING("Template link varaible is not array: %s", "template/templates.json");
					continue;
				}
				// ! Get template category links
				for (auto& lks : links) {
					if (lks.is_string()) {
						std::string lks_string = lks.get<std::string>();
						templinks.push_back(lks_string);
					}
				}
				if (templinks.size() <= 0) {
					TARA_WARNING("Template category size is zero: %zu", templinks.size());
					continue;
				}
				category[startHeader + category.size() - 1] = ProjectTemplateHeader(n, d);
				std::vector<ProjectTemplate> ptemps = std::vector<ProjectTemplate>();
				// ! Loop over links
				for (auto& lks : templinks) {
					std::string prefix_realPath = "template/";
					prefix_realPath.append(lks);
					std::string realPath = prefix_realPath;
					std::string mdPath = prefix_realPath;
					std::string des = "";
					realPath.append(".json");
					mdPath.append(".md");
					if (!bm.FileExist(realPath)) {
						TARA_WARNING("Buildin path does not exist: %s", realPath.c_str());
						continue;
					}
					if (bm.FileExist(mdPath)) {
						des = bm.GetFileData_String(mdPath);
					}
					std::vector<ProjectTemplateImport> imports = std::vector<ProjectTemplateImport>();
					std::string tempconfigstring = bm.GetFileData_String(realPath);
					nlohmann::json jtempconfig = Utility::Json::ReadJsonString(tempconfigstring.c_str());
					nlohmann::json jcn = jtempconfig["name"];
					nlohmann::json jcr = jtempconfig["icon"];
					nlohmann::json jci = jtempconfig["assets"]["import"];
					if (!jcn.is_string() || !jci.is_array()) {
						TARA_WARNING("Template format reading error: %s", realPath.c_str());
						continue;
					}
					std::string cn = jcn.get<std::string>();
					// ! Get template imports
					for (auto& imp : jci) {
						nlohmann::json c_from = imp["from"];
						nlohmann::json c_to = imp["to"];
						nlohmann::json c_recursion = imp["recursion"];
						if (!c_from.is_string() || !c_to.is_array() || !c_recursion.is_boolean()) {
							TARA_WARNING("Template import format reading error: %s", realPath.c_str());
							continue;
						}
						std::string cfrom = c_from.get<std::string>();
						std::string cto = c_to.get<std::string>();
						bool crecursion = c_recursion.get<bool>();
						imports.push_back(ProjectTemplateImport(cfrom, cto, crecursion));
					}
					bool haveIcon = jcr.is_string();
					Texture2D* cicon = nullptr;
					if (haveIcon) {
						// We have icon path
						PackageManager& pm = PackageManager::Singleton();
						cicon = pm.GetTexture(jcr.get<std::string>());
					}
					ptemps.push_back(ProjectTemplate(cn, des, cicon, imports));
				}
				temps[startHeader + category.size() - 1] = ptemps;
			}
		}
	}
}
