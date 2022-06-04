#pragma once
// Import std library
#include <vector>
#include <memory>

// Import Tara engine library
#include "../config.h"
#include "../asset.h"

namespace Tara {
	/*

		Structs, classes declaration

	*/
	struct TARA_API Scene;
	struct TARA_API CameraComponent;

	/*
		Summary:
			Get current active scene.
	*/
	TARA_API Scene* CurrentScene();
	/*
		Summary:
			Set current active scene.
	*/
	TARA_API void SetActiveScene(Scene* target);

	/*
		Summary:
			A container for stores objects and components.
	*/
	class Scene final : public AssetBase
	{
		friend class SceneObject;
		friend class EWindow;
		friend class Renderer;
	public:
		Scene();
		~Scene();

		static Scene* GetDefaultScene();
		/*
			Summary:
				Get asset pool
		*/
		static AssetPool<Scene>& GetAssetPool();

		/*
			Summary:
				Delete all objects in scene.
		*/
		void Clean();
		/*
			Summary:
				Use depth first search to find first object with matches name.
		*/
		SceneObject* FindObjectByName(const char* name);
		/*
			Summary:
				Use depth first search to collects all objects with matches name.
		*/
		std::vector<SceneObject*> FindObjectsByName(const char* name);
		/*
			Summary:
				Use depth first search to find first object with matches tag.
		*/
		SceneObject* FindObjectByTag(const char* tag);
		/*
			Summary:
				Use depth first search to collects all objects with matches tag.
		*/
		std::vector<SceneObject*> FindObjectsByTag(const char* tag);

		size_t TopLayerCount();
		/*
			Summary:
				Check how many instances of SceneObject in scene.
		*/
		size_t Count();
		SceneObject* GetChild(int32_t index);

	protected:
		/*
			Summary:
				Scene update, call update method for all SceneObjects.
		*/
		void Update();

	private:
		/*
			Summary:
				Normally user shouldn't call this method, user should set the active scene and create object instead.
		*/
		void AddObject(SceneObject* target);
		void RemoveObject(SceneObject* target);
		// Primary camera for rendering.
		CameraComponent* m_MainCamera = nullptr;
		// Scene objects top leaf.
		std::vector<SceneObject*> Objects;
		static AssetPool<Scene>* m_scenePool;
	private:
		/*
			Summary:
				Utility method for 'find_component_by_type'
		*/
		template<typename T> SceneObject* FindComponentByTypeHelper(SceneObject* t) {
			int32_t count = t->Count();
			for (int32_t i = 0; i < count; i++) {
				SceneObject* o = t->GetChild(i);
				if (o == nullptr) continue;
				T* buffer = o->GetRelateComponent<T>();
				if (buffer != nullptr) {
					return buffer;
				}
				if (o->Count() > 0) {
					return FindComponentByTypeHelper<T>(o);
				}
			}
			return nullptr;
		};
		/*
			Summary:
				Utility method for 'find_components_by_type'
		*/
		template<typename T> void FindComponentsByTypeHelper(SceneObject* t, std::vector<T*>& r) {
			int32_t count = t->Count();
			for (int32_t i = 0; i < count; i++) {
				SceneObject* o = t->GetChild(i);
				if (o == nullptr) continue;
				std::vector<T*> buffer = o->GetRelateComponents<T>();
				r.insert(r.end(), buffer.begin(), buffer.end());
				if (o->Count() > 0) {
					FindComponentsByTypeHelper<T>(o, r);
				}
			}
		};
		/*
			Summary:
				Utility method for 'objects_count'
		*/
		size_t ObjectsCountHelper(SceneObject* t);
	public:
		/*
			Summary:
				Use depth first search to find first object which contain target component.
		*/
		template<typename T> T* FindComponentByType() {
			static_assert(std::is_base_of<EComponent, T>::value, " 'find_component_by_type' trying to cast an not component type ");
			for (SceneObject* o : Objects) {
				SceneObject* r = FindComponentByTypeHelper<T>(o);
				if (r != nullptr) return r;
			}
			return nullptr;
		};
		/*
			Summary:
				Use depth first search to collects all objects which contain target component.
		*/
		template<typename T> std::vector<T*> FindComponentsByType() {
			static_assert(std::is_base_of<EComponent, T>::value, " 'find_components_by_type' trying to cast an not component type ");
			std::vector<T*> result = std::vector<T*>();
			for (SceneObject* o : Objects) {
				std::vector<T*> buffer = o->GetRelateComponents<T>();
				result.insert(result.end(), buffer.begin(), buffer.end());
				FindComponentsByTypeHelper<T>(o, result);
			}
			return result;
		};
	};
}
