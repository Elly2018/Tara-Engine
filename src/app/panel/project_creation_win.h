#pragma once
#include "../../editor/editor_container.h"

namespace Tara {
	class Texture2D;
	namespace UI {
		class FileExplorerWindow;
		struct ProjectTemplateHeader {
			ProjectTemplateHeader() = default;
			ProjectTemplateHeader(std::string n,
				std::string d) : name(n), description(d) {}
			std::string name;
			std::string description;
		};

		struct ProjectTemplateImport {
			ProjectTemplateImport() = default;
			ProjectTemplateImport(std::string f,
				std::string t,
				bool r): from(f), to(t), recursion(r) {}
			std::string from;
			std::string to;
			bool recursion;
		};

		/// <summary>
		/// <para> A struct contain project template description. </para>
		/// <para> Use for render project creation menu. </para>
		/// </summary>
		struct ProjectTemplate {
			ProjectTemplate() = default;
			ProjectTemplate(std::string n,
				std::string d,
				Texture2D* a,
				std::vector<ProjectTemplateImport> is) : name(n), readme(d), preview(a), imports(is){}
			ProjectTemplate(std::string n,
				std::string d,
				std::vector<ProjectTemplateImport> is) : name(n), readme(d), preview(nullptr), imports(is) {}
			/// <summary>
			/// Display title.
			/// </summary>
			std::string name;
			/// <summary>
			/// Tooltip message.
			/// </summary>
			std::string readme;
			/// <summary>
			/// Template icon
			/// </summary>
			Texture2D* preview;
			/// <summary>
			/// Import paths
			/// </summary>
			std::vector<ProjectTemplateImport> imports;
		};


		/// <summary>
		/// <para> Project creation window is showing when application start. </para>
		/// <para> It helps user to generate project structure and binding with the tara engine. </para>
		/// </summary>
		class ProjectCreationWindow : public ImGui_PopWindow {
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
			FileExplorerWindow* fileexplorer = nullptr;
		};
	}
}

