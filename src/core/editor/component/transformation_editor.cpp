#include "transformation_editor.h"
#include "../editor_lowlevel.h"
#include <glm/glm.hpp>

namespace Tara {
	namespace UI {
		void TransformationEditor::GUI()
		{
			if (!m_comp) return;
			ImGui_DragVec3("Position", &m_comp->LocalPosition(), 0.2f);
			ImGui_DragVec3("Eular Angle", &m_comp->LocalEualrAngle(), 0.2f);
			ImGui_DragVec3("Scale", &m_comp->LocalScale(), 0.2f);
			/*
			UI::ImGui_MeshField("Mesh", m_mesh);
			UI::ImGui_MaterialField("Material", m_mat);
			if (DebugMenu()) {
				UI::ImGui_BeginDisabled(true);
				if (m_mesh) {
					AABB aabb = m_mesh->GetAABB();
					UI::ImGui_LabelText("AABB center", "%f, %f, %f", &aabb.center.x, &aabb.center.y, &aabb.center.z);
					UI::ImGui_LabelText("AABB extends", "%f, %f, %f", &aabb.extents.x, &aabb.extents.y, &aabb.extents.z);
				}
				UI::ImGui_EndDisabled();
				if (UI::ImGui_Button("Print Uniform")) {
					m_mat->GetShader().PrintUniform();
				}
				if (m_mat) {
					Shader& m_shader = m_mat->GetShader();
					//auto unis = m_shader.Uniforms();
				}
			}
			*/
		}
	}
}
