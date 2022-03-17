#pragma once
// Include std library
#include <memory>
#include <string>
#include <vector>

// Include third party library
#include <glm/glm.hpp>

// Include tara library
#include "../config.h"
#include "../asset.h"

namespace Tara {
	/*
		Structures and classes
	*/
	class TARA_API AABB;

	/*
		Summary:
			Mesh use vertex buffer struct.
	*/
	struct TARA_API Vertex {
	public:
		glm::vec3 Position;
		glm::vec3 Normal;
		glm::vec2 TexCoords;
	};

	/*
		Summary:
			
	*/
	class TARA_API Mesh : public AssetBase {
		friend class BuildinManager;
	public:
		Mesh();
	protected:
		Mesh(bool buildin);
	public:
		~Mesh();
		
		static Mesh* ImportFromFile(const char* filename);
		static Mesh* ImportFromMemory(std::string memory);
		static Mesh* ImportFromMemory(const void* data, size_t length);
		/*
			Summary:
				Get asset pool
		*/
		static AssetPool<Mesh>& GetAssetPool();
		/*
			Summary:
				Clone the mesh instance.
		*/
		Mesh& Clone();
		void Bind();
		void Unbind();
		void Update();
		void Draw(glm::mat4 models = glm::mat4(1));
		void BatchDraw(std::vector<glm::mat4> models);
		size_t VerticesCount();
		size_t TriangleCount();
		AABB& GetAABB();
		AABB* GenerateAABB();

		void CleanStore();
		void CleanPack();

		void SetVertices(std::vector<glm::vec3>& ver);
		void SetNormal(std::vector<glm::vec3>& ver);
		void SetTextures(std::vector<glm::vec2>& tex);
		void SetIndices(std::vector<uint32_t>& ind);
		void SetVertex(std::vector<Vertex>& ver);

	private:
		uint32_t last_stream = 0;
		uint32_t m_VAO = -1;
		uint32_t m_VBO = -1;
		uint32_t m_EBO = -1;
		AABB* m_aabb;
		std::vector<glm::vec3> m_vertices = std::vector<glm::vec3>();
		std::vector<glm::vec3> m_normal = std::vector<glm::vec3>();
		std::vector<glm::vec2> m_textures = std::vector<glm::vec2>();
		std::vector<uint32_t> m_indices = std::vector<uint32_t>();
		std::vector<Vertex> m_pack = std::vector<Vertex>();
		static AssetPool<Mesh>* m_meshPool;
	};

	inline TARA_API AssetPool<Mesh>* Mesh::m_meshPool = new AssetPool<Mesh>();
}