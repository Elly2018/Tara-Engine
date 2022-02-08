#pragma once
#include <config.h>
#include <asset.h>
#include <glm/glm.hpp>

namespace Tara {
	/*

		Structs, classes declaration

	*/
	class DllExport FrameBuffer;

	class FrameBuffer : public AssetBase
	{
	public:
		FrameBuffer(int32_t width = 1920, int32_t height = 1080);
		~FrameBuffer();
		/*
			Summary:
				Get asset pool
		*/
		static AssetPool<FrameBuffer> GetAssetPool();

		void Bind();
		void Unbind();
		void BindTexture();
		void UnbindTexture();
		uint32_t GetTextureID();
		glm::ivec2 GetSize();

	private:
		int32_t m_width, m_height;
		uint32_t m_framebufferID;
		uint32_t m_textureID;
		uint32_t m_renderBufferID;
		static AssetPool<FrameBuffer> m_framebufferPool;
	};
}