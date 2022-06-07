#pragma once
#include <string>
#include <map>
#include "engine/core/config.h"

namespace Tara {
	class Scene;
	class CameraComponent;
	class ObjectBase;
	class SceneObject;
	class RenderState;

	/*
		Application use global panels collection
	*/
	template<typename T>
	class GlobalStates final {
	public:
		GlobalStates() {
			states = std::map<std::string, T>();
		}
		~GlobalStates() {
			states.clear();
		}

		inline bool SetState(std::string key, T state) {
			states[key] = state;
			return true;
		}
		inline T GetState(const std::string& key) {
			if (states.count(key)) {
				return states.at(key);
			}
			else {
				states[key] = NULL;
				return states.at(key);
			}
		}
		inline T GetState(const std::string& key, T _default) {
			if (states.count(key)) {
				return states.at(key);
			}
			else {
				states[key] = _default;
				return states.at(key);
			}
		}
		inline void CleanStates() {
			states.clear();
		}

	private:
		std::map<std::string, T> states;
	};


	/*
		Application use global panels collection for vector
	*/
	template<typename T>
	class GlobalStatesArray final {
	public:
		using container = std::vector<T>;
		GlobalStatesArray() {
			states = std::map<std::string, container>();
		}
		~GlobalStatesArray() {
			states.clear();
		}

		inline bool SetState(std::string key, container _states) {
			states[key] = _states;
			return true;
		}
		inline size_t Length(std::string key) {
			if (states.count(key)) {
				return states.at(key).size();
			}
			return -1;
		}
		inline container GetStates(const std::string& key) {
			if (states.count(key)) {
				return states.at(key);
			}
			else {
				states[key] = container();
				return states.at(key);
			}
		}
		inline container GetState(const std::string& key, container _default) {
			if (states.count(key)) {
				return states.at(key);
			}
			else {
				states[key] = _default;
				return states.at(key);
			}
		}
		inline T GetState(const std::string& key, int32_t index) {
			if (states.count(key)) {
				return states.at(key)[index];
			}
			else {
				return NULL;
			}
		}
		inline void CleanStates() {
			states.clear();
		}

	private:
		std::map<std::string, container> states;
	};	

	namespace Global {
		class TARA_APP_API GlobalStatePackage {
		public:
			static GlobalStatePackage& Singleton();

			GlobalStatesArray<Scene*> scenes;
			GlobalStates<bool> state_bool;
			GlobalStates<int32_t> state_int;
			GlobalStates<float_t> state_float;
			GlobalStates<CameraComponent*> state_camera;
			GlobalStates<ObjectBase*> state_objectBase;
			GlobalStates<SceneObject*> state_sceneObject;
			GlobalStates<RenderState> state_renderState;
		private:
			GlobalStatePackage();
			~GlobalStatePackage();
			static GlobalStatePackage* m_Singleton;
		};
	}
}