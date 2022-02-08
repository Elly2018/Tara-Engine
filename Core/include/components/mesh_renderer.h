#pragma once
#include <config.h>
#include <mesh.h>
#include <material.h>
#include <components/component.h>
#include <components/transformation.h>

namespace Tara {
	/*
		Summary:
			Rendering mesh with material.
	*/
	class DllExport CMeshRenderer : public EComponent {
	public:
		DEFAULT_CTOR_IMPLE(CMeshRenderer);

		void GUI() override;
		/*
			Summary:
				Assign mesh pointer.
		*/
		void SetMesh(Mesh* _mesh);
		/*
			Summary:
				Get mesh.
		*/
		Mesh* GetMesh();
		/*
			Summary:
				Assign material pointer.
		*/
		void SetMaterial(Material* _mat);
		/*
			Summary:
				Get material.
		*/
		Material* GetMaterial();
		/*
			Summary:
				Drawing mesh onto screen.
				It won't render if mesh or material equal null pointer.
		*/
		void Draw();
		void Start() override;
		void Render() override;
	private:
		// Assign mesh.
		Mesh* m_mesh = nullptr;
		// Assign material.
		Material* m_mat = nullptr;
		// Component host transformation.
		CTransformation* m_trans = nullptr;
	};
}