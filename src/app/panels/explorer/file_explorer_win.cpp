#include "file_explorer_win.h"
#include "editor/editor_lowlevel.h"
#include "engine/core/utility.h"

namespace Tara {
	namespace UI {
		const static volatile char A = 'a'; // All this is to prevent reverse engineering
#ifdef unix
		std::filesystem::path FileExplorerWindow::record = getenv("HOME");
		std::string FileExplorerWindow::recordDrive = getenv("HOMEDRIVE");
#elif defined(_WIN32)
		std::filesystem::path FileExplorerWindow::record = getenv("HOMEPATH");
		std::string FileExplorerWindow::recordDrive = getenv("HOMEDRIVE");
#endif
		
		FileExplorerWindow::FileExplorerWindow() : ImGui_PopWindow("File Explorer")
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
			callbacks = std::vector<std::function<void(std::vector<std::string>)>>();
			extensions = std::vector<std::string>();
		}
		FileExplorerWindow::FileExplorerWindow(std::filesystem::path startpath) : FileExplorerWindow()
		{
			current = startpath;
		}
		FileExplorerWindow::~FileExplorerWindow()
		{
		}
		void FileExplorerWindow::Start()
		{
			glm::vec2 size = ImGui_GetViewportSize();
			ImGui_SetNextWindowSize({ std::fmin(size.x - 200, 800), std::fmin(size.y - 200, 540) });
			ImGui_SetNextWindowPos({ size.x / 2.f, size.y / 2.f }, { 0.5, 0.5 });
		}
		void FileExplorerWindow::Content()
		{
			glm::vec2 size = ImGui_GetViewportSize();
			RenderPathBar();
			ImGui_Dummy(0, 30);
			ImGui_Column(2, true);
			if (ImGui_BeginChild("Left##FileExp", 0, std::fmin(size.y - 200, 430))) {
				RenderQuickAccess();
				RenderTree();
				ImGui_EndChild();
			}
			ImGui_NextColumn();
			if (ImGui_BeginChild("Right##FileExp", 0, std::fmin(size.y - 200, 430))) {
				RenderFileList();
				ImGui_EndChild();
			}
			ImGui_NextColumn();
			ImGui_Column(1, false);
			ActionBar();
		}
		void FileExplorerWindow::SetToDefault()
		{
		}
		void FileExplorerWindow::SetPath(std::filesystem::path)
		{
		}
		void FileExplorerWindow::SetFolderMode(bool foldermode)
		{
		}
		void FileExplorerWindow::SetMultipleSelection(bool b)
		{
		}
		void FileExplorerWindow::SetExtensionsFilter(bool exclude, std::vector<std::string> exts)
		{
		}
		void FileExplorerWindow::RegisterCallback(std::function<void(std::vector<std::string>)> callback)
		{
			callbacks.push_back(callback);
		}
		void FileExplorerWindow::CleanCallback()
		{
			callbacks = std::vector<std::function<void(std::vector<std::string>)>>();
		}
		void FileExplorerWindow::Open()
		{
			SetVisible(true);
			current = record;
			currentDrive = recordDrive;
		}
		void FileExplorerWindow::Done()
		{
			SetVisible(false);
			SetToDefault();
		}
		void FileExplorerWindow::RenderPathBar()
		{
			std::vector<std::string> pathSplit = std::vector<std::string>();
			pathSplit.push_back(currentDrive);
			std::vector<std::string> ps = Utility::String::Split(current.string(), "\\");
			pathSplit.insert(pathSplit.end(), ps.begin(), ps.end());
			std::string stack = "";
			size_t offset = 0;
			for (size_t i = 0; i < pathSplit.size(); i++) {
				if (pathSplit[i].empty()) continue;
				ImGui_Sameline(0, offset);
				if(i != 0)
					stack += pathSplit[i].c_str();
				if (ImGui_Button(pathSplit[i].c_str())) {
					current = stack;
				}
				ImGui_Sameline(0, offset + 1);
				if (i + 1 != pathSplit.size()) {
					ImGui_Text("/");
					if (i != 0)
						stack += "/";
				}
				offset += pathSplit[i].size() + 1;
			}
		}
		void FileExplorerWindow::RenderTree()
		{
			ImGui_Selectable("E1");
		}
		void FileExplorerWindow::RenderQuickAccess()
		{
			ImGui_Selectable("E2");
			ImGui_Selectable("E3");
		}
		void FileExplorerWindow::RenderFileList()
		{
			//ImGui_CustomTreeNode("", "", false, true);
		}
		void FileExplorerWindow::ActionBar()
		{
			if (ImGui_BeginChild("FileName##FileExp", 0, 24)) {
				glm::vec2 size = ImGui_GetViewportSize();
				ImGui_Column(2, false);
				ImGui_SetColumnWidth(0, std::fmin(size.x - 200, 700));
				ImGui_SetColumnWidth(1, 100);
				ImGui_TextField("File Name##FileExp", &filenameField);
				ImGui_NextColumn();
				if (ImGui_ColumnButton("Extension##FileExp", 24, 10)) {
					ImGui_OpenPopup("ExtensionPopup##FileExp");
				}
				ImGui_NextColumn();
				ImGui_Column(1, false);
				ImGui_EndChild();
			}
			if (ImGui_BeginChild("Actionbar##FileExp", 0, 24)) {
				ImGui_Column(2, false);
				ImGui_ColumnButton("Select##FileExplorer", 24, 10);
				ImGui_NextColumn();
				ImGui_ColumnButton("Cancel##FileExplorer", 24, 10);
				ImGui_NextColumn();
				ImGui_Column(1, false);
				ImGui_EndChild();
			}

			if (ImGui_BeginPopup("ExtensionPopup##FileExp")) {
				for (auto& i : extensions) {
					ImGui_Selectable(i.c_str());
				}
				ImGui_EndPopup();
			}
		}
		void FileExplorerWindow::UpdateTree()
		{
			nametree<std::string> s();
		}
	}
}