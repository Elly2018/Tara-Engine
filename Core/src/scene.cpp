#include "scene.h"

namespace Tara {
	Scene* current = nullptr;
	AssetPool<Scene> Scene::m_scenePool = AssetPool<Scene>();

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
		if (current == nullptr) current = this;
	}
	Scene::~Scene()
	{
		Clean();
	}

	void Scene::Clean()
	{
		for (EObject* i : Objects) {
			delete i;
		}
		Objects.clear();
	}
	EObject* Scene::FindObjectByName(const char* name)
	{
		return nullptr;
	}
	std::vector<EObject*> Scene::FindObjectsByName(const char* name)
	{
		return std::vector<EObject*>();
	}
	EObject* Scene::FindObjectByTag(const char* tag)
	{
		return nullptr;
	}
	std::vector<EObject*> Scene::FindObjectsByTag(const char* tag)
	{
		return std::vector<EObject*>();
	}

	size_t Scene::ObjectCount()
	{
		size_t count = 0;
		for (EObject* i : Objects) {
			count++;
			if (i->Count() > 0) {
				count += ObjectsCountHelper(i);
			}
		}
		return size_t();
	}
	void Scene::Update()
	{
		for (EObject* i : Objects) {
			i->Update();
		}
	}
	void Scene::Render()
	{
		// Draw on framebuffer
		for (EObject* i : Objects) {
			i->Render();
		}
	}

	void Scene::AddObject(EObject* target)
	{
		Objects.push_back(target);
	}
	size_t Scene::ObjectsCountHelper(EObject* t)
	{
		size_t count = 0;
		for (EObject* i : t->m_children) {
			count++;
			if (i->Count() > 0) {
				count += ObjectsCountHelper(i);
			}
		}
		return count;
	}
}