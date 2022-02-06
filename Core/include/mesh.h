#pragma once
#include <string>
#include <vector>
#include <config.h>
#include <asset.h>
#include <glm/glm.hpp>

namespace Tara {
	/*

		Structs, classes declaration

	*/
	struct DllExport Vertex;
	struct DllExport Mesh;

	enum class DllExport CommomMesh {
		Cube,
		Quad,
		Sphere, 
		Plane, 
		Cone,
		Triangle
	};

	struct Vertex {
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

	struct Mesh : public AssetBase
	{
	public:
		Mesh();
		~Mesh();

		static Mesh* GetCommon(CommomMesh type);
		static Mesh* GetCube(glm::vec3 size = glm::vec3(1), glm::ivec3 subdive = glm::ivec3(1));
		static Mesh* GetQuad(glm::vec3 size = glm::vec3(1), glm::ivec3 subdive = glm::ivec3(1));
		static Mesh* GetSphere(glm::vec3 size = glm::vec3(1), glm::ivec2 linecut = glm::ivec2(6));
		static Mesh* GetPlane(glm::vec2 size = glm::vec3(1));
		static Mesh* GetCone(glm::vec3 size = glm::vec3(1), int32_t dotcount = 12);
		static Mesh* GetTriangle(glm::vec3 size = glm::vec3(1));
		static Mesh* ImportFromFile(const char* filename);
		/*
			Summary:
				Get asset pool
		*/
		static AssetPool<Mesh>* GetAssetPool();
		

		void Bind();
		void Unbind();
		void Update();
		void Draw();

		void CleanStore();
		void CleanPack();

		void SetVertices(std::vector<glm::vec3> ver);
		void SetNormal(std::vector<glm::vec3> ver);
		void SetTextures(std::vector<glm::vec2> tex);
		void SetIndices(std::vector<uint32_t> ind);
		void SetVertex(std::vector<Vertex> ver);

	private:
		uint32_t m_VAO = -1;
		uint32_t m_VBO = -1;
		uint32_t m_EBO = -1;
		std::vector<glm::vec3> m_vertices = std::vector<glm::vec3>();
		std::vector<glm::vec3> m_normal = std::vector<glm::vec3>();
		std::vector<glm::vec2> m_textures = std::vector<glm::vec2>();
		std::vector<uint32_t> m_indices = std::vector<uint32_t>();
		std::vector<Vertex> m_pack = std::vector<Vertex>();

		static AssetPool<Mesh>* m_meshPool;
	};
}