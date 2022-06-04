#include "project.h"
#include "../../engine/core/utility.h"
#include <fstream>
#include <nlohmann/json.hpp>

namespace Tara {
	TaraProject* TaraProject::m_Singleton = nullptr;

	TaraProject& TaraProject::Singleton()
	{
		if (!m_Singleton)m_Singleton = new TaraProject();
		return *m_Singleton;
	}
	bool TaraProject::CreateProject(std::string name, std::filesystem::path path)
	{
		if (!std::filesystem::exists(path)) {
			return false;
		}

		// TODO: create project structure
		path = path.append(name + ".tara");
		return OpenProject(path);
	}
	bool TaraProject::OpenProject(std::filesystem::path path)
	{
		if (!std::filesystem::exists(path)) {
			return false;
		}
		if (!Vaild(path)) {
			return false;
		}
		m_ProjectPath = path;
		LoadProject();
	}
	bool TaraProject::HaveProject()
	{
		return IsProjectLoad;
	}
	void TaraProject::SetProjectSetupRequirement(bool b)
	{
		IsProjectSetupRequire = b;
	}
	bool TaraProject::RequireProject()
	{
		return IsProjectSetupRequire;
	}
	bool TaraProject::Vaild(std::filesystem::path path)
	{
		if (!(path.extension().string() == ".tara")) return false;
		return true;
	}
	bool TaraProject::LoadProject()
	{
		return false;
	}
}
