#pragma once
#include <string>
#include <vector>
#include <config.h>
#include <asset.h>
#include <glm/glm.hpp>
#include <emath.h>

namespace Tara {
	/*
		Summary:
			Buildin mesh types.
	*/
	enum class DllExport CommomMesh {
#ifndef TARA_NO_BUILDIN_3D
		Cube,
		Sphere, 
		Plane, 
		Cone,
		Triangle,
		Quad
#else
	#ifndef TARA_NO_BUILDIN_2D
		Quad,
	#endif
#endif
	};


	/*
		Summary:
			Mesh use vertex buffer struct.
	*/
	struct DllExport Vertex {
	public:
		glm::vec3 Position;
		glm::vec3 Normal;
		glm::vec2 TexCoords;
	};


	/*
		Summary:
			Generate default shaders.
	*/
	DllExport void CreateDefaultMeshes();


	/*
		Summary:
			
	*/
	class DllExport Mesh : public AssetBase
	{
	public:
		Mesh();
		~Mesh();
		/*
			Summary:
				Get buildin mesh
		*/
		static Mesh* GetCommon(CommomMesh type);
		static Mesh* ImportFromFile(const char* filename);
		static Mesh* ImportFromMemory(std::string memory);
		/*
			Summary:
				Get asset pool
		*/
		static AssetPool<Mesh>* GetAssetPool();
		/*
			Summary:
				Clone the mesh instance.
		*/
		Mesh& Clone();
		void Bind();
		void Unbind();
		void Update();
		void Draw();
		size_t VerticesCount();
		size_t TriangleCount();
		AABB GetAABB();
		AABB GenerateAABB();

		void CleanStore();
		void CleanPack();

		void SetVertices(std::vector<glm::vec3>& ver);
		void SetNormal(std::vector<glm::vec3>& ver);
		void SetTextures(std::vector<glm::vec2>& tex);
		void SetIndices(std::vector<uint32_t>& ind);
		void SetVertex(std::vector<Vertex>& ver);

	private:
		uint32_t m_VAO = -1;
		uint32_t m_VBO = -1;
		uint32_t m_EBO = -1;
		std::vector<glm::vec3> m_vertices = std::vector<glm::vec3>();
		std::vector<glm::vec3> m_normal = std::vector<glm::vec3>();
		std::vector<glm::vec2> m_textures = std::vector<glm::vec2>();
		std::vector<uint32_t> m_indices = std::vector<uint32_t>();
		std::vector<Vertex> m_pack = std::vector<Vertex>();
		AABB m_aabb = AABB();
		static AssetPool<Mesh>* m_meshPool;
	};
}