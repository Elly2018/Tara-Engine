#pragma once
#include <map>
#include <config.h>
#include <asset.h>
#include <shader.h>
#include <Texture.h>
#include <glm/glm.hpp>

namespace Tara {
	/*
		Summary:
			The container for shader, store uniform data.
			When 'use()' is call, it will send all the uniform buffer.
	*/
	class DllExport Material final : public AssetBase
	{
	public:
		Material(Shader& _shader);
		~Material();

		Material& Clone();
		/*
			Summary:
				Use the shader program.
				And sending all the uniform buffer.
		*/
		void Use();
		/*
			Summary:
				Unuse the shader program.
		*/
		void Unuse();
		/*
			Summary:
				Get material binding shader.
		*/
		Shader& GetShader();

#ifndef TARA_NO_IMGUI
		/*
			Summary:
				Draw all the material properties on GUI.
		*/
		void GUI();
#endif // !TARA_NO_IMGUI

		void SetTexture(const char* name, Texture& v);
		void SetTextureIndex(const char* name, const int32_t v);
		void SetNumber(const char* name, const float_t v);
		void SetVec2(const char* name, const glm::vec2 v);
		void SetVec3(const char* name, const glm::vec3 v);
		void SetVec4(const char* name, const glm::vec4 v);
		void SetMat3(const char* name, const glm::mat3 v);
		void SetMat4(const char* name, const glm::mat4 v);

		void UniformTexture(const char* location, Texture& v);
		void UniformTexture(const char* location, const uint32_t v);
		void UniformNumber(const char* location, const float_t v);
		void UniformVec2(const char* location, const glm::vec2 v);
		void UniformVec3(const char* location, const glm::vec3 v);
		void UniformVec4(const char* location, const glm::vec4 v);
		void UniformMat3(const char* location, const glm::mat3 v);
		void UniformMat4(const char* location, const glm::mat4 v);

		void PrintUniformLocations();
		void CleanUniform();
		/*
			Summary:
				Get asset pool
		*/
		static AssetPool<Material>* GetAssetPool();

	private:
		std::map<const char*, int32_t> m_TextureIndex = std::map<const char*, int32_t>();
		std::map<const char*, Texture*> m_TextureBind = std::map<const char*, Texture*>();
		std::map<const char*, float_t> m_numberBind = std::map<const char*, float_t>();
		std::map<const char*, glm::vec2> m_vec2Bind = std::map<const char*, glm::vec2>();
		std::map<const char*, glm::vec3> m_vec3Bind = std::map<const char*, glm::vec3>();
		std::map<const char*, glm::vec4> m_vec4Bind = std::map<const char*, glm::vec4>();
		std::map<const char*, glm::mat3> m_mat3Bind = std::map<const char*, glm::mat3>();
		std::map<const char*, glm::mat4> m_mat4Bind = std::map<const char*, glm::mat4>();
		Shader* m_shader;
		static AssetPool<Material>* m_materialPool;
	};
}