#pragma once
#include <vector>
#include <config.h>
#include <asset.h>
#include <shader.h>
#include <eobject.h>
#include <components/camera.h>

namespace Tara {
	/*

		Structs, classes declaration

	*/
	struct DllExport Scene;

	/*
		Summary:
			Get current active scene.
	*/
	DllExport Scene* CurrentScene();
	/*
		Summary:
			Set current active scene.
	*/
	DllExport void SetActiveScene(Scene* target);

	/*
		Summary:
			A container for stores objects and components.
	*/
	struct Scene : public AssetBase
	{
		friend class EObject;
		friend class EWindow;
	public:
		Scene();
		~Scene();

		static Scene* GetDefaultScene();
		/*
			Summary:
				Get asset pool
		*/
		static AssetPool<Shader> GetAssetPool();

		/*
			Summary:
				Delete all objects in scene.
		*/
		void Clean();
		/*
			Summary:
				Use depth first search to find first object with matches name.
		*/
		EObject* FindObjectByName(const char* name);
		/*
			Summary:
				Use depth first search to collects all objects with matches name.
		*/
		std::vector<EObject*> FindObjectsByName(const char* name);
		/*
			Summary:
				Use depth first search to find first object with matches tag.
		*/
		EObject* FindObjectByTag(const char* tag);
		/*
			Summary:
				Use depth first search to collects all objects with matches tag.
		*/
		std::vector<EObject*> FindObjectsByTag(const char* tag);

		size_t TopLayerCount();
		/*
			Summary:
				Check how many instances of EObject in scene.
		*/
		size_t Count();
		EObject* GetChild(int32_t index);

	protected:
		/*
			Summary:
				Scene update, call update method for all EObjects.
		*/
		virtual void Update();
		/*
			Summary:
				Scene update, call render method for all EObjects.
		*/
		virtual void Render();

	private:
		/*
			Summary:
				Normally user shouldn't call this method, user should set the active scene and create object instead.
		*/
		void AddObject(EObject* target);
		void RemoveObject(EObject* target);
		// Primary camera for rendering.
		Tara::CCamera* m_MainCamera = nullptr;
		// Scene objects top leaf.
		std::vector<EObject*> Objects = std::vector<EObject*>();
		static AssetPool<Scene> m_scenePool;
	private:
		/*
			Summary:
				Utility method for 'find_component_by_type'
		*/
		template<typename T> EObject* FindComponentByTypeHelper(EObject* t) {
			int32_t count = t->Count();
			for (int32_t i = 0; i < count; i++) {
				EObject* o = t->GetChild(i);
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
		template<typename T> void FindComponentsByTypeHelper(EObject* t, std::vector<T*>& r) {
			int32_t count = t->Count();
			for (int32_t i = 0; i < count; i++) {
				EObject* o = t->GetChild(i);
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
		size_t ObjectsCountHelper(EObject* t);
	public:
		/*
			Summary:
				Use depth first search to find first object which contain target component.
		*/
		template<typename T> T* FindComponentByType() {
			static_assert(std::is_base_of<EComponent, T>::value, " 'find_component_by_type' trying to cast an not component type ");
			for (EObject* o : Objects) {
				EObject* r = FindComponentByTypeHelper<T>(o);
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
			for (EObject* o : Objects) {
				std::vector<T*> buffer = o->GetRelateComponents<T>();
				result.insert(result.end(), buffer.begin(), buffer.end());
				FindComponentsByTypeHelper<T>(o, result);
			}
			return result;
		};
	};
}
