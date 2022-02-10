#pragma once
#include <vector>
#include <config.h>
#include <asset.h>
#include <glm/glm.hpp>

namespace Tara {
	/*
		Summary:
			BuildIn texture types.
	*/
	enum class DllExport CommomTexture {
		White,
		Grid,
		Default
	};


	/*
		Summary:
			Texture format. effect stride.
	*/
	enum class DllExport TextureFormat {
		R16,
		A,
		RGB,
		RGBA,
		BGR,
		BGRA
	};


	/*
		Summary:
			Texture wrap mode.
	*/
	enum class DllExport TextureWrapMode {
		Repeat,
		Mirror,
		Clamp,
		ClampBorder
	};


	/*
		Summary:
			Texture filter mode.
	*/
	enum class DllExport TextureFilterMode {
		Bilinear,
		Point
	};


	/*
		Summary:
			Create all buildin textures.
	*/
	DllExport void CreateDefaultTextures();


	/*
		Summary:
	*/
	class DllExport Texture : public AssetBase
	{
	public:
		friend class Material;
		Texture(int32_t width = 1, int32_t height = 1, TextureFormat format = TextureFormat::RGB);
		~Texture();

		/*
			Summary:
				Get the buildin textures.
		*/
		static Texture* GetCommon(CommomTexture type);
		/*
			Summary:
				Loading texture from file path.
		*/
		static Texture* LoadTexture(const char* path);
		/*
			Summary:
				Get asset pool.
		*/
		static AssetPool<Texture>* GetAssetPool();
		/*
			Summary:
				Binding textures.
		*/
		void Bind();
		/*
			Summary:
				Unbinding textures.
		*/
		void Unbind();
		/*
			Summary:
				Apply current changed setting.
		*/
		void Apply();
		/*
			Summary:
				Put pixel data at the given position of texture.
		*/
		void SetPixel(int32_t x, int32_t y, unsigned char* data);
		/*
			Summary:
				Put pixels data at the given rect of texture.
		*/
		void SetPixels(int32_t x, int32_t y, int32_t w, int32_t h, unsigned char* data);
		/*
			Summary:
				Read pixel data from the given position of texture.
		*/
		glm::vec4 ReadPixel(int32_t x, int32_t y);
		/*
			Summary:
				Read pixels data from the given rect of texture.
		*/
		std::vector<glm::vec4> ReadPixels(int32_t x, int32_t y, int32_t w, int32_t h);

		/*
			Summary:
				Current texture wrap mode (X, U) Axis.
		*/
		TextureWrapMode& WrapS();
		/*
			Summary:
				Current texture wrap mode (Y, V) Axis.
		*/
		TextureWrapMode& WrapT();
		/*
			Summary:
				Current texture wrap mode (Z) Axis.
				This only works at 3D texture.
		*/
		TextureWrapMode& WrapR();
		/*
			Summary:
				Current apply filter setting.
		*/
		TextureFilterMode& Filter();
		/*
			Summary:
				Current texture format.
		*/
		TextureFormat& Format();
		/*
			Summary:
				Texture size.
		*/
		glm::ivec2 Size();
		/*
			Summary:
				Texture ID.
		*/
		uint32_t TextureID();

	private:
		uint32_t m_textureID = -1;
		int32_t m_width = 1;
		int32_t m_height = 1;
		TextureWrapMode m_wrap_s = TextureWrapMode::Repeat;
		TextureWrapMode m_wrap_t = TextureWrapMode::Repeat;
		TextureWrapMode m_wrap_r = TextureWrapMode::Repeat;
		TextureFilterMode m_filter = TextureFilterMode::Bilinear;
		TextureFormat m_format = TextureFormat::RGB;
		unsigned char* m_colordata = new unsigned char[0];
		static AssetPool<Texture>* m_texturePool;
	};
}

