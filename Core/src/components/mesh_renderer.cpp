#include "components/mesh_Renderer.h"

// Include third party library
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <eobject.h>
#include <renderer.h>
#include <components/transformation.h>
#ifndef TARA_NO_IMGUI
	#include <gui/gui_lowlevel.h>
#endif

namespace Tara {
	void CMeshRenderer::GUI()
	{
#ifndef TARA_NO_IMGUI
		UI::ImGui_MeshField("Mesh", m_mesh);
		UI::ImGui_MaterialField("Material", m_mat);
		if (DebugMenu()) {
			UI::ImGui_BeginDisabled(true);
			if (m_mesh) {
				AABB aabb = m_mesh->GetAABB();
				UI::ImGui_InputVec3("AABB center", &aabb.center);
				UI::ImGui_InputVec3("AABB extends", &aabb.extents);
			}
			UI::ImGui_EndDisabled();
			if (m_mat) {
				if (UI::ImGui_Button("Print uniform")) {
					m_mat->PrintUniformLocations();
				}
			}
		}
#endif
	}
	void CMeshRenderer::SetMesh(Mesh* _Mesh) {
		m_mesh = _Mesh;
	}
	Mesh* CMeshRenderer::GetMesh() {
		return m_mesh;
	}
	void CMeshRenderer::SetMaterial(Material* _mat) {
		m_mat = _mat;
	}
	Material* CMeshRenderer::GetMaterial() {
		return m_mat;
	}
	void CMeshRenderer::Draw() {
		if (m_mat != nullptr && m_mesh != nullptr) {
			const AABB aabb = m_mesh->GetAABB();
			//if (!aabb.isOnFrustum(Renderer::m_cameraFrustum, *m_trans)) return;
			Material* select = nullptr;
			int count = 0;
			if (Renderer::wireframeMode) {
				count++;
				glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
				Renderer::pureColor->Use();
				Renderer::pureColor->UniformMat4("model", m_trans->LocalToGlobal());
				Renderer::pureColor->UniformMat4("view", Renderer::view);
				Renderer::pureColor->UniformMat4("projection", Renderer::projection);
				m_mesh->Draw();
			}
			if (Renderer::shadedMode) {
				count++;
				glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
				m_mat->Use();
				m_mat->UniformMat4("model", m_trans->LocalToGlobal());
				m_mat->UniformMat4("view", Renderer::view);
				m_mat->UniformMat4("projection", Renderer::projection);
				m_mesh->Draw();
			}
			if (!Renderer::m_renderRecord) return;
			else {
				Renderer::m_RenderState.DrawCall += static_cast<size_t>(count);
				Renderer::m_RenderState.Vertices += m_mesh->VerticesCount() * 2;
				Renderer::m_RenderState.Triangle += m_mesh->TriangleCount() * 2;
			}
		}
	}
	void CMeshRenderer::Start()
	{
		m_trans = m_host->GetRelateComponent<CTransformation>();
	}
	void CMeshRenderer::Render()
	{
		Draw();
	}
}