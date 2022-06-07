#include "global_panels.h"

namespace Tara {
	GlobalPanels* GlobalPanels::m_Singleton = NULL;

	GlobalPanels::GlobalPanels()
	{
		panels = std::map<std::string, std::shared_ptr<UI::ImGui_WindowBase>>();
	}
	GlobalPanels::~GlobalPanels()
	{
		CleanPanels();
	}
	
	bool GlobalPanels::AddPanel(const std::string& key, UI::ImGui_WindowBase* panel)
	{
		if (panels.count(key)) {
			return false;
		}
		panels.emplace(key, panel);
	}
	std::vector<UI::ImGui_WindowBase*> GlobalPanels::GetPanels()
	{
		std::vector<UI::ImGui_WindowBase*> r = std::vector<UI::ImGui_WindowBase*>();
		for (auto i : panels) r.push_back(i.second.get());
		return r;
	}
	UI::ImGui_WindowBase* GlobalPanels::GetPanel(const std::string& key)
	{
		if (panels.count(key)) {
			return panels.at(key).get();
		}
		return NULL;
	}
	void GlobalPanels::CleanPanels()
	{
		for (auto& i : panels) i.second.reset();
		panels.clear();
	}


	GlobalPanels& GlobalPanels::Singleton()
	{
		if (m_Singleton == NULL) m_Singleton = new GlobalPanels();
		return *m_Singleton;
	}
}
