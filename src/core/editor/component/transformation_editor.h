#pragma once
#include "../editor_config.h"
#include "editor_component.h"
#include "../../engine/component/transformation.h"

namespace Tara {
	namespace UI {
		class TARA_EDITOR_API TransformationEditor : public EditorComponent<TransformationComponent> {
		public:
			void GUI() override;
		};
	}
}