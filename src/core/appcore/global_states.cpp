#include "global_states.h"
#include "engine/core/scene/scene.h"
#include "engine/core/asset.h"
#include "engine/component/camera.h"
#include "engine/core/scene_object/scene_object.h"
#include "engine/core/renderer/renderer.h"

namespace Tara {
	namespace Global {
		GlobalStatePackage* GlobalStatePackage::m_Singleton = NULL;

		GlobalStatePackage::GlobalStatePackage()
		{
			scenes = GlobalStatesArray<Scene*>();
			state_bool = GlobalStates<bool>();
			state_int = GlobalStates<int32_t>();
			state_float = GlobalStates<float_t>();
			state_camera = GlobalStates<CameraComponent*>();
			state_objectBase = GlobalStates<ObjectBase*>();
			state_sceneObject = GlobalStates<SceneObject*>();
			state_renderState = GlobalStates<RenderState>();
		}
		GlobalStatePackage::~GlobalStatePackage()
		{
			// // O: insert return statement here
		}
		GlobalStatePackage& GlobalStatePackage::Singleton()
		{
			if (m_Singleton == NULL) m_Singleton = new GlobalStatePackage();
			return *m_Singleton;
		}
	}
}
