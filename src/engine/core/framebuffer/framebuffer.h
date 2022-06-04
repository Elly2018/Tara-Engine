#pragma once
// Include std library
#include <memory>

// Include third party library
#include <glm/glm.hpp>

// Include tara library
#include "../config.h"
#include "../asset.h"

namespace Tara {
	/*
		Summary:
			Framebuffer anti-alise sampling.
	*/
	enum class TARA_API MSAASamples {
		None,
		_2x,
		_4x,
		_8x,
		_16x
	};


	enum class TARA_API FrameBufferTextureType {
		Color,
		Depth
	};


	/*
		Summary:
			Handle the framebuffer behaviour.
	*/
	class TARA_API FrameBuffer : public AssetBase
	{
	public:
		FrameBuffer(int32_t width = 1920, int32_t height = 1080);
		virtual ~FrameBuffer();
		/*
			Summary:
				Get asset pool.
		*/
		static AssetPool<FrameBuffer>& GetAssetPool();
		/*
			Summary:
				Binding framebuffer.
		*/
		void Bind();
		/*
			Summary:
				Unbinding framebuffer.
		*/
		void Unbind();
		/*
			Summary:
				Binding color texture.
		*/
		virtual bool BindTexture(FrameBufferTextureType type = FrameBufferTextureType::Color);
		/*
			Summary:
				Unbinding color texture.
		*/
		void UnbindTexture();
		/*
			Summary:
				Resize framebuffer and it's binding color and depth textures.
		*/
		virtual void Resize(int32_t _w, int32_t _h);
		/*
			Summary:
				Get frambuffer id
		*/
		uint32_t& FramebufferID();
		/*
			Summary:
				Get color texture id
		*/
		uint32_t& TextureID();
		/*
			Summary:
				Change sampling config.
		*/
		glm::ivec2& Size();

	protected:
		int32_t m_width = 1;
		int32_t m_height = 1;
		uint32_t m_framebufferID = -1;
		uint32_t m_textureID = -1;
		static AssetPool<FrameBuffer>* m_framebufferPool;
	};


	class TARA_API DisplayFrameBuffer : public FrameBuffer {
	public:
		DisplayFrameBuffer(int32_t width = 1920, int32_t height = 1080, MSAASamples sample = MSAASamples::_2x);
		~DisplayFrameBuffer();
		/*
			Summary:
				Blit the sample buffer to color textures of intermediate framebuufer.
		*/
		void Blit();
		/*
			Summary:
				Change sampling config.
		*/
		void SetSamples(MSAASamples _samples);
		/*
			Summary:
				Resize framebuffer and it's binding color and depth textures.
		*/
		void Resize(int32_t _w, int32_t _h) override;

	private:
		MSAASamples m_ssaa = MSAASamples::None;
		uint32_t m_intermediateFramebufferID = -1;
		uint32_t m_multiSampledTextureID = -1;
		uint32_t m_renderBufferID = -1;
	};

	class TARA_API ShadowFrameBuffer : public FrameBuffer {
	public:
		ShadowFrameBuffer(int32_t width = 1024, int32_t height = 1024);
		~ShadowFrameBuffer();
	};
}