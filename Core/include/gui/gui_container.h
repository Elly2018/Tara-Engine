#pragma once
#include <vector>
#include <string>
#include <config.h>
#include <texture.h>
#include <gui/gui_flags.h>

/*
	Gui classes are just organize the gui functional call to object oriented style,
	Where you can adding element to the parent window and remove it etc...
*/
namespace Tara {
	#ifndef TARA_NO_IMGUI
	class DllExport CCamera;
	namespace UI {
		/*
			Summary:
				The gui object base class
		*/
		class DllExport ImGui_UIBase {
		public:
			virtual void Render() {}
		};

		/*
			Summary:
				The gui element base class
		*/
		class DllExport ImGui_ElementBase : public ImGui_UIBase {
		public:
			ImGui_ElementBase(const char* _label = "Empty");
			~ImGui_ElementBase();
		protected:
			std::string label;
		};

		/*
			Summary:
				The gui element base class.
		*/
		class DllExport ImGui_WindowBase : public ImGui_UIBase {
		public:
			ImGui_WindowBase();
			ImGui_WindowBase(const char* _title);
			~ImGui_WindowBase();
			virtual void Start() {}
			void Render() override;
			virtual void Content();
			void DefaultContent();

			ImGui_ElementBase* AddChild(ImGui_ElementBase* element);
			std::vector<ImGui_ElementBase*> AddChildren(std::vector<ImGui_ElementBase*> elements);
			bool RemoveChild(ImGui_ElementBase* element);
			bool RemoveChildren(std::vector<ImGui_ElementBase*> elements);
			bool RemoveAll();

			void Swap(int32_t index1, int32_t index2);
			ImGui_ElementBase* GetChild(int32_t index);
			std::vector<ImGui_ElementBase*> GetChildren(int32_t index, int32_t count);
			size_t Count();
			void SetVisible(bool v);
			bool Visible();

			template<typename T> T* Getchild()
			{
				static_assert(std::is_base_of<ImGui_ElementBase, T>::value, L"T must inherit from uielementbase");
				for (auto i = elementlist.begin(); i != elementlist.end(); i++) {
					if (dynamic_cast<T>(*i) != nullptr) {
						return *i;
					}
				}
				return nullptr;
			}
			template<typename T> std::vector<T*> GetChildren()
			{
				static_assert(std::is_base_of<ImGui_ElementBase, T>::value, L"T must inherit from uielementbase");
				std::vector<T*> result = std::vector<T*>();
				for (auto i = elementlist.begin(); i != elementlist.end(); i++) {
					if (dynamic_cast<T>(*i) != nullptr) {
						result.push_back(*i);
					}
				}
				return result;
			}

		protected:
			bool show = true;
			std::string title = "Default Window";

		private:
			std::vector<ImGui_ElementBase*> elementlist = std::vector<ImGui_ElementBase*>();
		};

		/*
			Summary:
				A simple window show all the application states.
		*/
		class DllExport ImGui_DebugWindow : public ImGui_WindowBase {
		public:
			ImGui_DebugWindow();
			~ImGui_DebugWindow();
			void Content() override;

		protected:
			void DebugInfo();
		};

		class DllExport ImGui_PopWindow : public ImGui_WindowBase {
		public:
			ImGui_PopWindow() : ImGui_WindowBase() {}
			ImGui_PopWindow(const char* _title) : ImGui_WindowBase(_title) {}
			void Render() override;
		};

		class DllExport ImGui_SceneView : public ImGui_WindowBase {
		public:
			ImGui_SceneView(const char* _title, const char* child_id);
			~ImGui_SceneView();
			ImGui_WindiwFlags& FrameFlags();
			void Content() override;
			virtual void MenuBar();
			virtual void PostRender();
			void SetCamera(CCamera* target);
			CCamera* GetCamera();
			void SetChildFlag(ImGui_WindiwFlags flags);
			ImGui_WindiwFlags GetChildFlag();

		protected:
			const char* m_child_id;
			CCamera* m_camera = nullptr;
			float_t m_leftPadding = 0;
			float_t m_topPadding = 0;

		private:
			ImGui_WindiwFlags m_flags = ImGui_WindiwFlags();
		};

		class DllExport ImGui_MaterialField : public ImGui_ElementBase {

		};

		class DllExport ImGui_MaterialView : public ImGui_ElementBase {

		};

		class DllExport ImGui_ShaderView : public ImGui_ElementBase {

		};

		/*
			Summary:
				Render a texture viewer that can use apply different effect on it.
				RGBA filter, information at bottom, brightness.
		*/
		class DllExport ImGui_TextureView : public ImGui_ElementBase {
		public:
			ImGui_TextureView(Texture* tex);
			~ImGui_TextureView();
			void Render() override;
		private:
			Texture* target;
		};

		/*
			Summary:
				Render a object field without the viewing object info.
				Only show the object icon and name.
		*/
		class DllExport ImGui_EObjectField : public ImGui_ElementBase {

		};

		class DllExport ImGui_EObjectHeaderView : public ImGui_ElementBase {

		};

		class DllExport ImGui_EObjectContentView : public ImGui_ElementBase {

		};
	}
	#endif
}