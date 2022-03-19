#pragma once
#include "../editor_config.h"
#include "editor_component.h"
#include "../../engine/component/light.h"

namespace Tara {
	namespace UI {
		class TARA_EDITOR_API LightEditor : public EditorComponent<LightComponent> {
		public:
			void GUI() override;
			std::string MenuPath() override { return "Render/Light"; }
		};
	}
}