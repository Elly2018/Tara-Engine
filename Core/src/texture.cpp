#include "texture.h"
#include <map>
#include <functional>
#include <string>
#include <buildin/buildin.h>
#include <base64.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

namespace Tara {
	#pragma region Static Members
	#define GridTexture_Path ".\\Resources\\Grid.png"
	#define DefaultTexture_Path ".\\Resources\\Default.png"
	std::map<TextureFormat, int32_t> stride = {
		{TextureFormat::R16, 1},
		{TextureFormat::A, 1},
		{TextureFormat::RGB, 3},
		{TextureFormat::RGBA, 4},
		{TextureFormat::BGR, 3},
		{TextureFormat::BGRA, 4},
	};
	Texture* GetWhiteTexture()
	{
		Texture* tex = new Texture(512, 512, TextureFormat::RGB);
		TARA_DEBUG_LEVEL("\tGenerate texture successfully: \"%s\"  \"%s\"", 2, "White texture", tex->Name().c_str());
		int32_t s = 512 * 512 * stride.at(TextureFormat::RGB);
		unsigned char* data = new unsigned char[s];
		for (int32_t i = 0; i < s; i++) {
			unsigned char c = 0xff;
			data[i] = c;
		}
		tex->SetPixels(0, 0, 512, 512, data);
		tex->Apply();
		return tex;
	}
	Texture* GetGridTexture()
	{
		Texture* tex = Texture::LoadTexture(GridTexture_Path);
		return tex;
	}
	Texture* GetDefaultTexture()
	{
		Texture* tex = Texture::LoadTexture(DefaultTexture_Path);
		return tex;
	}
	AssetPool<Texture>* Texture::m_texturePool = new AssetPool<Texture>();
	std::map<TextureFormat, int32_t> formatMap = {
		{TextureFormat::R16, GL_R16},
		{TextureFormat::A, GL_ALPHA},
		{TextureFormat::RGB, GL_RGB},
		{TextureFormat::RGBA, GL_RGBA},
		{TextureFormat::BGR, GL_BGR},
		{TextureFormat::BGRA, GL_BGRA},
	};
	std::map<TextureWrapMode, int32_t> wrapMap = {
		{TextureWrapMode::Repeat, GL_REPEAT},
		{TextureWrapMode::Mirror, GL_MIRRORED_REPEAT},
		{TextureWrapMode::Clamp, GL_CLAMP_TO_EDGE},
		{TextureWrapMode::ClampBorder, GL_CLAMP_TO_BORDER},
	};
	std::map<TextureFilterMode, int32_t> filterMap = {
		{TextureFilterMode::Bilinear, GL_LINEAR},
		{TextureFilterMode::Point, GL_NEAREST},
	};
	std::map<CommomTexture, std::pair<std::string, std::function<Texture* ()>>> texture_commonMap = {
		{CommomTexture::White, {"White Texture", GetWhiteTexture}},
		{CommomTexture::Grid, {"Grid Texture", GetGridTexture}},
		{CommomTexture::Default, {"Deafult Texture", GetDefaultTexture}},
	};
	#pragma endregion

	void CreateDefaultTextures()
	{
		TARA_DEBUG_LEVEL("Buildin resources texture create: White", 1);
		Texture::GetCommon(CommomTexture::White);
		TARA_DEBUG_LEVEL("Buildin resources texture create: Grid", 1);
		Texture::GetCommon(CommomTexture::Grid);
		TARA_DEBUG_LEVEL("Buildin resources texture create: Default", 1);
		Texture::GetCommon(CommomTexture::Default);
	}

	Texture::Texture(int32_t width, int32_t height, TextureFormat format)
	{
		TARA_DEBUG_LEVEL("Texture created!", 1);
		glGenTextures(1, &m_textureID);
		m_width = width;
		m_height = height;
		m_format = format;
		int32_t strd = stride.at(m_format);
		int size = m_width * m_height * strd;
		m_colordata = new unsigned char[size];
		GetAssetPool()->Add(*this);
	}
	Texture::~Texture()
	{
		TARA_DEBUG_LEVEL("Texture destroy! %s", 1, Name().c_str());
		glDeleteTextures(1, &m_textureID);
	}

	Texture* Texture::GetCommon(CommomTexture type)
	{
		if (!texture_commonMap.count(type)) {
			TARA_WARNING_LEVEL("Commom texture does not register:", 3);
			return nullptr;
		}
		auto cgs = texture_commonMap.at(type);
		Texture* s = GetAssetPool()->FindByName(cgs.first.c_str(), true);
		if (s == nullptr) {
			s = cgs.second();
			s->Name() = cgs.first;
			s->BuildIn() = true;
		}
		else {
			return s;
		}
	}
	Texture* Texture::LoadTexture(const char* path)
	{
		int w, h, cha = 0;
		stbi_set_flip_vertically_on_load(true);
		unsigned char* data = stbi_load(path, &w, &h, &cha, 3); //new unsigned char[s];
		if (data) {
			Texture* tex = new Texture(w, h, TextureFormat::RGB);
			tex->m_name = "Default Texture";
			TARA_DEBUG_LEVEL("\tImport texture successfully: \"%s\"  \"%s\"", 2, path, tex->Name().c_str());
			tex->m_buildIn = false;
			tex->m_width = w;
			tex->m_height = h;
			tex->m_colordata = data;
			tex->Apply();
			//stbi_image_free(tex->m_colordata);
			return tex;
		}
		else {
			TARA_DEBUG("Failed to load Texture %s", path);
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
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapMap.at(m_wrap_s));
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapMap.at(m_wrap_t));
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, wrapMap.at(m_wrap_r));
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filterMap.at(m_filter));
		glTexImage2D(GL_TEXTURE_2D, 0, formatMap.at(m_format), m_width, m_height, 0, formatMap.at(m_format), GL_UNSIGNED_BYTE, m_colordata);
		glGenerateMipmap(GL_TEXTURE_2D);
		TARA_DEBUG_LEVEL("Apply texture ! %s", 1, Name().c_str());
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

	TextureWrapMode& Texture::WrapS()
	{
		return m_wrap_s;
	}
	TextureWrapMode& Texture::WrapT()
	{
		return m_wrap_t;
	}
	TextureWrapMode& Texture::WrapR()
	{
		return m_wrap_r;
	}
	TextureFilterMode& Texture::Filter()
	{
		return m_filter;
	}
	TextureFormat& Texture::Format()
	{
		return m_format;
	}
	glm::ivec2 Texture::Size()
	{
		return glm::ivec2(m_width, m_height);
	}
	uint32_t Texture::TextureID()
	{
		return m_textureID;
	}
};