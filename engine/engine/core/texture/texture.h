#pragma once
// Include std library
#include <map>
#include <vector>

// Include third party library
#include <glm/glm.hpp>

// Include tara library
#include "../config.h"
#include "../asset.h"

namespace Tara {
	/*
		Summary:
			Texture format. effect stride.
	*/
	enum class TARA_API TextureFormat {
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
	enum class TARA_API TextureWrapMode {
		Repeat,
		Mirror,
		Clamp,
		ClampBorder
	};


	/*
		Summary:
			Texture filter mode.
	*/
	enum class TARA_API TextureFilterMode {
		Bilinear,
		Point
	};


	enum class TARA_API CubeMapType {
		Front = 0x8519,
		Back = 0x851A,
		Left = 0x8516,
		Right = 0x8515,
		Up = 0x8517,
		Down = 0x8518
	};


	struct TARA_API TextureConfig {
	public:
		TextureWrapMode Wrap_s = TextureWrapMode::Repeat;
		TextureWrapMode Wrap_t = TextureWrapMode::Repeat;
		TextureWrapMode Wrap_r = TextureWrapMode::Repeat;
		TextureFilterMode Filter = TextureFilterMode::Bilinear;
		TextureFormat Format = TextureFormat::RGB;
	};

	class TARA_API Texture : public AssetBase {
		friend class Material;
		friend class BuildinManager;
	public:
		Texture();
		~Texture();
		static AssetPool<Texture>& GetAssetPool();
		/*
			Summary:
				Binding textures.
		*/
		virtual void Bind() = 0;
		/*
			Summary:
				Unbinding textures.
		*/
		virtual void Unbind() = 0;
		/*
			Summary:
				Apply current changed setting.
		*/
		virtual void Apply() = 0;
		/*
			Summary:
				Current texture wrap mode (X, U) Axis.
		*/
		TextureConfig& Config();
		/*
			Summary:
				Texture ID.
		*/
		uint32_t TextureID();

	protected:
		Texture(bool buildin);
		uint32_t m_textureID = -1;
		TextureConfig m_config = TextureConfig();
		TextureConfig m_configbuffer = TextureConfig();
		unsigned char* m_colordata = new unsigned char[0];
		static AssetPool<Texture>* m_texturePool;
	};

	/*
		Summary:
	*/
	class TARA_API Texture2D : public Texture {
		friend class Material;
		friend class BuildinManager;
	public:
		Texture2D(int32_t width = 1, int32_t height = 1, TextureFormat format = TextureFormat::RGB);
	protected:
		Texture2D(bool buildin, int32_t width = 1, int32_t height = 1, TextureFormat format = TextureFormat::RGB);
	public:
		~Texture2D();

		void Bind() override;
		void Unbind() override;
		void Apply() override;

		/*
			Summary:
				Loading texture from file path.
		*/
		static Texture2D* ImportFromFile(std::string path);
		static Texture2D* ImportFromMemory(std::vector<uint8_t> memory);
		static Texture2D* ImportFromMemory(std::vector<char> memory);
		static Texture2D* ImportFromMemory(const void* data, size_t length);
		/*
			Summary:
				Clone texture object.
		*/
		Texture2D& Clone();
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
				Texture size.
		*/
		glm::ivec2 Size();

	protected:
		glm::ivec2 m_Size;
		unsigned char* m_Colordata = new unsigned char[0];
	};

	class TARA_API TextureMulti2DSample : public Texture2D {
		friend class Material;
		friend class TextureBuildIn;
		TextureMulti2DSample(int32_t width = 1, int32_t height = 1, TextureFormat format = TextureFormat::RGB);
	protected:
		TextureMulti2DSample(bool buildin, int32_t width = 1, int32_t height = 1, TextureFormat format = TextureFormat::RGB);
	public:
		void Bind() override;
		void Unbind() override;
		void Apply() override;
	};

	class TARA_API TextureCube : public Texture {
		friend class Material;
		friend class TextureBuildIn;
	public:
		TextureCube(int32_t width = 1, int32_t height = 1, TextureFormat format = TextureFormat::RGB);
	protected:
		TextureCube(bool buildin, int32_t width = 1, int32_t height = 1, TextureFormat format = TextureFormat::RGB);
	public:
		~TextureCube();

		void Bind() override;
		void Unbind() override;
		void Apply() override;

		/*
			Summary:
				Loading texture from file path.
		*/
		static TextureCube* LoadTexture(const char* front,
			const char* back, 
			const char* left, 
			const char* right, 
			const char* up, 
			const char* down);

		TextureCube& Clone();

		bool ReplaceTexture(CubeMapType type, unsigned char* data, glm::ivec2 size);
		bool ReplaceTexture(CubeMapType type, const char* path, glm::ivec2 size);
		bool ReplaceTexture(CubeMapType type, Texture* tex, glm::ivec2 size);
		/*
			Summary:
				Texture size.
		*/
		glm::ivec2 Size(CubeMapType type);

	protected:
		std::map<CubeMapType, glm::ivec2> m_Size = std::map<CubeMapType, glm::ivec2>();
		std::map<CubeMapType, unsigned char*> m_Colordata = std::map<CubeMapType, unsigned char*>();
	};

	inline TARA_API AssetPool<Texture>* Texture::m_texturePool = new AssetPool<Texture>();
}