#pragma once
#include <filesystem>
#include "../editor_config.h"

namespace Tara {
	/*
			Summary:
				The project file manager.
				Handle project vaild and directory path.
		*/
	class TARA_EDITOR_API TaraProject {
	public:
		static TaraProject& Singleton();
		bool CreateProject(std::string name, std::filesystem::path path);
		/*
			Summary:
				Trying to open project by file path.
		*/
		bool OpenProject(std::filesystem::path path);
		/*
			Summary:
				Check if project is loaded or not.
		*/
		bool HaveProject();
		/*
			Summary:
				Set no project mode.
				This will disabled all the feature that require proejct setup.
				But engine will be enable to run without project setup.
		*/
		void SetProjectSetupRequirement(bool b);
		/*
			Summary:
				Check current project setup requirement.
		*/
		bool RequireProject();

	private:
		static TaraProject* m_Singleton;
		/*
			Summary:
				Check project structure and project file is vaild format.
		*/
		bool Vaild(std::filesystem::path path);
		/*
			Summary:
				Read the project file data and import into engine.
		*/
		bool LoadProject();

		bool IsProjectLoad = false;
		bool IsProjectSetupRequire = true;
		std::filesystem::path m_ProjectPath;
	};
}

