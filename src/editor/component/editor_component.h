#pragma once
#include <map>
#include "../editor_config.h"
#include "../../engine/core/scene_object/scene_object.h"

namespace Tara {
	class TARA_API SceneObject;
	class TARA_API Component;

	namespace UI {
		class TARA_EDITOR_API EditorComponentBase;
		template<typename T> class TARA_EDITOR_API EditorComponent;

		class TARA_EDITOR_API EditorComponentManager {
		public:
			static EditorComponentManager& Singleton();
			void NewEObjectCreate(SceneObject* target);
			void NewEObjectDestroy(SceneObject* target);
			void NewEComponentCreate(Component* target);
			void NewEComponentDestroy(Component* target);

			template<typename T> typename EditorComponent<T>* GetEditor();
			EditorComponentBase* GetEditor(Component* comp);
			std::vector<std::pair<std::string, EditorComponentBase*>> GetComponents(std::string path);

		private:
			EditorComponentManager();

			static EditorComponentManager* m_Singleton;
			std::map<std::string, EditorComponentBase*> m_comp = std::map<std::string, EditorComponentBase*>();
		};

		class EditorComponentBase {
		public:
			virtual void GUI() = 0;
			virtual void DebugGUI() {
				GUI();
			}
			virtual std::string TypeID() = 0;
			virtual void SetComponent(Component* t) = 0;
			virtual std::string MenuName() { return TypeID(); }
			virtual std::string MenuPath() { return ""; }
			virtual void ApplyComponent(SceneObject* so) = 0;
		};

		template<typename T>
		class EditorComponent : public EditorComponentBase {
		public:
			void SetComponent(T* t)
			{
				m_comp = t;
			}

			void SetComponent(Component* t) override
			{
				if (TypeID() == typeid(*t).name()) {
					m_comp = (T*)t;
				}
			}

			std::string TypeID() override
			{
				return typeid(T).name();
			}

			void ApplyComponent(SceneObject* so) override
			{
				so->AddComponent<T>();
			}
		protected:
			T* m_comp = nullptr;
		};


		template<typename T>
		typename EditorComponent<T>* EditorComponentManager::GetEditor()
		{
			if (m_comp.count(typeid(T).name())) {
				return dynamic_cast<EditorComponent<T>*>(m_comp.at(typeid(T).name()));
			}
			return nullptr;
		}
	}
}