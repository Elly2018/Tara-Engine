#include "texture.h"
// Include std library
#include <map>
#include <functional>
#include <fstream>
#include <string>
#include <filesystem>

// Include third party library
#include <base64.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include "../utility.h"

namespace Tara {
	#pragma region Static Members
	const std::map<TextureFormat, int32_t> stride = {
		{TextureFormat::R16, 1},
		{TextureFormat::A, 1},
		{TextureFormat::RGB, 3},
		{TextureFormat::RGBA, 4},
		{TextureFormat::BGR, 3},
		{TextureFormat::BGRA, 4},
	};
	const std::map<TextureFormat, int32_t> formatMap = {
		{TextureFormat::R16, GL_R16},
		{TextureFormat::A, GL_ALPHA},
		{TextureFormat::RGB, GL_RGB},
		{TextureFormat::RGBA, GL_RGBA},
		{TextureFormat::BGR, GL_BGR},
		{TextureFormat::BGRA, GL_BGRA},
	};
	const std::map<TextureWrapMode, int32_t> wrapMap = {
		{TextureWrapMode::Repeat, GL_REPEAT},
		{TextureWrapMode::Mirror, GL_MIRRORED_REPEAT},
		{TextureWrapMode::Clamp, GL_CLAMP_TO_EDGE},
		{TextureWrapMode::ClampBorder, GL_CLAMP_TO_BORDER},
	};
	const std::map<TextureFilterMode, int32_t> filterMap = {
		{TextureFilterMode::Bilinear, GL_LINEAR},
		{TextureFilterMode::Point, GL_NEAREST},
	};
	const std::vector<CubeMapType> typelist = {
		CubeMapType::Front,
		CubeMapType::Back,
		CubeMapType::Left,
		CubeMapType::Right,
		CubeMapType::Up,
		CubeMapType::Down,
	};
	#pragma endregion


#pragma region Texture
	Texture::Texture()
	{
		TARA_DEBUG_LEVEL("Texture created!", 1);
		glGenTextures(1, &m_textureID);
	}
	Texture::~Texture()
	{
		TARA_DEBUG_LEVEL("Texture destroy! %s", 1, Name.c_str());
		glDeleteTextures(1, &m_textureID);
	}
	AssetPool<Texture>& Texture::GetAssetPool()
	{
		return *m_texturePool;
	}
	TextureConfig& Texture::Config()
	{
		return m_configbuffer;
	}
	uint32_t Texture::TextureID()
	{
		return m_textureID;
	}
	Texture::Texture(bool buildin)
	{
		m_buildIn = buildin;
	}
#pragma endregion


#pragma region Texture2D
	Texture2D::Texture2D(int32_t width, int32_t height, TextureFormat format) : Texture()
	{
		m_Size = glm::ivec2(width, height);
		m_config.Format = format;
		int32_t strd = stride.at(format);
		int size = m_Size.x * m_Size.y * strd;
		m_colordata = new unsigned char[size];
		GetAssetPool().Add(this);
	}
	Texture2D::Texture2D(bool buildin, int32_t width, int32_t height, TextureFormat format) : Texture2D(width, height, format)
	{
		m_buildIn = buildin;
	}

	Texture2D::~Texture2D()
	{
		delete m_Colordata;
	}

	void Texture2D::Bind()
	{
		glBindTexture(GL_TEXTURE_2D, m_textureID);
	}
	void Texture2D::Unbind()
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	void Texture2D::Apply()
	{
		m_config = m_configbuffer;
		Bind();
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapMap.at(m_config.Wrap_s));
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapMap.at(m_config.Wrap_t));
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, wrapMap.at(m_config.Wrap_r));
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filterMap.at(m_config.Filter));
		glTexImage2D(GL_TEXTURE_2D, 0, formatMap.at(m_config.Format),
			m_Size.x,
			m_Size.y,
			0,
			formatMap.at(m_config.Format),
			GL_UNSIGNED_BYTE,
			m_colordata);
		glGenerateMipmap(GL_TEXTURE_2D);
		TARA_DEBUG_LEVEL("Apply texture ! %s", 1, Name.c_str());
		Unbind();
	}
	Texture2D* Texture2D::ImportFromFile(std::string path)
	{
		TARA_DEBUG_LEVEL("Import texture file: %s", 2, path.c_str());
		if (!std::filesystem::exists(path)) {
			TARA_ERROR_LEVEL("File does not exist: %s", 4, path.c_str());
			return nullptr;
		}

		int w, h, cha;
		stbi_set_flip_vertically_on_load(true);
		unsigned char* data = stbi_load(path.c_str(), &w, &h, &cha, 3); //new unsigned char[s];
		if (data) {
			Texture2D* tex = new Texture2D(w, h, TextureFormat::RGB);
			tex->Name = "Default Texture";
			TARA_DEBUG_LEVEL("\tImport texture successfully: \"%s\"  \"%s\"", 2, path.c_str(), tex->Name.c_str());
			tex->m_buildIn = false;
			tex->m_Size.x = w;
			tex->m_Size.y = h;
			tex->m_colordata = data;
			tex->Apply();
			//stbi_image_free(tex->m_colordata);
			return tex;
		}
		else {
			TARA_WARNING_LEVEL("Failed to load Texture %s", 2, path.c_str());
			return nullptr;
		}
	}
	Texture2D* Texture2D::ImportFromMemory(std::vector<uint8_t> memory)
	{
		TARA_DEBUG_LEVEL("Import texture memory.", 2);
		remove(TEXTURE_IMPORT_TEMP);
		std::ofstream output(TEXTURE_IMPORT_TEMP, std::ios::out | std::ios::binary);
		for (auto i : memory) {
			output << i;
		}
		output.close();
		return ImportFromFile(TEXTURE_IMPORT_TEMP);
	}
	Texture2D* Texture2D::ImportFromMemory(std::vector<char> memory)
	{
		TARA_DEBUG_LEVEL("Import texture memory.", 2);
		remove(TEXTURE_IMPORT_TEMP);
		std::ofstream output(TEXTURE_IMPORT_TEMP, std::ios::out | std::ios::binary);
		output.write(memory.data(), memory.size());
		output.close();
		return ImportFromFile(TEXTURE_IMPORT_TEMP);
	}
	Texture2D* Texture2D::ImportFromMemory(const void* data, size_t length)
	{
		TARA_DEBUG_LEVEL("Import texture memory.", 2);
		remove(TEXTURE_IMPORT_TEMP);
		std::ofstream output(TEXTURE_IMPORT_TEMP, std::ios::out | std::ios::binary);
		output.write((const char*)data, length);
		output.close();
		return ImportFromFile(TEXTURE_IMPORT_TEMP);
	}
	Texture2D& Texture2D::Clone()
	{
		return *(new Texture2D(*this));
	}

	void Texture2D::SetPixel(int32_t x, int32_t y, unsigned char* data)
	{
		Bind();
		int32_t strd = stride.at(TextureFormat::RGB);
		int32_t current_index = (y * m_Size.x + x) * strd;
		for (int32_t s = 0; s < strd; s++) {
			m_colordata[current_index + s] = data[current_index + s];
		}
		Unbind();
	}
	void Texture2D::SetPixels(int32_t x, int32_t y, int32_t w, int32_t h, unsigned char* data)
	{
		Bind();
		int32_t strd = stride.at(TextureFormat::RGB);
		for (int32_t _y = y; _y < y + h; _y++) {
			for (int32_t _x = x; _x < x + w; _x++) {
				int32_t data_current_index = ((_y - y) * w + (_x - x)) * strd;
				int32_t current_index = (y * m_Size.x + x) * strd;
				for (int32_t s = 0; s < strd; s++) {
					m_colordata[current_index + s] = data[current_index + s];
				}
			}
		}
		Unbind();
	}
	glm::vec4 Texture2D::ReadPixel(int32_t x, int32_t y)
	{
		int32_t strd = stride.at(m_config.Format);
		int32_t si = (y * m_Size.x + x) * strd;
		glm::vec4 result = glm::vec4();
		switch (m_config.Format) {
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
	std::vector<glm::vec4> Texture2D::ReadPixels(int32_t x, int32_t y, int32_t w, int32_t h)
	{
		std::vector<glm::vec4> result = std::vector<glm::vec4>();
		for (int32_t _y = y; _y < y + h; _y++) {
			for (int32_t _x = x; _x < x + w; _x++) {
				result.push_back(ReadPixel(_x, _y));
			}
		}
		return result;
	}
	glm::ivec2 Texture2D::Size()
	{
		return m_Size;
	}
#pragma endregion


#pragma region Texture Multiple Sampler
	TextureMulti2DSample::TextureMulti2DSample(int32_t width, int32_t height, TextureFormat format) : Texture2D(width, height, format)
	{
	}
	TextureMulti2DSample::TextureMulti2DSample(bool buildin, int32_t width, int32_t height, TextureFormat format) : Texture2D(buildin, width, height, format)
	{
	}
	void TextureMulti2DSample::Bind()
	{
		glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, m_textureID);
	}
	void TextureMulti2DSample::Unbind()
	{
		glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, 0);
	}
	void TextureMulti2DSample::Apply()
	{
		m_config = m_configbuffer;
		Bind();
		glTexParameteri(GL_TEXTURE_2D_MULTISAMPLE, GL_TEXTURE_WRAP_S, wrapMap.at(m_config.Wrap_s));
		glTexParameteri(GL_TEXTURE_2D_MULTISAMPLE, GL_TEXTURE_WRAP_T, wrapMap.at(m_config.Wrap_t));
		glTexParameteri(GL_TEXTURE_2D_MULTISAMPLE, GL_TEXTURE_WRAP_R, wrapMap.at(m_config.Wrap_r));
		glTexParameteri(GL_TEXTURE_2D_MULTISAMPLE, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D_MULTISAMPLE, GL_TEXTURE_MAG_FILTER, filterMap.at(m_config.Filter));
		glTexImage2D(GL_TEXTURE_2D_MULTISAMPLE, 0, formatMap.at(m_config.Format),
			m_Size.x,
			m_Size.y,
			0,
			formatMap.at(m_config.Format),
			GL_UNSIGNED_BYTE,
			m_colordata);
		glGenerateMipmap(GL_TEXTURE_2D_MULTISAMPLE);
		TARA_DEBUG_LEVEL("Apply texture ! %s", 1, Name.c_str());
		Unbind();
	}
#pragma endregion


#pragma region TextureCube
	TextureCube::TextureCube(int32_t width, int32_t height, TextureFormat format) : Texture() {
		for (auto i : typelist) {
			m_Size[i] = glm::ivec2(width, height);
			int32_t strd = stride.at(format);
			int size = width * height * strd;
			m_colordata = new unsigned char[size];
		}
		m_config.Format = format;
		GetAssetPool().Add(this);
	}
	TextureCube::TextureCube(bool buildin, int32_t width, int32_t height, TextureFormat format) : TextureCube(width, height, format){
		m_buildIn = buildin;
	}
	TextureCube::~TextureCube() {
		for (auto& i : m_Colordata) {
			delete i.second;
		}
	}
	void TextureCube::Bind()
	{
		glBindTexture(GL_TEXTURE_CUBE_MAP, m_textureID);
	}
	void TextureCube::Unbind()
	{
		glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
	}
	void TextureCube::Apply()
	{
		m_config = m_configbuffer;
		Bind();
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, wrapMap.at(m_config.Wrap_s));
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, wrapMap.at(m_config.Wrap_t));
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, wrapMap.at(m_config.Wrap_r));
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, filterMap.at(m_config.Filter));
		for (auto i : typelist) {
			glTexImage2D((uint32_t)i, 0, formatMap.at(m_config.Format),
				m_Size.at(i).x,
				m_Size.at(i).y,
				0,
				formatMap.at(m_config.Format),
				GL_UNSIGNED_BYTE,
				m_Colordata.at(i));
		}
		//glGenerateMipmap(GL_TEXTURE_CUBE_MAP);
		TARA_DEBUG_LEVEL("Apply texture cube ! %s", 1, Name.c_str());
		Unbind();
	}
	TextureCube* TextureCube::LoadTexture(const char* front,
		const char* back,
		const char* left,
		const char* right,
		const char* up,
		const char* down)
	{
		std::vector<std::string> paths = {
			front,
			back,
			left,
			right,
			up,
			down
		};
		std::map<CubeMapType, std::pair<glm::ivec2, unsigned char*>> tdata = std::map<CubeMapType, std::pair<glm::ivec2, unsigned char*>>();
		int failed = 0;
		for (int32_t i = 0; i < 6; i++) {
			std::string path = paths.at(i);
			CubeMapType type = typelist.at(i);

			TARA_DEBUG_LEVEL("Import texture file: %s", 2, path.c_str());
			if (!std::filesystem::exists(path)) {
				TARA_ERROR_LEVEL("File does not exist: %s", 4, path.c_str());
				failed++;
				continue;
			}

			int w, h, cha = 0;
			stbi_set_flip_vertically_on_load(true);
			unsigned char* data = stbi_load(path.c_str(), &w, &h, &cha, 3); //new unsigned char[s];
			if (data) {
				tdata[type] = std::pair<glm::ivec2, unsigned char*>(glm::ivec2(w, h), data);
			}
			else {
				TARA_WARNING_LEVEL("Failed to load Texture %s", 2, path.c_str());
				failed++;
				continue;
			}
		}
		if (failed == 6) {
			TARA_WARNING_LEVEL("All cube map sources loading failed. return nullptr !", 2);
			return nullptr;
		}
		else {
			TextureCube* result = new TextureCube();
			result->Name = "Default Cube Texture";
			for (int32_t i = 0; i < 6; i++) {
				CubeMapType type = typelist.at(i);
				std::pair<glm::ivec2, unsigned char*> target = tdata.at(type);
				result->ReplaceTexture(type, target.second, target.first);
			}
			result->Apply();
			return result;
		}
	}
	bool TextureCube::ReplaceTexture(CubeMapType type, unsigned char* data, glm::ivec2 size)
	{
		return false;
	}
	bool TextureCube::ReplaceTexture(CubeMapType type, const char* path, glm::ivec2 size)
	{
		return false;
	}
	bool TextureCube::ReplaceTexture(CubeMapType type, Texture* tex, glm::ivec2 size)
	{
		return false;
	}
	glm::ivec2 TextureCube::Size(CubeMapType type)
	{
		return m_Size.at(type);
	}
#pragma endregion
};