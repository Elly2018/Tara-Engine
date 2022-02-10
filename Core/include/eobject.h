#pragma once
#include <vector>
#include <string.h>
#include <config.h>
#include <asset.h>
#include <mesh.h>
#include <components/component.h>

namespace Tara {
	// Prevent include loop.
	class DllExport Scene;
	/*
		Summary:
			An entity in scene, object contains name, tag, components.
	*/
	class EObject : public ObjectBase
	{
	public:
		friend class Scene;
		friend class Renderer;
		EObject();
		~EObject();

		/*
			Summary:
				Set parent EObject, if input is null, then it will apply to host scene.
		*/
		bool SetParent(EObject* target);
		/*
			Summary:
				Return parent EObject.
		*/
		EObject* Parent();
		Scene* HostScene();
		/*
			Summary:
				Get child EObject by index.
		*/
		EObject* GetChild(int32_t index);
		/*
			Summary:
				Add child under EObject.
		*/
		bool AddChild(EObject* target);
		bool RemoveChild(EObject* target);
		bool RemoveChild(int32_t index);
		/*
			Summary:
				Get child count.
		*/
		size_t Count();

		void SetEnable(bool enable);
		bool GetEnable();
		

	private:
		void Init();
		void Start();
		void Render();

#ifndef TARA_NO_IMGUI
		void Gizmo();
#endif // !TARA_NO_IMGUI

		void Update();
		void Destroy();

		void Enable();
		void Disable();

		bool m_init = false;
		bool m_enable = true;
		std::string m_tag = "";
		int32_t m_layer = 0;
		EObject* m_parent = nullptr;
		Scene* m_hostScene = nullptr;
		std::vector<EObject*> m_children = std::vector<EObject*>();
		std::vector<EComponent*> m_components = std::vector<EComponent*>();

	public:
		/*
			Summary:
				Apply component to EObject.
		*/
		template<typename T> T* AddComponent() {
			static_assert(std::is_base_of<Tara::EComponent, T>::value, "type cast error");
			T* instance = new T(this);
			m_components.push_back(instance);
			return instance;
		};
		/*
			Summary:
				Get component by type.
		*/
		template<typename T> T* GetRelateComponent() {
			static_assert(std::is_base_of<Tara::EComponent, T>::value, "type cast error");
			for (Tara::EComponent* i : m_components) {
				T* e = dynamic_cast<T*>(i);
				if (e != nullptr) {
					return (T*)i;
				}
			}
			return nullptr;
		}
		/*
			Summary:
				Collect components by type.
		*/
		template<typename T> std::vector<T*> GetRelateComponents() {
			static_assert(std::is_base_of<Tara::EComponent, T>::value, "type cast error");
			std::vector<T*> result = std::vector<T*>();
			for (Tara::EComponent* i : m_components) {
				T* e = dynamic_cast<T*>(i);
				if (e != nullptr) {
					result.push_back((T*)i);
				}
			}
			return result;
		}
	};

	class DllExport ObjectFactory {
	public:
		static EObject* CreateEmpty();
		/*
			Summary:
				Get a standard actor EObject.
		*/
		static EObject* CreateActor();
		/*
			Summary:
				Get a standard pawn EObject.
		*/
		static EObject* CreatePawn();
	};

	class DllExport ObjectFactoryViewer {
	public:
		/*
			Summary:
				Get a free camera EObject.
		*/
		static EObject* CreateFreeCamera();
		static EObject* CreateCamera();
	};
	class DllExport ObjectFactory3D {
	public:
		static EObject* CreateMesh(CommomMesh mesh);
		static EObject* CreateMeshWithPhysics(CommomMesh mesh);
	};
	class DllExport ObjectFactory2D {
	public:
		static EObject* CreateSprite();
		static EObject* CreateSpriteWithPhysics();
	};
	class DllExport ObjectFactorySystem {
	public:
		static EObject* CreatePostProcessSystem();
		static EObject* CreateVoxelSystem();
	};
	class DllExport ObjectFactoryUI {
	public:
	};
	class DllExport ObjectFactoryParticle {
	public:
		static EObject* CreateDefaultParticleSystem();
		static EObject* CreateGPUParticleSystem();
	};
}
