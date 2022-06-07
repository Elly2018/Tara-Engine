#pragma once
#include "engine/core/config.h"
#include "editor/editor_container.h"
#include "project_template.h"

namespace Tara {
	namespace UI {
		class FileExplorerWindow;

		/// <summary>
		/// <para> Project creation window is showing when application start. </para>
		/// <para> It helps user to generate project structure and binding with the tara engine. </para>
		/// </summary>
		class TARA_APP_API ProjectCreationWindow : public ImGui_PopWindow {
		public:
			ProjectCreationWindow();
			~ProjectCreationWindow();

			void Start() override;
			void Content() override;

		protected:
			/// <summary>
			/// Render project left menu.
			/// </summary>
			virtual void CategoryMenu();
			/// <summary>
			/// Render project right content.
			/// </summary>
			virtual void TemplateMenu();
			virtual void DescriptionContent();

			void OpenProject();
			void OpenProjectDir();
			virtual void ReceivedFile(std::vector<std::string> ps);
			virtual void ReceivedDir(std::vector<std::string> ps);
			/// <summary>
			/// <para> Check if it's possible create project with current setting. </para>
			/// <para> If not set the error message. </para>
			/// </summary>
			virtual void CheckCreateState();
			/// <summary>
			/// Display list of context.
			/// </summary>
			void DrawTemplateMenu();
			/// <summary>
			/// <para> Display list of context with pre define selectable element enable getter method. </para>
			/// <para> This will ignore target content's enable getter. </para>
			/// <para> Instead it will check match second_select by vector order. </para>
			/// </summary>
			/// <param name="key">Key of the template index</param>
			void DrawTemplateSecondaryMenu(int32_t key);

			ImGui_SelectableFlags selectflag = ImGui_SelectableFlags();

		private:
			/// <summary>
			/// Import templates from buildin package.
			/// </summary>
			void ImportTemplates();

			const int32_t startHeader = 1;
			std::string projectPath;
			std::string errorMessage;
			int32_t select = -1;
			int32_t second_select = -1;
			bool somethingHoverd = false;
			float_t tooltipCountdown = 0;
			std::map<int32_t, ProjectTemplateHeader> category = std::map<int32_t, ProjectTemplateHeader>();
			std::map<int32_t, std::vector<ProjectTemplate>> temps = std::map<int32_t, std::vector<ProjectTemplate>>();
			std::unique_ptr<FileExplorerWindow> fileexplorer = nullptr;
		};
	}
}

