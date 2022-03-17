#pragma once
#include "../../editor/editor_container.h"

namespace Tara {
	namespace UI {
		/// <summary>
		/// <para> A struct contain project template description. </para>
		/// <para> Use for render project creation menu. </para>
		/// </summary>
		struct ProjectTemplate {
			ProjectTemplate(std::string n,
				std::string d,
				std::function<void()> a) : name(n), description(d), action(a){}
			ProjectTemplate(std::string n,
				std::string d,
				std::function<void()> a,
				std::function<bool()> e) : name(n), description(d), action(a), enable(e) {}
			/// <summary>
			/// Display title.
			/// </summary>
			std::string name;
			/// <summary>
			/// Tooltip message.
			/// </summary>
			std::string description;
			/// <summary>
			/// Click action.
			/// </summary>
			std::function<void()> action;
			/// <summary>
			/// Selectable enable getter method.
			/// </summary>
			std::function<bool()> enable;
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
			virtual void LeftMenu();
			/// <summary>
			/// Render project right content.
			/// </summary>
			virtual void RightContent();

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
			/// <param name="target">Description list</param>
			void DrawTemplateMenu(std::vector<ProjectTemplate>& target);
			/// <summary>
			/// <para> Display list of context with pre define selectable element enable getter method. </para>
			/// <para> This will ignore target content's enable getter. </para>
			/// <para> Instead it will check match second_select by vector order. </para>
			/// </summary>
			/// <param name="target">Description list</param>
			void DrawTemplateSecondaryMenu(std::vector<ProjectTemplate>& target);

			ImGui_SelectableFlags selectflag = ImGui_SelectableFlags();
			std::vector<ProjectTemplate> m_Menu = std::vector<ProjectTemplate>();
			std::vector<ProjectTemplate> m_Template3D = std::vector<ProjectTemplate>();
			std::vector<ProjectTemplate> m_Template2D = std::vector<ProjectTemplate>();
			std::vector<ProjectTemplate> m_TemplateAnim = std::vector<ProjectTemplate>();

		private:
			void MenuEmpty();
			void Menu3D();
			void Menu2D();
			void MenuAnim();
			void MenuOpen();
			void MenuContinue();

			void T3DStandard();
			void T3DFirst();
			void T3DThird();
			void T3DTop();
			void T3DStrategy();
			void T3DPlatfrom();

			void T2DStandard();
			void T2DPlatfrom();

			void TAnimStandard();

			std::string projectPath;
			std::string errorMessage;
			int32_t select = -1;
			int32_t second_select = -1;
			bool somethingHoverd = false;
			float_t tooltipCountdown = 0;
		};
	}
}

