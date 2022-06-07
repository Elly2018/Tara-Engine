#pragma once
// Include std library
#include <vector>
#include <memory>
#include <string.h>

// Include tara library
#include "../config.h"
#include "../asset.h"
#include "../base.h"

namespace Tara {
	/*
		Structures and classes
	*/
	class TARA_API Mesh;
	class TARA_API Material;
	class TARA_API Scene;
	class TARA_API Component;

	/*
		Summary:
			An entity in scene, object contains name, tag, components.
	*/
	struct TARA_API SceneObject final : public ObjectBase, public TaraObjectEventBase {
	public:
		friend class Scene;
		friend class Renderer;
		SceneObject();
		~SceneObject();

		/*
			Summary:
				Set parent EObject, if input is null, then it will apply to host scene.
		*/
		bool SetParent(SceneObject* target);
		/*
			Summary:
				Return parent EObject.
		*/
		SceneObject* Parent();
		Scene* HostScene();
		/*
			Summary:
				Get child EObject by index.
		*/
		SceneObject* GetChild(int32_t index);
		/*
			Summary:
				Add child under EObject.
		*/
		bool AddChild(SceneObject* target);
		bool RemoveChild(SceneObject* target);
		bool RemoveChild(int32_t index);
		/*
			Summary:
				Get child count.
		*/
		size_t Count();

		void SetEnable(bool enable);
		bool GetEnable();
		

	protected:
		void Init() override;
		void Start() override;
		void Update() override;
		void Destroy() override;
		void Enable() override;
		void Disable() override;

	private:
		bool m_init;
		bool m_enable;
		std::string m_tag;
		int32_t m_layer = 0;
		SceneObject* m_parent;
		Scene* m_hostScene;
		std::vector<SceneObject*> m_children;
		std::vector<Component*> m_components;
	public:
		/*
			Summary:
				Apply component to EObject.
		*/
		template<typename T> T* AddComponent() {
			static_assert(std::is_base_of<Component, T>::value, "type cast error");
			T* instance = new T(this);
			m_components.push_back(instance);
			return instance;
		};
		/*
			Summary:
				Get component by type.
		*/
		template<typename T> T* GetRelateComponent() {
			static_assert(std::is_base_of<Component, T>::value, "type cast error");
			for (Component* i : m_components) {
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
			static_assert(std::is_base_of<Component, T>::value, "type cast error");
			std::vector<T*> result = std::vector<T*>();
			for (Component* i : m_components) {
				T* e = dynamic_cast<T*>(i);
				if (e != nullptr) {
					result.push_back((T*)i);
				}
			}
			return result;
		}
	};

	class TARA_API ObjectFactoryViewer {
	public:
		ObjectFactoryViewer(){}
		/*
			Summary:
				Get a free camera EObject.
		*/
		static SceneObject* CreateFreeCamera();
		static SceneObject* CreateCamera();
	};

	class TARA_API ObjectFactory3D {
	public:
		ObjectFactory3D() {}
		SceneObject* CreateMesh(Mesh* mesh = nullptr, Material* = nullptr);
		SceneObject* CreateMeshWithPhysics(Mesh* mesh = nullptr, Material* = nullptr);
	};

	class TARA_API ObjectFactoryLight {
	public:
		ObjectFactoryLight() {}
		SceneObject* CreateDirection();
		SceneObject* CreatePointLight();
		SceneObject* CreateSpotLight();
	};

	class TARA_API ObjectFactory2D {
	public:
		ObjectFactory2D() {}
		SceneObject* CreateSprite();
		SceneObject* CreateSpriteWithPhysics();
	};

	class TARA_API ObjectFactorySystem {
	public:
		ObjectFactorySystem() {}
		SceneObject* CreatePostProcessSystem();
		SceneObject* CreateVoxelSystem();
	};

	class TARA_API ObjectFactoryUI {
	public:
		ObjectFactoryUI() {}
		SceneObject* CreateCanvas();
	};

	class TARA_API ObjectFactoryParticle {
	public:
		ObjectFactoryParticle() {}
		SceneObject* CreateDefaultParticleSystem();
		SceneObject* CreateGPUParticleSystem();
	};

	class TARA_API ObjectFactory {
	public:
		ObjectFactory();
		~ObjectFactory();

		static ObjectFactory& Singleton();

		SceneObject* CreateEmpty();
		/*
			Summary:
				Get a standard actor EObject.
		*/
		SceneObject* CreateActor();
		/*
			Summary:
				Get a standard pawn EObject.
		*/
		SceneObject* CreatePawn();

		ObjectFactoryViewer m_Viewer;
		ObjectFactory3D m_3D;
		ObjectFactoryLight m_Lighting;
		ObjectFactory2D m_2D;
		ObjectFactorySystem m_System;
		ObjectFactoryUI m_UI;
		ObjectFactoryParticle m_Particle;

	private:
		static ObjectFactory* m_Singleton;
	};
}
