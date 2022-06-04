#pragma once
#include "../../editor/editor_base.h"
#include "../../editor/editor_container.h"

namespace Tara {
	class Texture2D;
	namespace UI {

		enum class NodeEditorType {
			RenderView,
			Shader,
			Component
		};

		class NodeEditorWindow : public ImGui_WindowBase {
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