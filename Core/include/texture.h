#pragma once
#include <vector>
#include <config.h>
#include <asset.h>
#include <glm/glm.hpp>

namespace Tara {
	/*

		Structs, classes declaration

	*/
	class DllExport Texture;

	enum class DllExport CommomTexture {
		White,
		Grid,
		Default
	};

	enum class DllExport TextureFormat {
		R16 = 0x822A,
		A = 0x1906,
		RGB = 0x1907,
		RGBA = 0x1908,
		BGR = 0x80E0,
		BGRA = 0x80E1
	};

	DllExport void CreateDefaultTextures();

	class Texture : public AssetBase
	{
	public:
		friend class Material;
		Texture();
		Texture(int32_t _w, int32_t _h, TextureFormat _f);
		~Texture();

		static Texture* GetCommon(CommomTexture type);
		static Texture* GetWhiteTexture(int32_t size = 512);
		static Texture* GetGridTexture();
		static Texture* GetDefaultTexture();
		/*
			Summary:
				Get asset pool
		*/
		static AssetPool<Texture>* GetAssetPool();

		void Bind();
		void Unbind();

		void Apply();
		void SetPixel(int32_t x, int32_t y, unsigned char* data);
		void SetPixels(int32_t x, int32_t y, int32_t w, int32_t h, unsigned char* data);
		glm::vec4 ReadPixel(int32_t x, int32_t y);
		std::vector<glm::vec4> ReadPixels(int32_t x, int32_t y, int32_t w, int32_t h);
		glm::ivec2 Size();
		uint32_t ID();

	private:
		uint32_t m_textureID = -1;
		int32_t m_width = 1;
		int32_t m_height = 1;
		TextureFormat m_format;
		unsigned char* m_colordata;
		static AssetPool<Texture>* m_texturePool;
	};
}

