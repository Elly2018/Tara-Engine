#include "light_editor.h"
#include "../editor_lowlevel.h"
#include <glm/glm.hpp>

namespace Tara {
	namespace UI {

		const std::map<LightType, const char*> lighttypestring = {
			{LightType::Direction, "Directional Light"},
			{LightType::Point, "Point Light"},
			{LightType::Spot, "Spot Light"},
		};

		void LightEditor::GUI()
		{
			if (!m_comp) return;
			
			if (ImGui_ColumnButton(lighttypestring.at(m_comp->m_type), 24, 10)) {
				ImGui_OpenPopup("LightTypeSelect");
			}
			if (ImGui_BeginPopup("LightTypeSelect")) {
				for (auto i : lighttypestring) {
					if (ImGui_Selectable(i.second, i.first == m_comp->m_type)) {
						m_comp->m_type = i.first;
						ImGui_ClosePopup();
					}
				}
				ImGui_EndPopup();
			}
			ImGui_DragFloat("Intensity", &m_comp->m_intensity, 0.05f, 0, 10000);
			ImGui_ColorEditor3("Color", &m_comp->m_color);
			ImGui_Checkbox("Important", &m_comp->m_important);
		}
	}
}
