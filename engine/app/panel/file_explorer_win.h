#pragma once
#include <filesystem>
#include <functional>
#include "../../editor/editor_container.h"

namespace Tara {
	namespace UI {
		/*
			Summary:
				A window which help user to pick directory or file.
		*/
		class FileExplorerWindow : public ImGui_PopWindow {
		public:
			/*
				Summary:
					Default path will be home, desktop.
			*/
			FileExplorerWindow();
			FileExplorerWindow(std::filesystem::path startpath);
			~FileExplorerWindow();

			void Start() override;
			void Content() override;

			void SetToDefault();
			/*
				Summary:
					Set current path.
			*/
			void SetPath(std::filesystem::path);
			/*
				Summary:
					Set folder mode
			*/
			void SetFolderMode(bool foldermode);
			/*
				Summary:
					Set multiple select mode.
			*/
			void SetMultipleSelection(bool b);
			/*
				Summary:
					Set extension filter.
				Arugments:
					exclude: True if user want files with extension that without in the given list.
					exts: Extnesions list.
			*/
			void SetExtensionsFilter(bool exclude, std::vector<std::string> exts);
			/*
				Summary:
					Register callback function.
			*/
			void RegisterCallback(std::function<void(std::vector<std::string>)> callback);
			/*
				Summary:
					Clean callback function.
			*/
			void CleanCallback();
			void Open();
			void Done();

		private:
			/*
				Summary:
					Render path text field
			*/
			void RenderPathBar();
			/*
				Summary:
					Render directory tree.
			*/
			void RenderTree();
			/*
				Summary:
					Render tags.
			*/
			void RenderQuickAccess();
			/*
				Summary:
					Render file list.
			*/
			void RenderFileList();

			std::filesystem::path current;
			std::vector<std::function<void(std::vector<std::string>)>> callbacks;
			bool multiple = false;
			bool exclude = false;
			bool folder = false;
			std::vector<std::string> extensions;
		};
	}
}

