#include "texture.h"
#include <map>
#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

namespace Tara {
	const char* GridTexture_Path = ".\\Resources\\Grid.png";
	const char* DefaultTexture_Path = ".\\Resources\\Default.png";
	AssetPool<Texture>* Texture::m_texturePool = new AssetPool<Texture>();
	std::map<TextureFormat, int32_t> stride = {
		{TextureFormat::R16, 1},
		{TextureFormat::A, 1},
		{TextureFormat::RGB, 3},
		{TextureFormat::RGBA, 4},
		{TextureFormat::BGR, 3},
		{TextureFormat::BGRA, 4},
	};

	void CreateDefaultTextures()
	{
		TARA_DEBUG_LEVEL("Buildin resources texture create: White", 1);
		Texture::GetCommon(CommomTexture::White);
		TARA_DEBUG_LEVEL("Buildin resources texture create: Grid", 1);
		Texture::GetCommon(CommomTexture::Grid);
		TARA_DEBUG_LEVEL("Buildin resources texture create: Default", 1);
		Texture::GetCommon(CommomTexture::Default);
	}

	Texture::Texture() : Texture(1, 1, TextureFormat::RGB) {}
	Texture::Texture(int32_t _w, int32_t _h, TextureFormat _f)
	{
		TARA_DEBUG_LEVEL("Texture created!", 1);
		glGenTextures(1, &m_textureID);
		m_width = _w;
		m_height = _h;
		m_format = _f;
		int32_t strd = stride.at(m_format);
		int size = m_width * m_height * strd;
		m_colordata = new unsigned char[size];
		m_texturePool->Add(this);
	}
	Texture::~Texture()
	{
		TARA_DEBUG_LEVEL("Texture destroy! %s", 1, Name());
		glDeleteTextures(1, &m_textureID);
	}

	Texture* Texture::GetCommon(CommomTexture type)
	{
		switch (type)
		{
		case CommomTexture::White:
		{
			Texture* s = m_texturePool->Find("White Texture", true);
			if (s == nullptr) return GetWhiteTexture();
			else return s;
		}
		case CommomTexture::Grid:
		{
			Texture* s = m_texturePool->Find("Grid Texture", true);
			if (s == nullptr) return GetGridTexture();
			else return s;
		}
		case CommomTexture::Default:
		{
			Texture* s = m_texturePool->Find("Default Texture", true);
			if (s == nullptr) return GetDefaultTexture();
			else return s;
		}
		}
		return nullptr;
	}
	Texture* Texture::GetWhiteTexture(int32_t size)
	{
		Texture* tex = new Texture(size, size, TextureFormat::RGB);
		tex->m_name = "White Texture";
		tex->m_buildIn = false;
		TARA_DEBUG_LEVEL("\tGenerate texture successfully: \"%s\"  \"%s\"", 2, "White texture", tex->Name());
		int32_t s = size * size * stride.at(TextureFormat::RGB);
		unsigned char* data = new unsigned char[s];
		for (int32_t i = 0; i < s; i++) {
			unsigned char c = 0xff;
			data[i] = c;
		}
		tex->SetPixels(0, 0, size, size, data);
		tex->Apply();
		return tex;
	}
	Texture* Texture::GetGridTexture()
	{
		int w, h, cha = 0;
		stbi_set_flip_vertically_on_load(true);
		unsigned char* data = stbi_load(GridTexture_Path, &w, &h, &cha, 3); //new unsigned char[s];
		if (data) {
			Texture* tex = new Texture(w, h, TextureFormat::RGB);
			tex->m_name = "Grid Texture";
			TARA_DEBUG_LEVEL("\tImport texture successfully: \"%s\"  \"%s\"", 2, GridTexture_Path, tex->Name());
			tex->m_buildIn = true;
			tex->m_width = w;
			tex->m_height = h;
			tex->m_colordata = data;
			tex->Apply();
			//stbi_image_free(tex->m_colordata);
			return tex;
		}
		else {
			TARA_ERROR_LEVEL("Failed to load Texture %s", 3, GridTexture_Path);
			return nullptr;
		}
	}
	Texture* Texture::GetDefaultTexture()
	{
		int w, h, cha = 0;
		stbi_set_flip_vertically_on_load(true);
		unsigned char* data = stbi_load(DefaultTexture_Path, &w, &h, &cha, 3); //new unsigned char[s];
		if (data) {
			Texture* tex = new Texture(w, h, TextureFormat::RGB);
			tex->m_name = "Default Texture";
			TARA_DEBUG_LEVEL("\tImport texture successfully: \"%s\"  \"%s\"", 2, DefaultTexture_Path, tex->Name());
			tex->m_buildIn = true;
			tex->m_width = w;
			tex->m_height = h;
			tex->m_colordata = data;
			tex->Apply();
			//stbi_image_free(tex->m_colordata);
			return tex;
		}
		else {
			TARA_DEBUG("Failed to load Texture %s", DefaultTexture_Path);
			return nullptr;
		}
	}
	AssetPool<Texture>* Texture::GetAssetPool()
	{
		return m_texturePool;
	}

	void Texture::Bind()
	{
		glBindTexture(GL_TEXTURE_2D, m_textureID);
	}
	void Texture::Unbind()
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	void Texture::Apply()
	{
		Bind();
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D, 0, (GLint)m_format, m_width, m_height, 0, (GLint)m_format, GL_UNSIGNED_BYTE, m_colordata);
		glGenerateMipmap(GL_TEXTURE_2D);
		TARA_DEBUG("Apply ! %s", Name());
		Unbind();
	}
	void Texture::SetPixel(int32_t x, int32_t y, unsigned char* data)
	{
		Bind();
		int32_t strd = stride.at(TextureFormat::RGB);
		int32_t current_index = (y * m_width + x) * strd;
		for (int32_t s = 0; s < strd; s++) {
			m_colordata[current_index + s] = data[current_index + s];
		}
		Unbind();
	}
	void Texture::SetPixels(int32_t x, int32_t y, int32_t w, int32_t h, unsigned char* data)
	{
		Bind();
		int32_t strd = stride.at(TextureFormat::RGB);
		for (int32_t _y = y; _y < y + h; _y++) {
			for (int32_t _x = x; _x < x + w; _x++) {
				int32_t data_current_index = ((_y - y) * w + (_x - x)) * strd;
				int32_t current_index = (y * m_width + x) * strd;
				for (int32_t s = 0; s < strd; s++) {
					m_colordata[current_index + s] = data[current_index + s];
				}
			}
		}
		Unbind();
	}
	glm::vec4 Texture::ReadPixel(int32_t x, int32_t y)
	{
		int32_t strd = stride.at(m_format);
		int32_t si = (y * m_width + x) * strd;
		glm::vec4 result = glm::vec4();
		switch (m_format) {
		case TextureFormat::A:
			result = glm::vec4(0, 0, 0, m_colordata[si]);
			break;
		case TextureFormat::RGB:
			result = glm::vec4(m_colordata[si], m_colordata[si + 1], m_colordata[si + 2], 1);
			break;
		case TextureFormat::RGBA:
			result = glm::vec4(m_colordata[si], m_colordata[si + 1], m_colordata[si + 2], m_colordata[si + 3]);
			break;
		case TextureFormat::BGR:
			result = glm::vec4(m_colordata[si + 1], m_colordata[si + 1], m_colordata[si], 1);
			break;
		case TextureFormat::BGRA:
			result = glm::vec4(m_colordata[si + 2], m_colordata[si + 1], m_colordata[si], m_colordata[si + 3]);
			break;
		}
		return result;
	}
	std::vector<glm::vec4> Texture::ReadPixels(int32_t x, int32_t y, int32_t w, int32_t h)
	{
		std::vector<glm::vec4> result = std::vector<glm::vec4>();
		for (int32_t _y = y; _y < y + h; _y++) {
			for (int32_t _x = x; _x < x + w; _x++) {
				result.push_back(ReadPixel(_x, _y));
			}
		}
		return result;
	}
	glm::ivec2 Texture::Size()
	{
		return glm::ivec2(m_width, m_height);
	}
	uint32_t Texture::ID()
	{
		return m_textureID;
	}
};