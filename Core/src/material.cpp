#include "material.h"
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/matrix.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>


namespace Tara {
	AssetPool<Material>* Material::m_materialPool = new AssetPool<Material>();

	Material::Material(Shader& _shader)
	{
		m_shader = &_shader;
		m_materialPool->Add(*this);
	}
	Material::~Material()
	{
		
	}

	Material& Material::Clone()
	{
		Material& m = *new Material(*this);
		m.m_buildIn = false;
		return m;
	}
	void Material::Use()
	{
		if (m_shader == nullptr) {
			TARA_ERROR_LEVEL("Material has no shader binding: %s.", 4, Name().c_str());
			return;
		}
		m_shader->Use();
		for (auto it = m_TextureIndex.begin(); it != m_TextureIndex.end(); it++) {
			glUniform1i(glGetUniformLocation(m_shader->program, it->first), it->second);
		}
		for (auto it = m_TextureBind.begin(); it != m_TextureBind.end(); it++) {
			UniformTexture(it->first, *it->second);
		}
		for (auto it = m_numberBind.begin(); it != m_numberBind.end(); it++) {
			UniformNumber(it->first, it->second);
		}
		for (auto it = m_vec2Bind.begin(); it != m_vec2Bind.end(); it++) {
			UniformVec2(it->first, it->second);
		}
		for (auto it = m_vec3Bind.begin(); it != m_vec3Bind.end(); it++) {
			UniformVec3(it->first, it->second);
		}
		for (auto it = m_vec4Bind.begin(); it != m_vec4Bind.end(); it++) {
			UniformVec4(it->first, it->second);
		}
		for (auto it = m_mat3Bind.begin(); it != m_mat3Bind.end(); it++) {
			UniformMat3(it->first, it->second);
		}
		for (auto it = m_mat4Bind.begin(); it != m_mat4Bind.end(); it++) {
			UniformMat4(it->first, it->second);
		}
	}
	void Material::Unuse()
	{
		m_shader->Unuse();
	}
	Shader& Material::GetShader()
	{
		if (!m_shader) m_shader = Shader::GetCommon(CommonShader::Error);
		return *m_shader;
	}
	void Material::GUI()
	{

	}

	void Material::SetTextureIndex(const char* name, const int32_t v)
	{
		m_TextureIndex[name] = v;
	}
	void Material::SetTexture(const char* name, Texture& v)
	{
		m_TextureBind[name] = &v;
	}
	void Material::SetNumber(const char* name, const float_t v)
	{
		m_numberBind[name] = v;
	}
	void Material::SetVec2(const char* name, const glm::vec2 v)
	{
		m_vec2Bind[name] = v;
	}
	void Material::SetVec3(const char* name, const glm::vec3 v)
	{
		m_vec3Bind[name] = v;
	}
	void Material::SetVec4(const char* name, const glm::vec4 v)
	{
		m_vec4Bind[name] = v;
	}
	void Material::SetMat3(const char* name, const glm::mat3 v)
	{
		m_mat3Bind[name] = v;
	}
	void Material::SetMat4(const char* name, const glm::mat4 v)
	{
		m_mat4Bind[name] = v;
	}
	void Material::UniformTexture(const char* location, Texture& v)
	{
		int32_t index = m_TextureIndex.at(location);
		glActiveTexture(GL_TEXTURE0 + index);
		v.Bind();
	}
	void Material::UniformTexture(const char* location, const uint32_t v)
	{
		if (v == -1) return;
		int32_t index = m_TextureIndex.at(location);
		glActiveTexture(GL_TEXTURE0 + index);
		glBindTexture(GL_TEXTURE_2D, v);
	}

	void Material::UniformNumber(const char* location, const float_t v)
	{
		GLint i = m_shader->GetUniformLocation(location);
		glUniform1f(i, v);
	}
	void Material::UniformVec2(const char* location, const glm::vec2 v)
	{
		GLint i = m_shader->GetUniformLocation(location);
		glUniform2f(i, v.x, v.y);
	}
	void Material::UniformVec3(const char* location, const glm::vec3 v)
	{
		GLint i = m_shader->GetUniformLocation(location);
		glUniform3f(i, v.x, v.y, v.z);
	}
	void Material::UniformVec4(const char* location, const glm::vec4 v)
	{
		GLint i = m_shader->GetUniformLocation(location);
		glUniform4f(i, v.x, v.y, v.z, v.w);
	}
	void Material::UniformMat3(const char* location, const glm::mat3 v)
	{
		GLint i = m_shader->GetUniformLocation(location);
		glUniformMatrix3fv(i, 1, false, glm::value_ptr(v));
	}
	void Material::UniformMat4(const char* location, const glm::mat4 v)
	{
		GLint i = m_shader->GetUniformLocation(location);
		glUniformMatrix4fv(i, 1, false, glm::value_ptr(v));
	}
	void Material::PrintUniformLocations()
	{
		m_shader->PrintUniform();
	}
	void Material::CleanUniform()
	{
		m_TextureIndex = std::map<const char*, int32_t>();
		m_TextureBind = std::map<const char*, Texture*>();
		for (auto it = m_numberBind.begin(); it != m_numberBind.end(); it++) {
			(*it).second = 0;
		}
		for (auto it = m_vec2Bind.begin(); it != m_vec2Bind.end(); it++) {
			(*it).second = glm::vec2(0);
		}
		for (auto it = m_vec3Bind.begin(); it != m_vec3Bind.end(); it++) {
			(*it).second = glm::vec3(0);
		}
		for (auto it = m_vec4Bind.begin(); it != m_vec4Bind.end(); it++) {
			(*it).second = glm::vec4(0);
		}
		for (auto it = m_mat3Bind.begin(); it != m_mat3Bind.end(); it++) {
			(*it).second = glm::mat3(1);
		}
		for (auto it = m_mat4Bind.begin(); it != m_mat4Bind.end(); it++) {
			(*it).second = glm::mat4(1);
		}
	}
	AssetPool<Material>* Material::GetAssetPool()
	{
		return m_materialPool;
	}
};