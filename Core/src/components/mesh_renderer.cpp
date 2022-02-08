#include "components/mesh_renderer.h"
#include <eobject.h>
#include <renderer.h>
#include <components/component.h>
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
			Material* select = nullptr;
			select = renderer::wireframeMode ? renderer::pureColor : m_mat;
			select->Use();
			select->UniformMat4("model", m_trans->LocalToGlobal());
			select->UniformMat4("view", renderer::view);
			select->UniformMat4("projection", renderer::projection);
			m_mesh->Draw();
			renderer::m_RenderState.DrawCall++;
			renderer::m_RenderState.Vertices += m_mesh->VerticesCount();
			renderer::m_RenderState.Triangle += m_mesh->TriangleCount();
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