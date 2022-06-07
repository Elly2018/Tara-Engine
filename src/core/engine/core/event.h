#pragma once
// Include std library
#include <map>
#include <functional>

// Include tara library
#include "config.h"

namespace Tara {
	class TARA_API Scene;
	class TARA_API SceneObject;
	class TARA_API Component;

	template<typename T>
	class EventBase {
	public:
		EventBase() {
			events = std::map<int32_t, T>();
		}
		virtual ~EventBase() {}
		int32_t Add(int32_t priority, T t) {
			int32_t index = GetLastIndex(priority);
			events[index] = t;
			return index;
		}
		int32_t Add(T t) {
			int32_t index = GetLastIndex(0);
			events[index] = t;
			return index;
		}
		void Remove(int32_t priority) {
			if(events.count(priority))
				events.erase(events.find(priority));
		}
		void Clean() {
			events = std::map<int32_t, T>();
		}
		typename std::map<int32_t, T>::const_iterator begin() {
			return events.begin();
		}
		typename std::map<int32_t, T>::const_iterator end() {
			return events.end();
		}
	private:
		int32_t GetLastIndex(int32_t p) {
			while (events.count(p)) {
				p++;
			}
			return p;
		}
		std::map<int32_t, T> events;
	};

	class TARA_API TaraEvent {
		friend class Scene;
		friend class SceneObject;
		friend class Component;
	public:
		TaraEvent();
		~TaraEvent();
		static TaraEvent& Singleton();
		EventBase<std::function<void(Scene*)>> SceneCreateEvent;
		EventBase<std::function<void(SceneObject*)>> SceneObjectCreateEvent;
		EventBase<std::function<void(Component*)>> ComponentCreateEvent;
		EventBase<std::function<void(Scene*)>> SceneDestroyEvent;
		EventBase<std::function<void(SceneObject*)>> SceneObjectDestroyEvent;
		EventBase<std::function<void(Component*)>> ComponentDestroyEvent;

	private:
		static TaraEvent* m_Singleton;
		void OnSceneCreate(Scene* target);
		void OnSceneObjectCreate(SceneObject* target);
		void OnComponentCreate(Component* target);
		void OnSceneDestroy(Scene* target);
		void OnSceneObjectDestroy(SceneObject* target);
		void OnComponentDestroy(Component* target);
	};
}