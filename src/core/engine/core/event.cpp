#include "event.h"
#include <map>
#include "scene/scene.h"
#include "../component/component.h"
#include "scene_object/scene_object.h"

namespace Tara {
	TaraEvent* TaraEvent::m_Singleton = new TaraEvent();

	TaraEvent::TaraEvent()
	{
		SceneCreateEvent = EventBase<std::function<void(Scene*)>>();
		SceneObjectCreateEvent = EventBase<std::function<void(SceneObject*)>>();
		ComponentCreateEvent = EventBase<std::function<void(Component*)>>();
		SceneDestroyEvent = EventBase<std::function<void(Scene*)>>();
		SceneObjectDestroyEvent = EventBase<std::function<void(SceneObject*)>>();
		ComponentDestroyEvent = EventBase<std::function<void(Component*)>>();
	}

	TaraEvent::~TaraEvent()
	{
	}

	TaraEvent& TaraEvent::Singleton()
	{
		return *m_Singleton;
	}

	void TaraEvent::OnSceneCreate(Scene* target)
	{
		for (auto i : SceneCreateEvent) {
			i.second(target);
		}
	}
	void TaraEvent::OnSceneObjectCreate(SceneObject* target)
	{
		for (auto i : SceneObjectCreateEvent) {
			i.second(target);
		}
	}
	void TaraEvent::OnComponentCreate(Component* target)
	{
		for (auto i : ComponentCreateEvent) {
			i.second(target);
		}
	}
	void TaraEvent::OnSceneDestroy(Scene* target)
	{
		for (auto i : SceneDestroyEvent) {
			i.second(target);
		}
	}
	void TaraEvent::OnSceneObjectDestroy(SceneObject* target)
	{
		for (auto i : SceneObjectDestroyEvent) {
			i.second(target);
		}
	}
	void TaraEvent::OnComponentDestroy(Component* target)
	{
		for (auto i : ComponentDestroyEvent) {
			i.second(target);
		}
	}
}
