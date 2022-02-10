#include "mesh.h"
#include <map>
#include <functional>
#include <fstream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <glm/gtx/string_cast.hpp>
#include <buildin/buildin.h>

namespace Tara {
#pragma region BuildIn Getter
	#ifndef TARA_NO_BUILDIN_3D
	Mesh* GetCube()
	{
		Mesh* buffer = Mesh::ImportFromMemory(BuildInMesh::Cube().c_str());
		buffer->Name() = "Cube";
		buffer->BuildIn() = true;
		return buffer;
	}
	Mesh* GetSphere()
	{
		Mesh* buffer = Mesh::ImportFromMemory(BuildInMesh::Sphere().c_str());
		return buffer;
	}
	Mesh* GetPlane()
	{
		Mesh* buffer = Mesh::ImportFromMemory(BuildInMesh::Plane().c_str());
		return buffer;
	}
	Mesh* GetCone()
	{
		Mesh* buffer = Mesh::ImportFromMemory(BuildInMesh::Cone().c_str());
		return buffer;
	}
	Mesh* GetTriangle()
	{
		Mesh* buffer = Mesh::ImportFromMemory(BuildInMesh::Triangle().c_str());
		return buffer;
	}
	Mesh* GetQuad()
	{
		Mesh* buffer = Mesh::ImportFromMemory(BuildInMesh::Quad().c_str());
		return buffer;
	}
	#else
	#ifndef TARA_NO_BUILDIN_2D
	Mesh* GetQuad()
	{
		Mesh* buffer = Mesh::ImportFromMemory(BuildInMesh::Quad().c_str());
		return buffer;
	}
	#endif
	#endif
#pragma endregion

	AssetPool<Mesh>* Mesh::m_meshPool = new AssetPool<Mesh>();
	const std::map<CommomMesh, std::pair<std::string, std::function<Mesh* ()>>> mesh_commonMap = {
		#ifndef TARA_NO_BUILDIN_3D
		{CommomMesh::Cube, {"Cube", GetCube}},
		{CommomMesh::Sphere, {"Sphere", GetSphere}},
		{CommomMesh::Plane, {"Plane", GetPlane}},
		{CommomMesh::Cone, {"Cone", GetCone}},
		{CommomMesh::Triangle, {"Triangle", GetTriangle}},
		{CommomMesh::Quad, {"Quad", GetQuad}},
		#else
		#ifndef TARA_NO_BUILDIN_2D
		{CommomMesh::Error, {"Texture Shader", GetTextureShader}},
		#endif
		#endif
	};

	Mesh* ImportFromScene(const aiScene* scene) {
		if (scene->HasMeshes()) {
			aiMesh* bmesh = scene->mMeshes[0];
			Mesh* result = new Mesh();
			TARA_DEBUG_LEVEL("\tSet mesh name %s", 1, scene->mRootNode->mName.C_Str());
			result->Name() = scene->mRootNode->mName.C_Str();
			std::vector<glm::vec3> ver = std::vector<glm::vec3>();
			std::vector<glm::vec3> nor = std::vector<glm::vec3>();
			std::vector<glm::vec2> tex = std::vector<glm::vec2>();
			std::vector<uint32_t> ind = std::vector<uint32_t>();
			for (unsigned int i = 0; i < bmesh->mNumVertices; i++) {
				aiVector3D aver = bmesh->mVertices[i];
				ver.push_back(glm::vec3(aver.x, aver.y, aver.z));
				if (bmesh->HasNormals()) {
					aiVector3D anor = bmesh->mNormals[i];
					nor.push_back(glm::vec3(anor.x, anor.y, anor.z));
				}
				if (bmesh->mTextureCoords[0]) {
					aiVector3D atex = bmesh->mTextureCoords[0][i];
					tex.push_back(glm::vec2(atex.x, atex.y));
				}
				else {
					tex.push_back(glm::vec2(0, 0));
				}
			}
			for (unsigned int i = 0; i < bmesh->mNumFaces; i++) {
				aiFace face = bmesh->mFaces[i];
				for (unsigned int j = 0; j < face.mNumIndices; j++) {
					ind.push_back(face.mIndices[j]);
				}
			}
			result->SetVertices(ver);
			result->SetNormal(nor);
			result->SetTextures(tex);
			result->SetIndices(ind);
			result->Update();
			return result;
		}
		return nullptr;
	}

	void CreateDefaultMeshes()
	{
#ifndef TARA_NO_BUILDIN_3D
		TARA_DEBUG_LEVEL("Buildin resources mesh create: Cube", 1);
		Mesh::GetCommon(CommomMesh::Cube);
		TARA_DEBUG_LEVEL("Buildin resources mesh create: Sphere", 1);
		Mesh::GetCommon(CommomMesh::Sphere);
		TARA_DEBUG_LEVEL("Buildin resources mesh create: Plane", 1);
		Mesh::GetCommon(CommomMesh::Plane);
		TARA_DEBUG_LEVEL("Buildin resources mesh create: Cone", 1);
		Mesh::GetCommon(CommomMesh::Cone);
		TARA_DEBUG_LEVEL("Buildin resources mesh create: Triangle", 1);
		Mesh::GetCommon(CommomMesh::Triangle);
		TARA_DEBUG_LEVEL("Buildin resources mesh create: Quad", 1);
		Mesh::GetCommon(CommomMesh::Quad);
#else
#ifndef TARA_NO_BUILDIN_2D
		TARA_DEBUG_LEVEL("Buildin resources mesh create: Quad", 1);
		Mesh::GetCommon(CommomMesh::Quad);
#endif
#endif
	}

	Mesh::Mesh()
	{
		TARA_DEBUG_LEVEL("Mesh created!", 1);
		glGenVertexArrays(1, &m_VAO);
		glGenBuffers(1, &m_VBO);
		glGenBuffers(1, &m_EBO);
		TARA_DEBUG_LEVEL("\tMesh pool add!", 1);
		GetAssetPool()->Add(*this);
	}
	Mesh::~Mesh()
	{
		TARA_DEBUG_LEVEL("Mesh destroy! %s", 1, Name().c_str());
		glDeleteVertexArrays(1, &m_VAO);
		glDeleteBuffers(1, &m_VBO);
		glDeleteBuffers(1, &m_EBO);
		m_vertices.clear();
		m_normal.clear();
		m_textures.clear();
		m_indices.clear();
	}

	Mesh* Mesh::GetCommon(CommomMesh type)
	{
		if (!mesh_commonMap.count(type)) {
			TARA_WARNING_LEVEL("Commom mesh does not register:", 3);
			return nullptr;
		}
		auto cgs = mesh_commonMap.at(type);
		Mesh* s = GetAssetPool()->FindByName(cgs.first.c_str(), true);
		if (s == nullptr) {
			s = cgs.second();
			s->Name() = cgs.first;
			s->BuildIn() = true;
		}
		else {
			return s;
		}
	}
	Mesh* Mesh::ImportFromFile(const char* filename)
	{
		TARA_DEBUG_LEVEL("Trying import mesh from: %s", 1, filename);
		Assimp::Importer importer;
		const aiScene* scene = importer.ReadFile(filename, aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);
		if (scene) {
			return ImportFromScene(scene);
		}
		TARA_DEBUG_LEVEL("ASSIMP::ERROR::%s", 4, importer.GetErrorString());
		return nullptr;
	}
	Mesh* Mesh::ImportFromMemory(std::string memoey) {
		TARA_DEBUG_LEVEL("Trying import mesh from memory", 1);
		Assimp::Importer importer;
		remove(MESH_IMPORT_TEMP);
		std::ofstream output(MESH_IMPORT_TEMP);
		output << memoey;
		output.close();
		return ImportFromFile(MESH_IMPORT_TEMP);
	}
	AssetPool<Mesh>* Mesh::GetAssetPool()
	{
		return m_meshPool;
	}

	Mesh& Mesh::Clone()
	{
		Mesh m = *new Mesh(*this);
		m.Name() += " Clone";
		m.BuildIn() = false;
		return m;
	}
	void Mesh::Bind()
	{
		glBindVertexArray(m_VAO);
	}
	void Mesh::Unbind()
	{
		glBindVertexArray(0);
	}
	void Mesh::Update()
	{
		Bind();
		TARA_DEBUG_LEVEL("Mesh update start: %s", 2, Name().c_str());
		m_pack.clear();
		m_aabb = GenerateAABB();
		size_t size = m_vertices.size();
		for (int32_t i = 0; i < size; i++) {
			glm::vec3 v = m_vertices.at(i);
			glm::vec3 n = glm::vec3();
			glm::vec2 t = glm::vec2();
			if (i < m_normal.size()) {
				n = m_normal.at(i);
			}
			if (i < m_textures.size()) {
				t = m_textures.at(i);
			}
			Vertex ver = Vertex();
			ver.Position = v;
			ver.Normal = n;
			ver.TexCoords = t;
			m_pack.push_back(ver);
		}

		glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
		glBufferData(GL_ARRAY_BUFFER, m_pack.size() * sizeof(Vertex), &m_pack[0], GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indices.size() * sizeof(uint32_t), &m_indices[0], GL_STATIC_DRAW);
		// Vertex
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
		glEnableVertexAttribArray(0);
		// Normal
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);
		// Texture
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(6 * sizeof(float)));
		glEnableVertexAttribArray(2);
		TARA_DEBUG_LEVEL("Mesh update end: %s", 2, Name().c_str());
		Unbind();
	}
	void Mesh::Draw()
	{
		Bind();
		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);
		glDrawElements(GL_TRIANGLES, m_indices.size(), GL_UNSIGNED_INT, 0);
		Unbind();
	}
	size_t Mesh::VerticesCount()
	{
		return m_pack.size();
	}
	size_t Mesh::TriangleCount()
	{
		return m_indices.size() / 3;
	}
	AABB Mesh::GetAABB()
	{
		return m_aabb;
	}
	AABB Mesh::GenerateAABB()
	{
		glm::vec3 minAABB = glm::vec3(std::numeric_limits<float_t>::max());
		glm::vec3 maxAABB = glm::vec3(std::numeric_limits<float_t>::min());
		for (glm::vec3& vertex : m_vertices)
		{
			minAABB.x = std::min(minAABB.x, vertex.x);
			minAABB.y = std::min(minAABB.y, vertex.y);
			minAABB.z = std::min(minAABB.z, vertex.z);
							 
			maxAABB.x = std::max(maxAABB.x, vertex.x);
			maxAABB.y = std::max(maxAABB.y, vertex.y);
			maxAABB.z = std::max(maxAABB.z, vertex.z);
		}
		TARA_DEBUG("min %f, %f, %f", minAABB.x, minAABB.y, minAABB.z);
		TARA_DEBUG("max %f, %f, %f", maxAABB.x, maxAABB.y, maxAABB.z);
		return AABB(minAABB, maxAABB);
	}
	void Mesh::CleanStore()
	{
		m_vertices.clear();
		m_normal.clear();
		m_textures.clear();
		m_indices.clear();
	}
	void Mesh::CleanPack()
	{
		m_pack.clear();
	}

	void Mesh::SetVertices(std::vector<glm::vec3>& ver)
	{
		m_vertices = ver;
		TARA_DEBUG_LEVEL("\t%s Vertex register size: %i", 1, Name().c_str(), m_vertices.size());
	}
	void Mesh::SetNormal(std::vector<glm::vec3>& ver)
	{
		m_normal = ver;
		TARA_DEBUG_LEVEL("\t%s Normal register size: %i", 1, Name().c_str(), m_normal.size());
	}
	void Mesh::SetTextures(std::vector<glm::vec2>& tex)
	{
		m_textures = tex;
		TARA_DEBUG_LEVEL("\t%s Textures register size: %i", 1, Name().c_str(), m_textures.size());
	}
	void Mesh::SetIndices(std::vector<uint32_t>& ind)
	{
		m_indices = ind;
		TARA_DEBUG_LEVEL("\t%s Indices register size: %i", 1, Name().c_str(), m_indices.size());
	}
	void Mesh::SetVertex(std::vector<Vertex>& ver)
	{
		m_pack = ver;
		TARA_DEBUG_LEVEL("\t%s Pack register size: %i", 1, Name().c_str(), m_pack.size());
	}
}