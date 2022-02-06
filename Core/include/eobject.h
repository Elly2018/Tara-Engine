#pragma once
#include <vector>
#include <string.h>
#include <config.h>
#include <asset.h>
#include <EComponent.h>

namespace Tara {
	/*

		Structs, classes declaration

	*/
	class DllExport Scene;
	class DllExport EObject;

	/*
		Summary:
			An entity in scene, object contains name, tag, components.
	*/
	class EObject : public ObjectBase
	{
	public:
		friend class Scene;
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

		class DllExport OFViewer {
		public:
			/*
				Summary:
					Get a free camera EObject.
			*/
			static EObject* CreateFreeCamera();
			static EObject* CreateCamera();
		};
		class DllExport OF3D {
			static EObject* CreateMesh(CommomMesh mesh);
			static EObject* CreateMeshWithPhysics(CommomMesh mesh);
		};
		class DllExport OF2D {
			static EObject* CreateSprite();
			static EObject* CreateSpriteWithPhysics();
		};
		class DllExport OFSystem {
			static EObject* CreatePostProcessSystem();
			static EObject* CreateVoxelSystem();
		};
		class DllExport OFUI {
			
		};
		class DllExport OFParticle {
			static EObject* CreateDefaultParticleSystem();
			static EObject* CreateGPUParticleSystem();
		};
	};
}
