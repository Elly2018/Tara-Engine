#include "scene.h"
#include "../scene_object/scene_object.h"

namespace Tara {
	Scene* current = nullptr;
	AssetPool<Scene>* Scene::m_scenePool = new AssetPool<Scene>();

	Scene* CurrentScene()
	{
		return current;
	}
	void SetActiveScene(Scene* target)
	{
		current = target;
	}

	Scene::Scene()
	{
		TARA_DEBUG_LEVEL("Create scene", 2);
		Objects = std::vector<SceneObject*>();
		if (current == nullptr) current = this;
	}
	Scene::~Scene()
	{
		TARA_DEBUG_LEVEL("Scene destroy! %s", 2, Name.c_str());
		Clean();
	}

	Scene* Scene::GetDefaultScene()
	{
		return nullptr;
	}

	AssetPool<Scene>& Scene::GetAssetPool()
	{
		return *m_scenePool;
	}

	void Scene::Clean()
	{
		for (SceneObject* i : Objects) {
			delete i;
		}
	}
	SceneObject* Scene::FindObjectByName(const char* name)
	{
		return nullptr;
	}
	std::vector<SceneObject*> Scene::FindObjectsByName(const char* name)
	{
		return std::vector<SceneObject*>();
	}
	SceneObject* Scene::FindObjectByTag(const char* tag)
	{
		return nullptr;
	}
	std::vector<SceneObject*> Scene::FindObjectsByTag(const char* tag)
	{
		return std::vector<SceneObject*>();
	}

	size_t Scene::TopLayerCount() {
		Objects.erase(std::remove(Objects.begin(), Objects.end(), nullptr), Objects.end());
		size_t count = 0;
		for (SceneObject* i : Objects) {
			count++;
		}
		return count;
	}
	size_t Scene::Count()
	{
		size_t count = 0;
		for (SceneObject* i : Objects) {
			count++;
			if (i->Count() > 0) {
				count += ObjectsCountHelper(i);
			}
		}
		return count;
	}
	SceneObject* Scene::GetChild(int32_t index) {
		Objects.erase(std::find(Objects.begin(), Objects.end(), nullptr), Objects.end());
		if (index >= Objects.size() || index < 0) return nullptr;
		return Objects.at(index);
	}
	void Scene::Update()
	{
		for (SceneObject* i : Objects) {
			if(i) i->Update();
		}
	}

	void Scene::AddObject(SceneObject* target)
	{
		Objects.push_back(target);
	}
	void Scene::RemoveObject(SceneObject* target)
	{
		Objects.erase(std::remove_if(Objects.begin(), Objects.end(), [&](SceneObject* c) -> bool { return c == target; }), Objects.end());
	}
	size_t Scene::ObjectsCountHelper(SceneObject* t)
	{
		size_t count = 0;
		for (SceneObject* i : t->m_children) {
			count++;
			if (i->Count() > 0) {
				count += ObjectsCountHelper(i);
			}
		}
		return count;
	}
}