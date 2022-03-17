#pragma once
#include "../../engine/core/config.h"
#include "../editor_flags.h"
#include "editor_component.h"
#include "../../engine/component/mesh_renderer.h"

namespace Tara {
	namespace UI {
		struct TARA_API ImGui_WindiwFlags;

		class TARA_API MeshRendererEditor : public EditorComponent<MeshRendererComponent> {
		public:
			MeshRendererEditor();
			void GUI() override;

		private:
			std::string m_Search = "";
			ImGui_WindiwFlags popupFlags;
		};
	}
}