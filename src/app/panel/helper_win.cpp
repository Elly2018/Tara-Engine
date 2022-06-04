#include "helper_win.h"
#include "../../editor/editor_lowlevel.h"

namespace Tara {
	namespace UI {
		void HelperWindow::Content() {
			std::string text = "# H1 header\n ## H2 ssss\n H3 YoYo\n * Hello world\n* [link description](https://...)";
			UI::ImGui_Markdown(text);
		}
	}
}