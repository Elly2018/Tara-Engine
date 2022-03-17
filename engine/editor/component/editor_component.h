#pragma once
#include <map>
#include "../../engine/core/config.h"
#include "../../engine/core/scene_object/scene_object.h"

namespace Tara {
	class TARA_API SceneObject;
	class TARA_API Component;

	namespace UI {
		class TARA_API EditorComponentBase;
		template<typename T> class TARA_API EditorComponent;

		class TARA_API EditorComponentManager {
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

		class TARA_API EditorComponentBase {
		public:
			virtual void GUI() = 0;
			virtual std::string TypeID() = 0;
			virtual void SetComponent(Component* t) = 0;
			virtual std::string MenuName() { return TypeID(); }
			virtual std::string MenuPath() { return ""; }
			virtual void ApplyComponent(SceneObject* so) = 0;
		};

		template<typename T>
		class TARA_API EditorComponent : public EditorComponentBase {
		public:
			void SetComponent(T* t);
			void SetComponent(Component* t) override;
			std::string TypeID() override;
			void ApplyComponent(SceneObject* so) override;
		protected:
			T* m_comp = nullptr;
		};


		inline TARA_API EditorComponentManager* EditorComponentManager::m_Singleton = new EditorComponentManager();
		template<typename T>
		typename EditorComponent<T>* EditorComponentManager::GetEditor()
		{
			if (m_comp.count(typeid(T).name())) {
				return dynamic_cast<EditorComponent<T>*>(m_comp.at(typeid(T).name()));
			}
			return nullptr;
		}

		template<typename T>
		void EditorComponent<T>::SetComponent(T* t)
		{
			m_comp = t;
		}
		template<typename T>
		void EditorComponent<T>::SetComponent(Component* t)
		{
			if (TypeID() == typeid(*t).name()) {
				m_comp = (T*)t;
			}
		}

		template<typename T>
		std::string EditorComponent<T>::TypeID()
		{
			return typeid(T).name();
		}

		template<typename T>
		inline void EditorComponent<T>::ApplyComponent(SceneObject* so)
		{
			so->AddComponent<T>();
		}
	}
}