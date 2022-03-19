#include "editor_component.h"
#include <map>
#include "../../engine/core/scene_object/scene_object.h"
#include "../../engine/core/utility.h"
#include "alleditor.h"

namespace Tara {
	namespace UI {
		EditorComponentManager* EditorComponentManager::m_Singleton = nullptr;

		struct EditorComponentTree {
		public:
			EditorComponentTree(std::string _name, EditorComponentTree* p = nullptr) : name(_name), par(p) {
				target = nullptr;
				child = std::vector<EditorComponentTree*>();
			}
			~EditorComponentTree() {
				for (auto i : child) {
					delete i;
				}
			}
			EditorComponentTree* GetTree(std::string c, bool add = false) {
				for (auto i : child) {
					if (i->name == c) {
						return i;
					}
				}
				if (!add) return nullptr;
				EditorComponentTree* t = new EditorComponentTree(c, this);
				child.push_back(t);
				return t;
			}
			bool Vaild() {
				for (auto i : child) {
					if (i->target) return true;
				}
				return false;
			}
			std::string name;
			EditorComponentTree* par;
			EditorComponentBase* target;
			std::vector<EditorComponentTree*> child;
		};

		EditorComponentTree* root;

		void AddToTree(EditorComponentBase* ecb) {
			if (ecb->MenuPath().size() == 0) return;
			std::vector<std::string> paths = Utility::String::Split(ecb->MenuPath(), "/");
			
			for (auto i : paths)
				TARA_DEBUG("%s", i.c_str());

			EditorComponentTree* ptr = root;
			for (auto i : paths) {
				ptr = ptr->GetTree(i.c_str(), true);
			}
			ptr->target = ecb;
		}

		void RemoveFromTree(EditorComponentBase* ecb) {
			if (ecb->MenuPath().size() == 0) return;
			std::vector<std::string> paths = Utility::String::Split(ecb->MenuPath(), "/");
			
			EditorComponentTree* ptr = root;
			for (auto i : paths) {
				ptr = ptr->GetTree(i);
				if (ptr == nullptr) return;
			}
			ptr->target = nullptr;

			while (ptr != root) {
				if (ptr->Vaild()) {
					break;
				}
				else {
					EditorComponentTree* d = ptr;
					ptr = ptr->par;

					std::remove(ptr->child.begin(), ptr->child.end(), d);
				}
			}
		}

		EditorComponentTree* GetFromPath(std::string p) {
			if (p.size() == 0) {
				return root;
			}
			else {
				std::vector<std::string> paths = Utility::String::Split(p, "/");
				EditorComponentTree* ptr = root;
				for (auto i : paths) {
					ptr = ptr->GetTree(i);
					if (ptr == nullptr) return nullptr;
				}
				return ptr;
			}
		}

		EditorComponentManager& EditorComponentManager::Singleton()
		{
			if (!m_Singleton) m_Singleton = new EditorComponentManager();
			return *m_Singleton;
		}

		void EditorComponentManager::NewEObjectCreate(SceneObject* target)
		{

		}
		void EditorComponentManager::NewEObjectDestroy(SceneObject* target)
		{

		}
		void EditorComponentManager::NewEComponentCreate(Component* target)
		{
			
		}
		void EditorComponentManager::NewEComponentDestroy(Component* target)
		{
			
		}

		EditorComponentBase* EditorComponentManager::GetEditor(Component* comp)
		{
			if (m_comp.count(typeid(*comp).name())) {
				return m_comp.at(typeid(*comp).name());
			}
			return nullptr;
		}

		std::vector<std::pair<std::string, EditorComponentBase*>> EditorComponentManager::GetComponents(std::string path)
		{
			std::vector<std::pair<std::string, EditorComponentBase*>> result = std::vector<std::pair<std::string, EditorComponentBase*>>();
			EditorComponentTree* t = GetFromPath(path);
			if (t) {
				for (auto i : t->child) {
					result.push_back({ i->name, i->target });
				}
			}
			return result;
		}

		EditorComponentManager::EditorComponentManager() 
		{
			root = new EditorComponentTree("");
			TransformationEditor* transformationEditor = new TransformationEditor();
			LightEditor* lightEditor = new LightEditor();
			MeshRendererEditor* meshRendererEditor = new MeshRendererEditor();

			m_comp[transformationEditor->TypeID()] = transformationEditor;
			m_comp[lightEditor->TypeID()] = lightEditor;
			m_comp[meshRendererEditor->TypeID()] = meshRendererEditor;

			AddToTree(lightEditor);
		}
	}
}