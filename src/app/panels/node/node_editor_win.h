#pragma once
#include "engine/core/config.h"
#include "editor/editor_base.h"
#include "editor/editor_container.h"

namespace Tara {
	class TARA_APP_API Texture2D;
	namespace UI {

		enum class TARA_APP_API NodeEditorType {
			RenderView,
			Shader,
			Component
		};

		class TARA_APP_API NodeEditorWindow : public ImGui_WindowBase {
		public:
			NodeEditorWindow();
			void Content() override;

		private:
			std::vector<Node> m_Nodes = std::vector<Node>();
			std::vector<Link> m_Links = std::vector<Link>();

			Texture2D* m_HeaderBackground = nullptr;
			Texture2D* m_SaveIcon = nullptr;
			Texture2D* m_RestoreIcon = nullptr;
		};
	}
}