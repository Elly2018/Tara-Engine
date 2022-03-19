#pragma once
// Import Tara engine library
#include "../core/config.h"
#include "component.h"

namespace Tara {
	class TARA_API Mesh;
	class TARA_API Material;

	/*
		Summary:
			Rendering mesh with material.
	*/
	class TARA_API MeshRendererComponent : public Component {
	public:
		DEFAULT_HEADER_CTOR(MeshRendererComponent);
		virtual ~MeshRendererComponent();
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
		void Render();
		void Start() override;

	private:
		// Assign mesh.
		Mesh* m_mesh = nullptr;
		// Assign material.
		Material* m_mat = nullptr;
		// Component host transformation.
		TransformationComponent* m_trans = nullptr;
	};
}