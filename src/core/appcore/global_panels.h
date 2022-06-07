#pragma once
#include "engine/core/config.h"
#include "editor/editor_container.h"
#include "engine/core/config.h"

namespace Tara {
	/*
		Application use global panels collection
	*/
	class TARA_APP_API GlobalPanels final {
	public:
		GlobalPanels();
		~GlobalPanels();

		bool AddPanel(const std::string& key, UI::ImGui_WindowBase* panel);
		std::vector<UI::ImGui_WindowBase*> GetPanels();
		UI::ImGui_WindowBase* GetPanel(const std::string& key);
		template<typename T>
		inline T* GetPanel(const std::string& key) {
			if (panels.count(key)) {
				return dynamic_cast<T*>(panels.at(key).get());
			}
			return NULL;
		}
		void CleanPanels();

		static GlobalPanels& Singleton();

	private:
		std::map<std::string, std::shared_ptr<UI::ImGui_WindowBase>> panels;
		static GlobalPanels* m_Singleton;
	};
}