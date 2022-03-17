#include "file_explorer_win.h"
#include "../../editor/editor_lowlevel.h"

namespace Tara {
	namespace UI {
		FileExplorerWindow::FileExplorerWindow() : ImGui_PopWindow("File Explorer")
		{
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
			ImGui_SetNextWindowSize({ 800, 540 });
			ImGui_SetNextWindowPos({ size.x / 2.f, size.y / 2.f }, { 0.5, 0.5 });
		}
		void FileExplorerWindow::Content()
		{
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
		}
		void FileExplorerWindow::Done()
		{
			SetVisible(false);
			SetToDefault();
		}
		void FileExplorerWindow::RenderPathBar()
		{
		}
		void FileExplorerWindow::RenderTree()
		{
		}
		void FileExplorerWindow::RenderQuickAccess()
		{
		}
		void FileExplorerWindow::RenderFileList()
		{
		}
	}
}