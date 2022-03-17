#include "mesh_Renderer.h"

// Include third party library
#include <glad/glad.h>
#include <GLFW/glfw3.h>

// Import Tara engine library
#include "../core/scene_object/scene_object.h"
#include "../core/mesh/mesh.h"
#include "../core/material/material.h"
#include "../core/renderer/renderer.h"
#include "../core/emath.h"
#include "transformation.h"
#include "../system/system.h"
#include "../system/mesh_renderer_system.h"

namespace Tara {
	DEFAULT_SRC_CTOR(MeshRendererComponent) {
		SystemRegister& sys = SystemRegister::Singleton();
		sys.AppendComponent<MeshRendererComponent>(this);
	}
	MeshRendererComponent::~MeshRendererComponent()
	{
		TARA_DEBUG("Remove Mesh Renderer");
		SystemRegister& sys = SystemRegister::Singleton();
		sys.RemoveComponent<MeshRendererComponent>(this);
	}
	void MeshRendererComponent::SetMesh(Mesh* _Mesh) {
		m_mesh = _Mesh;
	}
	Mesh* MeshRendererComponent::GetMesh() {
		return m_mesh;
	}
	void MeshRendererComponent::SetMaterial(Material* _mat) {
		m_mat = _mat;
	}
	Material* MeshRendererComponent::GetMaterial() {
		return m_mat;
	}
	void MeshRendererComponent::Draw() {
		Renderer& renderer = Renderer::Singleton();
		BatchRenderer& batchRenderer = BatchRenderer::Singleton();

		if (m_mat != nullptr && m_mesh != nullptr) {
			const AABB aabb = m_mesh->GetAABB();
			if (!aabb.isOnFrustum(renderer.CameraFrustum(), m_trans)) return;
			int count = 0;
			//Material::m_globalBlocks.at("ModelMatrix")->SetMat4("model", m_trans->LocalToGlobal());
			batchRenderer.AddRender(m_mesh, m_mat, m_trans);
		}
	}
	void MeshRendererComponent::Start()
	{
		m_trans = m_host->GetRelateComponent<TransformationComponent>();
	}
	void MeshRendererComponent::Render()
	{
		Draw();
	}
}