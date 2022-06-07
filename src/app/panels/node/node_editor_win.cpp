#include "node_editor_win.h"
#include "editor/editor_lowlevel.h"

namespace Tara {
	namespace UI {
		NodeEditorWindow::NodeEditorWindow() : ImGui_WindowBase("Node Editor")
		{
			SetVisible(false);
		}
		void NodeEditorWindow::Content()
		{

		}
	}
}