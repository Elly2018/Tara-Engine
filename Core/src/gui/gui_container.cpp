#include "gui/gui_container.h"
#ifndef TARA_NO_IMGUI
#include <gui/gui_lowlevel.h>
#include <components/camera.h>
#include <einput.h>
#endif

namespace Tara {
#ifndef TARA_NO_IMGUI
	namespace UI {
		#pragma region Gui Base Objects
		ImGui_ElementBase::ImGui_ElementBase(const char* _label)
		{
			label = label;
		}
		ImGui_ElementBase::~ImGui_ElementBase()
		{
		}
		ImGui_WindowBase::ImGui_WindowBase()
		{
		}
		ImGui_WindowBase::ImGui_WindowBase(const char* _title)
		{
			title = _title;
		}
		ImGui_WindowBase::~ImGui_WindowBase()
		{
			for (auto i = elementlist.begin(); i != elementlist.end(); i++) {
				delete* i;
			}
		}
		void ImGui_WindowBase::Render()
		{
			if (show) {
				ImGui_Begin(title.c_str(), &show);
				Content();
				ImGui_End();
			}
		}
		void ImGui_WindowBase::Content()
		{
			DefaultContent();
		}
		void ImGui_WindowBase::DefaultContent()
		{
			for (auto i = elementlist.begin(); i != elementlist.end(); i++) {
				ImGui_ElementBase* buffer = *i;
				buffer->Render();
			}
		}

		ImGui_ElementBase* ImGui_WindowBase::AddChild(ImGui_ElementBase* element)
		{
			if (element)
				elementlist.push_back(element);
			return element;
		}
		std::vector<ImGui_ElementBase*> ImGui_WindowBase::AddChildren(std::vector<ImGui_ElementBase*> elements)
		{
			for (auto i = elements.begin(); i != elements.end(); i++) {
				ImGui_ElementBase* buffer = (*i);
				if (buffer)
					elementlist.push_back(buffer);
			}
			return elements;
		}
		bool ImGui_WindowBase::RemoveChild(ImGui_ElementBase* element)
		{
			for (auto i = elementlist.begin(); i != elementlist.end(); i++) {
				ImGui_ElementBase* buffer = (*i);
				if (buffer == element) {
					elementlist.erase(i);
					return true;
				}
			}
			return false;
		}
		bool ImGui_WindowBase::RemoveChildren(std::vector<ImGui_ElementBase*> elements)
		{
			for (auto i = elements.begin(); i != elements.end(); i++) {
				ImGui_ElementBase* buffer = (*i);
				RemoveChild(buffer);
			}
			return true;
		}
		bool ImGui_WindowBase::RemoveAll()
		{
			elementlist.clear();
			return true;
		}

		void ImGui_WindowBase::Swap(int32_t index1, int32_t index2)
		{
			ImGui_ElementBase* buffer = elementlist.at(index1);
			elementlist[index1] = elementlist[index2];
			elementlist[index2] = buffer;
		}
		ImGui_ElementBase* ImGui_WindowBase::GetChild(int32_t index)
		{
			return elementlist[index];
		}
		std::vector<ImGui_ElementBase*> ImGui_WindowBase::GetChildren(int32_t index, int32_t count)
		{
			std::vector<ImGui_ElementBase*> result = std::vector<ImGui_ElementBase*>();
			for (int i = index; i < index + count; i++) {
				if (i > elementlist.size()) break;
				ImGui_ElementBase* buffer = elementlist[i];
				result.push_back(buffer);
			}
			return result;
		}
		size_t ImGui_WindowBase::Count()
		{
			return elementlist.size();
		}
		void ImGui_WindowBase::SetVisible(bool v) {
			show = v;
		}
		bool ImGui_WindowBase::Visible() {
			return show;
		}
		#pragma endregion

		#pragma region Gui Window Subclasses
		ImGui_DebugWindow::ImGui_DebugWindow() : ImGui_WindowBase("Tara Debug Info")
		{
		}
		ImGui_DebugWindow::~ImGui_DebugWindow()
		{
		}
		void ImGui_DebugWindow::Content()
		{
			DebugInfo();
		}
		void ImGui_DebugWindow::DebugInfo()
		{
			std::string t = "";
			if (ImGui_BeginTabBar("Debug Info")) {
				if (ImGui_BeginTabitems("Application", 0)) {
					t = "Tara version: 1.0";
					ImGui_Text(t.c_str());
					ImGui_EndTabitems();
				}
				if (ImGui_BeginTabitems("Input", 0)) {
					t = "time: ";
					t.append(std::to_string(EInput::Time()));
					ImGui_Text(t.c_str());

					t = "time delta: ";
					t.append(std::to_string(EInput::Delta()));
					ImGui_Text(t.c_str());

					glm::ivec2 m = EInput::GetMousePosition();
					t = "mouse: ";
					t.append(std::to_string((int)m.x));
					t.append(", " + std::to_string((int)m.y));
					ImGui_Text(t.c_str());

					m = EInput::GetMouseDelta();
					t = "mouse delta: ";
					t.append(std::to_string((int)m.x));
					t.append(", " + std::to_string((int)m.y));
					ImGui_Text(t.c_str());

					char c = EInput::GetLastChar();
					t = "last char: ";
					t += c;
					ImGui_Text(t.c_str());

					t = "log level: ";
					t.append(std::to_string(DEBUG_LEVEL));
					ImGui_Text(t.c_str());

					t = "log filename: ";
					t.append(DEBUG_FILENAME);
					ImGui_Text(t.c_str());
					ImGui_EndTabitems();
				}
				ImGui_EndTabBar();
			}
		}
		void ImGui_PopWindow::Render()
		{
			if (show) {
				ImGui_BeginPopupModal(title.c_str(), &show);
				Content();
				ImGui_EndPopup();
			}
		}

		ImGui_SceneView::ImGui_SceneView(const char* _title, const char* child_id) : ImGui_WindowBase(_title){
			m_child_id = child_id;
		}
		ImGui_SceneView::~ImGui_SceneView() {}
		ImGui_WindiwFlags& ImGui_SceneView::FrameFlags()
		{
			return m_flags;
		}
		void ImGui_SceneView::RenderCamera(CCamera* target)
		{
			// Get the child window size and position
			glm::vec2 wsize = UI::ImGui_GetWindowSize();
			glm::vec2 wpos = UI::ImGui_GetWindowPos();
			/*
				Calculate height ratio first
			*/
			// Total height will be child frame height - menubar height
			float_t frameHeight = wsize.y - 40;
			float_t heightRatio = frameHeight / m_camera->m_height;
			glm::vec2 mulSize = glm::vec2(m_camera->m_width, m_camera->m_height) * heightRatio;
			// Now we have display texture that height is match with the child window size
			// But how about the width ?
			/*
				Calculate width ratio
				Then put the dummy as padding space
			*/
			if (mulSize.x > wsize.x) {
				// The display width is bigger than child window width
				// We have to adjust display texture again
				// The same solution which we get the height match the child window size
				float_t widthRatio = wsize.x / mulSize.x;
				mulSize = mulSize * widthRatio;
				float_t heightDiff = frameHeight - mulSize.y;
				// Place padding top and bottom then we finish :D
				UI::ImGui_Dummy(0, (heightDiff / 2.f) - 25.f);
				UI::ImGui_Image(target, mulSize.x, mulSize.y);
				UI::ImGui_Dummy(0, (heightDiff / 2.f) - 25.f);
				m_leftPadding = 0;
				m_topPadding = (heightDiff / 2.f) - 25.f;
			}
			else {
				// The display width is smaller than child window width
				// Put the padding left then we finish :D
				UI::ImGui_Dummy((wsize.x - mulSize.x) / 2.f, 0);
				UI::ImGui_Sameline(0, 1);
				UI::ImGui_Image(target, mulSize.x, mulSize.y);
				m_leftPadding = (wsize.x - mulSize.x) / 2.f;
				m_topPadding = 0;
			}
		}
		void ImGui_SceneView::Content()
		{
			UI::ImGui_BeginChild(m_child_id, 0, 0, false, m_flags);
			MenuBar();
			// GUI initialization is create earlier than scene
			// So the camera will be null at first
			// Put the guard here to prevent crash
			if (!m_camera) {
				UI::ImGui_EndChild();
				return;
			}
			RenderCamera(m_camera);
			PostRender();
			UI::ImGui_EndChild();
		}
		void ImGui_SceneView::MenuBar() {}
		void ImGui_SceneView::PostRender() {}
		void ImGui_SceneView::SetCamera(CCamera* target)
		{
			m_camera = target;
		}
		CCamera* ImGui_SceneView::GetCamera()
		{
			return m_camera;
		}
		void ImGui_SceneView::SetChildFlag(ImGui_WindiwFlags flags)
		{
			m_flags = m_flags;
		}
		ImGui_WindiwFlags ImGui_SceneView::GetChildFlag()
		{
			return m_flags;
		}
		#pragma endregion

		#pragma region Gui Element Subclasses
		ImGui_TextureView::ImGui_TextureView(Texture* tex)
		{
			target = tex;
		}
		ImGui_TextureView::~ImGui_TextureView()
		{
		}
		void ImGui_TextureView::Render()
		{
			ImGui_Image((void*)target->TextureID(), glm::vec2(512, 512), glm::vec2(0));
		}
		#pragma endregion
}
#endif
}