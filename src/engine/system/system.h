#pragma once
// Include std library
#include <memory>
#include <string>
#include <list>

// Import Tara engine library
#include "../core/config.h"

namespace Tara {
	class TARA_API Component;

	/*
		Summary:
			Component system base
	*/
	class TARA_API SystemBase { 
	public:
		virtual void CleanNull() = 0;
		virtual std::string TypeString() = 0;
	};


	/*
		Summary:
			Contain basic system with type functionality.
	*/
	template<typename T>
	class TARA_API System : public SystemBase {
	public:
		System() {
			static_assert(std::is_base_of<Component, T>::value, "Component system type must be base of component");
			components = std::list<T*>();
		}
		size_t Size() {
			return components.size();
		}
		void Append(T* comp) {
			components.push_back(comp);
		}
		void Remove(T* comp) {
			components.erase(std::remove(components.begin(), components.end(), comp), components.end());
		}
		void CleanNull() override {
			components.erase(std::remove(components.begin(), components.end(), nullptr), components.end());
		}
		std::string TypeString() override {
			return typeid(T).name();
		}

		using container = std::list<T>;
		using iterator = typename container::iterator;
		using const_iterator = typename container::const_iterator;

		typename std::list<T*>::iterator begin() {
			return components.begin();
		}
		typename std::list<T*>::iterator end() {
			return components.end();
		}
		typename std::list<T*>::const_iterator begin() const {
			return components.begin();
		}
		typename std::list<T*>::const_iterator end() const {
			return components.end();
		}

	protected:
		std::list<T*> components;
	};


	/*
		Summary:
			Regsiter your component system to this worker.
			So everytime component spawned, they will trying to search match system and append to it.
	*/
	class TARA_API SystemRegister {
	public:
		SystemRegister();
		static SystemRegister& Singleton();

		void Register(SystemBase* system);
		void CleanNull();

		template<typename T> System<T>* GetSystem() {
			static_assert(std::is_base_of<Component, T>::value, "Component system type must be base of component");
			for (auto i : systems) {
				if (i->TypeString() == std::string(typeid(T).name())) {
					return (System<T>*)i;
				}
			}
			return nullptr;
		}

		template<typename T> bool AppendComponent(T* comp) {
			static_assert(std::is_base_of<Component, T>::value, "Component system type must be base of component");
			System<T>* sys = GetSystem<T>();
			if (sys == nullptr) return false;
			sys->Append(comp);
			return true;
		}
		template<typename T> bool RemoveComponent(T* comp) {
			static_assert(std::is_base_of<Component, T>::value, "Component system type must be base of component");
			System<T>* sys = GetSystem<T>();
			if (sys == nullptr) return false;
			sys->Remove(comp);
			return true;
		}

	private:
		static SystemRegister* m_Singleton;

		std::list<SystemBase*> systems;
	};
}