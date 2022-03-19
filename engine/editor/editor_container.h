#pragma once
#include <vector>
#include <string>
#include "editor_config.h"
#include "editor_flags.h"

/*
	Gui classes are just organize the gui functional call to object oriented style,
	Where you can adding element to the parent window and remove it etc...
*/
namespace Tara {
	class TARA_API CameraComponent;
	class TARA_API Texture;

	namespace UI {
		/*
			Summary:
				The gui object base class
		*/
		class TARA_EDITOR_API ImGui_UIBase {
		public:
			virtual void Render() {}
		};

		/*
			Summary:
				The gui element base class
		*/
		class TARA_EDITOR_API ImGui_ElementBase : public ImGui_UIBase {
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
		class TARA_EDITOR_API ImGui_WindowBase : public ImGui_UIBase {
		public:
			ImGui_WindowBase();
			ImGui_WindowBase(const char* _title);
			~ImGui_WindowBase();
			virtual void Start() {}
			virtual void Content();
			void Render() override;
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
			ImGui_WindiwFlags flag = ImGui_WindiwFlags();

		private:
			std::vector<ImGui_ElementBase*> elementlist = std::vector<ImGui_ElementBase*>();
		};

		class TARA_EDITOR_API ImGui_PopWindow : public ImGui_WindowBase {
		public:
			ImGui_PopWindow() : ImGui_WindowBase() {
				SetVisible(false);
			}
			ImGui_PopWindow(const char* _title) : ImGui_WindowBase(_title) {
				SetVisible(false);
			}
			void Render() override;
		protected:
			ImGui_PopupFlags pflags = ImGui_PopupFlags();
		};

		class TARA_EDITOR_API ImGui_SceneView : public ImGui_WindowBase {
		public:
			ImGui_SceneView(const char* _title, const char* child_id);
			~ImGui_SceneView();
			ImGui_WindiwFlags& FrameFlags();
			void RenderCamera(CameraComponent* target);
			void Content() override;
			virtual void MenuBar();
			virtual void PostRender();
			void SetCamera(CameraComponent* target);
			CameraComponent* GetCamera();
			void SetChildFlag(ImGui_WindiwFlags flags);
			ImGui_WindiwFlags GetChildFlag();

		protected:
			const char* m_child_id;
			CameraComponent* m_camera = nullptr;
			float_t m_leftPadding = 0;
			float_t m_topPadding = 0;

		private:
			ImGui_WindiwFlags m_flags = ImGui_WindiwFlags();
		};

		/*
			Summary:
				Render a texture viewer that can use apply different effect on it.
				RGBA filter, information at bottom, brightness.
		*/
		class TARA_EDITOR_API ImGui_TextureView : public ImGui_ElementBase {
		public:
			ImGui_TextureView(Texture* tex);
			~ImGui_TextureView();
			void Render() override;
		private:
			Texture* target;
		};
	}
}