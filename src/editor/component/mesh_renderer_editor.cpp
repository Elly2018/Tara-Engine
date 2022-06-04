#include "mesh_renderer_editor.h"
#include "../editor_lowlevel.h"
#include "../asset/filebase.h"
#include <glm/glm.hpp>

namespace Tara {
	namespace UI {
		MeshRendererEditor::MeshRendererEditor()
		{
			popupFlags = ImGui_WindiwFlags();
			popupFlags.NoMove = true;
			popupFlags.NoDecoration = true;
			popupFlags.UnSave = true;
		}
		void MeshRendererEditor::GUI()
		{
			using namespace FileSystem;
			Material* mat = m_comp->GetMaterial();
			Mesh* mes = m_comp->GetMesh();

			bool popupMatSelect = false;
			bool popupMeshSelect = false;

			FileType type = FileType::Material;

			if (ImGui_MaterialField("Material", mat)) {
				popupMatSelect = true;
			}
			if (ImGui_MeshField("Mesh", mes)) {
				popupMeshSelect = true;
			}

			if (popupMatSelect) {
				ImGui_OpenPopup("Menu##AssetSelect");
				m_Search = "";
				type = FileType::Material;
			}
			else if (popupMeshSelect) {
				ImGui_OpenPopup("Menu##AssetSelect");
				m_Search = "";
				type = FileType::Mesh;
			}

			if (ImGui_BeginPopup("Menu##AssetSelect", popupFlags)) {
				FileDataBase& fdb = FileDataBase::Singleton();

				ImGui_Text("TODO");

				ImGui_EndPopup();
			}
		}
	}
}
