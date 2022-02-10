#pragma once
#include <config.h>
#include <asset.h>
#include <glm/glm.hpp>

namespace Tara {
	/*
		Summary:
			Framebuffer anti-alise sampling.
	*/
	enum class DllExport MSAASamples {
		None,
		_2x,
		_4x,
		_8x,
		_16x
	};


	/*
		Summary:
			Handle the framebuffer behaviour.
	*/
	class DllExport FrameBuffer : public AssetBase
	{
	public:
		FrameBuffer(int32_t width = 1920, int32_t height = 1080, MSAASamples sample = MSAASamples::_2x);
		~FrameBuffer();
		/*
			Summary:
				Get asset pool.
		*/
		static AssetPool<FrameBuffer>* GetAssetPool();
		/*
			Summary:
				Binding framebuffer.
		*/
		void Bind();
		/*
			Summary:
				Blit the sample buffer to color textures of intermediate framebuufer.
		*/
		void Blit();
		/*
			Summary:
				Unbinding framebuffer.
		*/
		void Unbind();
		/*
			Summary:
				Binding color texture.
		*/
		void BindTexture();
		/*
			Summary:
				Unbinding color texture.
		*/
		void UnbindTexture();
		/*
			Summary:
				Resize framebuffer and it's binding color and depth textures.
		*/
		void Resize(int32_t _w, int32_t _h);
		/*
			Summary:
				Change sampling config.
		*/
		void SetSamples(MSAASamples _samples);

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

	private:
		int32_t m_width = 1;
		int32_t m_height = 1;
		MSAASamples m_ssaa = MSAASamples::None;
		uint32_t m_framebufferID = -1;
		uint32_t m_intermediateFramebufferID = -1;
		uint32_t m_textureID = -1;
		uint32_t m_multiSampledTextureID = -1;
		uint32_t m_renderBufferID = -1;
		static AssetPool<FrameBuffer>* m_framebufferPool;
	};
}